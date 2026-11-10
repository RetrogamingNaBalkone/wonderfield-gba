"""Rendering regressions: perspective-owned player panel and clean name entry after restart."""
import runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
tap,read,write,setmp=m['tap'],m['read'],m['write'],m['setmp']
def redraw(e):write(e,'dirty',struct.pack('<i',1));e.run(30)
def frame(e):return read(e,'framebuffer',240*160)
e=Emulator();m['menu'](e,2)
for _ in range(3):m['accept_name'](e)
e.run(1400);assert e.state()[3]==1
references={}
for viewer in (2,0,1):
 setmp(e,2,viewer)
 for actor in (2,0,1):
  e.poke(5,actor);redraw(e);pixels=frame(e);panel=pixels[150*240:]
  if viewer not in references:references[viewer]=panel
  else:assert references[viewer]==panel,(actor,viewer)
  assert pixels[159*240]==7
 e.screenshot(f'perspective-panel-player{(viewer+1)%3+1}.png')
assert len(set(references.values()))==3
setmp(e,2,2);e.poke(5,2);redraw(e)
# Carry used letters through the actual restart menu into new name entry.
for i in range(32):e.poke(38+i,1)
tap(e,3)
for _ in range(3):tap(e,5)
tap(e,8);assert e.state()[3]==25
tap(e,5);tap(e,8);assert e.state()[3]==0
tap(e,8);tap(e,5);tap(e,8);tap(e,8);tap(e,8);assert e.state()[3]==27
e.run(60);before=frame(e)[84*240:150*240];e.screenshot('name-after-restart.png')
for i in range(32):e.poke(38+i,0)
redraw(e);assert before==frame(e)[84*240:150*240]
tap(e,8);assert e.state()[80]==1
# Actual letter selection must still show the used-letter marks.
e.poke(3,3);e.poke(5,2);e.poke(71,1);redraw(e);clean=frame(e)[84*240:150*240]
for i in range(32):e.poke(38+i,1)
redraw(e);assert clean!=frame(e)[84*240:150*240]
e.close();print('PASS: panel follows viewer and stays stable across active players; restart names ignore used letters; game keyboard retains marks')
