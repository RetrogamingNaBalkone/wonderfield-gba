"""Compare actual ROM animation clocks using identical RAM fixtures in mGBA.

Pass a baseline directory containing pole.gba and pole.elf. Fixtures bypass RNG
and menus, but movement, drawing, IRQs and completion run in cartridge code.
"""
import argparse,ctypes as c,hashlib,json,struct
from pathlib import Path
from emulator import Emulator,ROOT
parser=argparse.ArgumentParser()
parser.add_argument('baseline',type=Path)
args=parser.parse_args()
def measure(directory,humans):
 e=Emulator(directory/'pole.gba',directory/'pole.elf');e.run(220)
 def read(name,off=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+off,4))[0]
 def write(name,value,off=0):c.memmove(e.ram+e.sym[name]-0x02000000+off,struct.pack('<I',value&0xffffffff),4)
 write('fast_input',0)
 if 'mp' in e.sym:
  write('mp',humans)
  for p in range(3):c.memmove(e.ram+e.sym['mp']-0x02000000+28+p*11,b'PLAYER'+bytes([49+p])+b'\0'*4,11)
 def setup(mode):
  e.poke(3,1);e.poke(6,0);write('dirty',1);e.run(60)
  for i,v in {3:mode,4:0,5:2,6:0,7:12,8:10,9:100,10:100,11:100,71:0,72:0,74:0,75:1,76:0,79:0}.items():e.poke(i,v)
  for i in range(20):e.poke(18+i,0)
  write('message1',0);write('message2',0);write('scene',0,168);write('dirty',1)
  return read('video_ticks')
 def trace(mode,fields,start):
  rows=[];last=None
  for frame in range(2000):
   state=fields()
   if state!=last:rows.append([read('video_ticks')-start,*state]);last=state
   if e.state()[3]!=mode:return dict(vblanks=read('video_ticks')-start,trace=rows)
   e.run(1)
  raise AssertionError('Animation did not finish')
 result={}
 for steps in (16,24,31):
  start=setup(2);e.poke(74,steps);e.poke(73,0)
  write('scene',start,20);write('scene',0,152);write('scene',3,156)
  result['spin_'+str(steps)]=trace(2,lambda:[e.state()[7],read('scene',152),e.state()[74]],start)
 for value in (10,100):
  for positions in ([0],[0,2,4]):
   start=setup(16);e.poke(8,value)
   for off,v in {12:start,16:start,36:1,40:0,44:32,48:0,148:100}.items():write('scene',v,off)
   for i in range(20):write('scene',int(i in positions),64+i*4)
   result[f'reveal_{value}_{len(positions)}']=trace(16,lambda:[read('scene',44),read('scene',48),sum(e.state()[18:38])],start)
 e.close()
 return dict(rom_sha256=hashlib.sha256((directory/'pole.gba').read_bytes()).hexdigest(),animations=result)
report={'method':'RAM fixtures; video_ticks sampled every emulated frame; no fast-forward input',
        'v11':measure(args.baseline,1),'current_single':measure(ROOT/'build/gba',1),'current_multiplayer':measure(ROOT/'build/gba',3)}
# A frame of sampling/render latency is allowed, but no missing poses or drift.
for name,before in report['v11']['animations'].items():
 for version in ('current_single','current_multiplayer'):
  after=report[version]['animations'][name]
  assert [r[1:] for r in before['trace']]==[r[1:] for r in after['trace']],(name,version,'poses')
  assert all(abs(a[0]-b[0])<=1 for a,b in zip(before['trace'],after['trace'])),(name,version,'timing')
report['result']='All poses match; all transition timestamps differ by at most one VBlank'
path=ROOT/'docs/verification/animation-pacing-v11.json';path.write_text(json.dumps(report,indent=2)+'\n')
for name,before in report['v11']['animations'].items():
 print(name,*(f'{version}: {report[version]["animations"][name]["vblanks"]}' for version in ('v11','current_single','current_multiplayer')))
