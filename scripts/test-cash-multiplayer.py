"""Cash acceptance on Prize: all human seats, offers and two full turn cycles.

RAM fixtures select rare offers and zero sectors; actual ROM input handlers
accept money, eliminate participants and select subsequent players.
"""
import runpy,struct
from emulator import Emulator, ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'));tap=m['tap'];mp=m['mp'];setmp=m['setmp']

def check_bargaining_input():
 e=Emulator()
 def bills():return struct.unpack('<II',m['read'](e,'cash',8))
 def press_with_bounce():
  e.run(8,(8,));e.run(3);e.run(4,(8,));e.run(8)
 try:
  m['menu'](e,0)
  e.poke(3,7);e.poke(5,2);e.poke(81,1);e.poke(82,0)
  tap(e,6)  # Left: take the prize and hear the first offer.
  press_with_bounce()
  assert e.state()[82:84]==(1,100),e.state()[82:84]
  press_with_bounce()
  assert e.state()[82:84]==(2,1000),e.state()[82:84]
  tap(e,6)
  press_with_bounce()
  assert e.state()[3]==21 and bills()==(0,100)
  e.run(108)
  assert 0<bills()[0]<100
  paying=e.checkpoint()
  e.run(100)
  assert e.state()[3]==21 and bills()==(100,100)
  e.restore(paying)
  press_with_bounce()
  assert e.state()[3]==21 and bills()==(100,100)
  press_with_bounce()
  assert e.state()[3]==10
  e.run(40)
  assert e.state()[3]==10
 finally:e.close()

check_bargaining_input()
for humans in (2,3):
 for actor in ((2,0) if humans==2 else (2,0,1)):
  for offer in (1,2,3,4):
   e=Emulator();m['menu'](e,humans-1)
   for _ in range(humans):m['accept_name'](e)
   e.poke(3,7);e.poke(5,actor);e.poke(81,0);e.poke(82,offer);e.poke(83,(100,1000,100000,1000000)[offer-1]);setmp(e,2,actor)
   tap(e,8);assert e.state()[3]==21,e.state()[:10]
   for _ in range(3):
    if e.state()[3]==21:tap(e,8)
   assert mp(e)[6]&(1<<actor),(humans,actor,offer,mp(e),e.state()[:10])
   assert e.state()[3]==35 and e.state()[5]==actor
   tap(e,8)
   assert e.state()[5]!=actor
   # Exercise actual zero-sector transitions through two complete cycles.
   for _ in range(6):
    if e.state()[3]==28:tap(e,8)
    current=e.state()[5];assert current!=actor
    rom=(ROOT/'build/gba/pole.gba').read_bytes()
    sectors=struct.unpack_from('<16h',rom,e.sym['wheel_sectors']-0x08000000)
    values=struct.unpack_from('<12h',rom,e.sym['sector_values']-0x08000000)
    zero=next(i for i,v in enumerate(sectors) if values[v-4]==0)
    scene=bytearray(m['read'](e,'scene',180));struct.pack_into('<i',scene,156,zero);m['write'](e,'scene',bytes(scene))
    e.poke(3,2);tap(e,8)
    assert e.state()[3]==6
    tap(e,8)
    assert e.state()[5]!=actor
   print('PASS',humans,actor,offer);e.close()
