"""Exercise avatar choice through the ROM and inspect resulting scene pixels."""
import runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
tap,read,write,setmp=m['tap'],m['read'],m['write'],m['setmp']
def selected(e):return struct.unpack('<3i',read(e,'avatars',12))
def redraw(e):write(e,'dirty',struct.pack('<i',1));e.run(30)
for version in (0,1):
 e=Emulator();e.run(100);tap(e,3);tap(e,8);tap(e,5);tap(e,5);tap(e,8)
 if version==0:tap(e,4);tap(e,7);tap(e,5)
 tap(e,8);assert e.state()[3]==27
 tap(e,8);tap(e,3);assert e.state()[3]==33
 assert selected(e)==(0,0,0)
 count=9 if version else 7
 for avatar in range(count):
  assert selected(e)[2]==avatar
  e.screenshot(f'avatar-v{version+1}-{avatar}.png');tap(e,7)
 assert selected(e)[2]==0
 tap(e,6);assert selected(e)[2]==count-1
 tap(e,0);assert e.state()[3]==27
 tap(e,3);assert selected(e)[2]==count-1
 tap(e,8);assert m['mp'](e)[4]==0
 m['accept_name'](e);m['accept_name'](e)
 assert selected(e)==(0,0,count-1)
 e.run(1400);assert e.state()[3]==1
 # Fix the scene for visual comparisons; real rendering reads the stable ids.
 e.poke(3,1);e.poke(5,0);setmp(e,2,0);e.poke(71,0);redraw(e)
 e.screenshot(f'avatar-v{version+1}-in-game.png')
 before=e.raw
 setmp(e,6,4);redraw(e);e.screenshot(f'avatar-v{version+1}-eliminated.png')
 # Player one lies on the right from viewer two's perspective.
 stride=240*(4 if e.format==1 else 2);bpp=stride//240
 def portrait(frame):return b''.join(frame[y*stride+153*bpp:y*stride+183*bpp] for y in range(83,110))
 assert portrait(before)!=portrait(e.raw)
 setmp(e,6,0);redraw(e);assert portrait(before)==portrait(e.raw)
 for viewer in (0,1,2):
  setmp(e,2,viewer);redraw(e);assert selected(e)==(0,0,count-1)
 e.close()
 print(f'PASS version {version+1}: all avatars, wrap, name return, identity, disappearance/restoration')
