"""Real mGBA input/timer checks; fixtures never replace input entropy.

The seed arithmetic fixtures live in audit_rng.py. These checks exercise
actual timing, SRAM independence, held keys and replay/skip behavior.
"""
from emulator import Emulator, ROOT
import ctypes as c
import hashlib
import json
import struct

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
def read(e,name):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000,4))[0]
def fixture_turn(e):
 for index,value in ((3,1),(5,2),(6,0),(7,12),(81,1),(2,12345)):
  e.poke(index,value)
def result(e):return tuple(e.state()[i] for i in (7,8,2))

boots=[]
for delay in range(4,13):
 e=Emulator();e.run(delay);before=e.state();e.tap(8)
 check(f'early A after {delay} VBlank starts game',e.state()[3]==15)
 boots.append(dict(delay=delay,loop_before=before[1],word=e.state()[6],
                   rng=e.state()[2]&0xffffffff,entropy=read(e,'input_entropy')))
 e.close()
groups={frame:[b for b in boots if b['loop_before']==frame] for frame in {b['loop_before'] for b in boots}}
check('early inputs include multiple frames in the same old loop bucket',any(len(g)>1 for g in groups.values()))
check('different early input frames have distinct seeds within each loop bucket',
      all(len({b['rng'] for b in g})==len(g) for g in groups.values()))

for fill in (0,255):
 e=Emulator()
 e.core.retro_get_memory_size.argtypes=[c.c_uint];e.core.retro_get_memory_size.restype=c.c_size_t
 address=e.core.retro_get_memory_data(0);size=e.core.retro_get_memory_size(0)
 c.memset(address,fill,size);e.core.retro_reset();e.run(220)
 stored=c.string_at(address,size);e.tap(8)
 check(f'game starts with invalid SRAM filled with {fill}',e.state()[3]==15 and 0<=e.state()[6]<495 and read(e,'input_entropy')!=0)
 check(f'input seeding does not write SRAM filled with {fill}',c.string_at(address,size)==stored)
 e.close()

e=Emulator();e.run(220)
seed=e.state()[2];e.run(60)
check('idle title does not advance the game RNG',e.state()[2]==seed)
e.run(12,(8,));entropy=read(e,'input_entropy');e.run(60,(8,))
check('held A collects no repeated input edges',read(e,'input_entropy')==entropy)
e.run(12)
fixture_turn(e);checkpoint=e.checkpoint();timings=[]
for delay in range(8):
 e.restore(checkpoint);e.run(delay)
 check(f'waiting {delay} VBlank before spin leaves draw state unchanged',e.state()[2]==12345)
 e.tap(8)
 check(f'timed human spin {delay} starts',e.state()[3]==2)
 timings.append(dict(delay=delay,rng=e.state()[2]&0xffffffff,entropy=read(e,'input_entropy'),
                     target=struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+156,4))[0]))
check('later human input timings change the RNG',len({t['rng'] for t in timings})==8)
check('timed human spins can select different sectors',len({t['target'] for t in timings})>1)

e.restore(checkpoint);e.tap(8);spin=e.checkpoint()
e.until(lambda s:s[3]!=2);natural=result(e)
for delay in (0,7,30,75):
 e.restore(spin);e.run(delay)
 check(f'skip test {delay} is still spinning',e.state()[3]==2)
 entropy=read(e,'input_entropy');e.tap(8)
 check(f'skip at {delay} captures its own input time',read(e,'input_entropy')!=entropy)
 check(f'skip at {delay} keeps the natural sector, value and RNG',e.state()[3]!=2 and result(e)==natural)

e.restore(checkpoint);e.tap(8);first=(e.state()[2],read(e,'input_entropy'))
e.restore(checkpoint);e.tap(8)
check('complete emulator replay remains deterministic',first==(e.state()[2],read(e,'input_entropy')))

# Ignored gameplay buttons still contribute timing for the next human draw.
e.restore(checkpoint);e.tap(11);fixture_turn(e);e.tap(8);with_input=e.state()[2]
e.restore(checkpoint);e.run(6);fixture_turn(e);e.tap(8)
check('additional input contributes to later RNG state',e.state()[2]!=with_input)
e.close()
report=dict(status='passed',count=len(checks),checks=checks,
 rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),
 early_boots=boots,later_input_timings=timings,
 limitation='Identical complete emulator state and cycle-identical inputs remain reproducible; presses before the first input poll can coalesce.')
out=ROOT/'build/qa/rng-verification.json';out.parent.mkdir(exist_ok=True)
out.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(f'RNG checks passed: {len(checks)}')
print(json.dumps(boots,indent=2))
