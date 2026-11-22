"""Check intro phases in cartridge code, including later-round RAM fixtures."""
import hashlib
import json
import runpy
import struct
from emulator import Emulator, ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
read,write,tap=m['read'],m['write'],m['tap']
def phase(e):return struct.unpack_from('<i',read(e,'scene',36),32)[0]

def check_a_release():
 e=Emulator()
 try:
  e.run(60)
  e.run(20,(8,))
  for _ in range(5):
   e.run(1);e.run(2,(8,))
  assert e.state()[3]==0
  e.run(300)
  assert e.state()[3]==26
  e.run(20,(8,))
  for _ in range(4):
   e.run(3);e.run(3,(8,))
  e.run(200)
  assert e.state()[3]==32
  e.run(8,(8,))
  assert e.state()[3]==15 and phase(e)==0
  # A brief break in the signal while releasing the rules confirmation.
  for _ in range(3):
   e.run(1);e.run(2,(8,))
  assert e.state()[3]==15 and phase(e)==0
  e.run(8)
  checkpoint=e.checkpoint()
  for next_phase in range(1,7):
   start=struct.unpack_from('<I',read(e,'scene',20),16)[0]
   e.until(lambda state:state[3]!=15 or phase(e)==next_phase,limit=190)
   if next_phase<6:
    assert e.state()[3]==15
    end=struct.unpack_from('<I',read(e,'scene',20),16)[0]
   else:
    assert e.state()[3]==1
    end=struct.unpack('<I',read(e,'video_ticks',4))[0]
   assert end-start==180,(next_phase,end-start)
  e.restore(checkpoint)
  tap(e,8)
  assert e.state()[3]==15 and phase(e)==1
  for _ in range(4):tap(e,8)
  assert e.state()[3]==15 and phase(e)==5
  e.run(8,(8,))
  assert e.state()[3]==1
  e.run(1);e.run(2,(8,));e.run(8)
  assert e.state()[3]==1
  e.run(12,(8,))
  assert e.state()[3]==2
  for _ in range(3):
   e.run(3);e.run(2,(8,))
   assert e.state()[3]==2
  e.run(12)
  spin=e.checkpoint()
  e.run(180)
  assert e.state()[3]==2
  e.until(lambda state:state[3]!=2,limit=250)
  sector=e.state()[7]
  e.restore(spin)
  tap(e,8)
  assert e.state()[3]!=2 and e.state()[7]==sector
 finally:e.close()

check_a_release()
checks=[]
for humans in (1,2,3):
 e=Emulator();m['options'](e,humans);tap(e,8)
 if humans>1:
  for _ in range(humans):m['accept_name'](e)
 assert e.state()[3]==15
 for round_index,shootout in ((0,False),(1,False),(0,True)):
  if humans==1 and shootout:continue
  # Isolate the intro; the A presses execute its actual phase transitions.
  e.poke(3,15);e.poke(4,round_index)
  scene=bytearray(read(e,'scene',180));struct.pack_into('<i',scene,32,0);write(e,'scene',scene)
  match=bytearray(read(e,'match',64));struct.pack_into('<i',match,36,int(shootout));write(e,'match',match)
  expected=[4,5] if humans>1 and (round_index or shootout) else [1,2,3,4,5]
  for want in expected:
   tap(e,8);assert e.state()[3]==15 and phase(e)==want,(humans,round_index,shootout,want,phase(e))
  tap(e,8);assert e.state()[3] in (1,28)
  checks.append(dict(humans=humans,round=round_index,shootout=shootout,phases=expected))
 e.close()
report=dict(rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),checks=checks)
(ROOT/'docs/verification/intro-roster-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
