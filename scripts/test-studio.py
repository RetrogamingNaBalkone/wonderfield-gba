"""Compare complete PPU frames with the Mode 4 ROM/ELF from the parent revision."""
import argparse
import itertools
import json
import hashlib
import os
from pathlib import Path
import shlex
import struct
import subprocess
from emulator import ROOT, symbols

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('reference', type=Path, help='directory containing original pole.gba and pole.elf')
parser.add_argument('--current', type=Path, default=ROOT / 'build/gba')
parser.add_argument('--report', type=Path)
parser.add_argument('--comparison', type=Path, help='save example frames from both cartridges side by side')
args = parser.parse_args()
if args.comparison:
    from PIL import Image
build = Path(os.environ['MGBA_BUILD']).resolve()
flags = []
for line in (build/'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
    if line.startswith(('C_DEFINES =', 'C_INCLUDES =')):
        flags.extend(shlex.split(line.split('=', 1)[1]))
qa = ROOT/'build/qa'
qa.mkdir(parents=True, exist_ok=True)
driver = qa/'test-studio'
subprocess.run(['cc', *flags, str(ROOT/'scripts/test-studio.c'), '-L'+str(build),
                '-Wl,-rpath,'+str(build), '-lmgba', '-o', str(driver)], check=True)


class Cartridge:
    def __init__(self, path):
        self.sym = symbols(path/'pole.elf')
        self.proc = subprocess.Popen([str(driver), str(path/'pole.gba')],
                                     stdin=subprocess.PIPE, stdout=subprocess.PIPE)

    def write(self, symbol, value, word=0):
        address = self.sym[symbol] + 4*word
        self.proc.stdin.write(f'w {address:x} {value&0xffffffff:x}\n'.encode())

    def string(self, addr, data):
        for offset, byte in enumerate(data+b'\0'):
            self.proc.stdin.write(f'b {addr+offset:x} {byte:x}\n'.encode())

    def call(self, symbol):
        self.proc.stdin.write(f'c {self.sym[symbol]:x}\n'.encode())

    def frame(self, tiled):
        s = self.sym
        mute = s.get('mute_icon', 0 if tiled else s.get('draw_mute_icon', 0))
        self.proc.stdin.write(f'f {s["render"]:x} {mute:x} {s["present"]:x}\n'.encode())
        self.proc.stdin.flush()
        info = struct.unpack('<5I', self.proc.stdout.read(20))
        pixels = self.proc.stdout.read(240*160*2)
        assert len(pixels) == 240*160*2
        return info, pixels

    def close(self):
        self.proc.stdin.close()
        assert self.proc.wait() == 0


old, new = carts = [Cartridge(path) for path in (args.reference, args.current)]
count = 0
hot_cycles = []
measurements = []
examples = []


def put(symbol, value, word=0):
    for cart in carts:
        cart.write(symbol, value, word)


def fixture(mode, humans=1, now=500, phase=4):
    put('fast_input', 0)
    for word, value in {3: mode, 4: 0, 5: 2, 6: 3, 7: 4, 8: 150,
                        9: 0, 10: 25, 11: 500, 12: 0, 13: 1, 70: 3,
                        71: int(mode == 3), 81: 0}.items():
        put('game', value, word)
    for word,value in {0: now, 1: 490, 3: 470, 4: 490, 7: 530, 8: phase,
                       11: 48, 12: 0, 15: 1, 38: 0, 42: 1, 43: 0}.items():
        put('scene', value, word)
    for word,value in {0: humans, 2: 2, 3: 2, 6: 0}.items():
        put('mp', value, word)
    for cart in carts:
        for i, name in enumerate([b'LEFT', b'RIGHT', b'HUMAN']):
            cart.string(cart.sym['mp']+28+11*i, name)
        for name, text in [('message1','msg_1011'), ('message2','msg_101d')]:
            cart.write(name, cart.sym[text])


def check(label, tiled=True, hot=False):
    global count
    _, before = old.frame(False)
    info, after = new.frame(tiled)
    measurements.append(dict(case=label,render_cycles=info[0],last_line=info[1],
                             cycles_after_vblank=info[3],vblanks=info[4],animation=hot))
    if before != after:
        diff = [i for i in range(240*160) if before[2*i:2*i+2] != after[2*i:2*i+2]]
        for name, data in [('reference', before), ('current', after)]:
            (qa/f'studio-{name}.ppm').write_bytes(b'P6\n240 160\n255\n'+
                bytes(((v >> shift) & 31)*255//31 for v, in struct.iter_unpack('<H',data) for shift in (0,5,10)))
        raise AssertionError((label,len(diff),[(i%240,i//240) for i in diff[:12]]))
    if args.comparison and label in (('wheel',3,19),('walk',3,217,12),('chest',3,1,6)):
        pair = Image.new('RGB',(480,160))
        for x, data in [(0,before),(240,after)]:
            rgb=bytes(((v>>shift)&31)*255//31 for v, in struct.iter_unpack('<H',data) for shift in (0,5,10))
            pair.paste(Image.frombytes('RGB',(240,160),rgb),(x,0))
        examples.append(pair)
    assert info[2]&7 == (0 if tiled else 4), label
    if hot:
        hot_cycles.append(info[0])
        assert info[0] < 280896 and info[4]==1, (label,info)
    count += 1


try:
    for humans in (1, 2, 3):
        for mode in (1,2,3,4,6,7,8,9,10,15,16,17,18,22,35):
            fixture(mode, humans)
            check((mode,humans))
        fixture(2, humans)
        for phase in range(32):
            put('game', (12-phase//2)&15, 7)
            put('scene', phase%2, 38)
            check(('wheel', humans, phase), hot=phase>0)
        for phase, age in itertools.product(range(6), (0,18,36,54)):
            fixture(15, humans, now=490+age, phase=phase)
            check(('intro',humans,phase,age))
        fixture(16, humans)
        put('game',100,8)
        for x, age in itertools.product((-8,10,14,15,32,210,217,224,225), (0,6,12,18)):
            put('scene',x,11)
            put('scene',504+age,0)
            check(('walk',humans,x,age),hot=(x,age)!=(-8,0))
        fixture(8, humans)
        for option, elapsed in itertools.product(range(2),(0,6,89,90)):
            put('game',option,81)
            put('scene',490+elapsed,0)
            check(('chest',humans,option,elapsed))
        fixture(1,humans)
        for face in range(11):
            put('scene',face,43)
            check(('host',humans,face),hot=face>0)
        fixture(17,humans)
        for age in range(41):
            put('scene',470+age,0)
            check(('credits',humans,age),hot=age>0)
    for mode in (0,23,11,12,24,5,14,19,21):
        fixture(mode)
        check(('page',mode),tiled=mode in (5,19,21))
        fixture(3,3)
        check(('back to stage',mode))
    # Check active-player perspectives, original and expanded portraits, labels
    # behind chests, every key, and both transparent and opaque black surfaces.
    for graphics,viewer,avatar in itertools.product(range(2),range(3),range(9)):
        if graphics==0 and avatar>6:continue
        fixture(8,3)
        put('prefs',graphics,2);put('mp',viewer,2);put('mp',(1<<viewer) if avatar%2 else 0,6)
        for i in range(3):
            put('avatars',(avatar+i)%(9 if graphics else 7),i)
            put('game',0 if i==viewer else 123456789,9+i)
        put('prefs',avatar%3,4);put('prefs',5,5)
        check(('portraits',graphics,viewer,avatar))
    for mode,cursor in itertools.product((3,4,5),range(32)):
        fixture(mode,3)
        put('game',cursor,70);put('game',cursor%2,18+cursor%20)
        put('game',int(cursor%3!=0),38+cursor)
        check(('cursor',mode,cursor))
    for mode in (1,2,3,4,6,7,8,9,10,15,16,17,18,19,21,22,35):
        fixture(mode,2)
        put('sound_on',0)
        for cart in carts:
            cart.string(cart.sym['turn_line'],b'ABCDEFGHIJKLMNO PQRSTUVWXYZ123')
            cart.write('message1',cart.sym['turn_line'])
        check(('mute-long-speech',mode))
        put('sound_on',1)
    for page in range(4):
        fixture(19)
        put('scene',1,45);put('scene',page,46)
        check(('certificate',page))
    for mode in (0,11,12,14,23,24,25,26,27,28,30,31,32,33,34,36,37,38,39):
        fixture(mode,3)
        put('prefs',0,3);put('avatars',0,2)
        check(('menu',mode),tiled=False)
    for humans in (1,3):
        fixture(7,humans)
        put('game',1000,83);put('game',0x1234567,2)
        for cart in carts:cart.call('cash_begin')
        put('scene',500,0);put('scene',495,1)
        for pose in range(11):
            put('scene',pose,43)
            check(('cash-host',humans,pose),hot=pose>0)
        for step in range(34):
            for cart in carts:
                for _ in range(min(3,100-step*3)):cart.call('cash_note')
            put('cash',1,5)
            check(('notes',humans,step),hot=step>0)
        fixture(23);check(('pause-cash',humans),tiled=False)
        fixture(21,humans);check(('restore-cash',humans))
    assert all(r['last_line']>=160 and r['cycles_after_vblank']<83776 for r in measurements), [r for r in measurements if r['last_line']<160]
    if args.comparison:
        sheet=Image.new('RGB',(480,160*len(examples)))
        for i,pair in enumerate(examples):sheet.paste(pair,(0,i*160))
        sheet.save(args.comparison)
    if args.report:
        args.report.write_text(json.dumps(dict(frames=count,
            reference_sha256=hashlib.sha256((args.reference/'pole.gba').read_bytes()).hexdigest(),
            rom_sha256=hashlib.sha256((args.current/'pole.gba').read_bytes()).hexdigest(),
            measurements=measurements),indent=2)+'\n')
    print(f'{count} complete 240x160 PPU frames identical. '
          f'Slowest cached animation render {max(hot_cycles)} cycles (frame budget 280896).')
finally:
    for cart in carts:
        cart.close()
