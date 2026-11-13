"""Real title-to-mode navigation and fixed lower-panel boundaries in mGBA."""
import runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'));tap,read,write=m['tap'],m['read'],m['write']
for choice in range(3):
 for humans in ((1,) if choice==0 else (2,3)):
  e=Emulator();e.run(150);tap(e,8);assert e.state()[3]==26
  e.screenshot('mode-menu-direct.png')
  for _ in range(choice):tap(e,5)
  tap(e,8)
  if choice==2:
   assert e.state()[3]==39;tap(e,8)
   assert e.state()[3]==30 and not struct.unpack('<i',read(e,'link_name_edit',4))[0]
   tap(e,0);assert e.state()[3]==39
   tap(e,0);assert e.state()[3]==26
   tap(e,0);assert e.state()[3]==0
   e.close();continue
  if choice==1:
   assert e.state()[3]==34
   if humans==3:tap(e,5)
   e.screenshot(f'player-count-{choice}-{humans}.png');tap(e,8)
  assert e.state()[3]==32
  assert m['mp'](e)[0]==(2 if choice==2 else humans) and m['mp'](e)[1]==(choice==2)
  tap(e,0);assert e.state()[3]==(34 if choice==1 else 39 if choice==2 else 26)
  if choice in (1,2):
   tap(e,0);assert e.state()[3]==26
  tap(e,0);assert e.state()[3]==0
  e.close()
# Explicit scene fixture: lower wheel pixels must remain intact above y=144.
e=Emulator();m['menu'](e,1);m['accept_name'](e);m['accept_name'](e);e.run(1400)
e.poke(3,2);e.poke(75,10000)
scene=bytearray(read(e,'scene',180));struct.pack_into('<i',scene,152,0);write(e,'scene',bytes(scene))
write(e,'dirty',struct.pack('<i',1));e.run(60)
frame=read(e,'framebuffer',240*160)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
spin_half=struct.unpack_from('<i',read(e,'scene',180),152)[0]
phase=(24-e.state()[7]*2+spin_half)&31
bank=e.sym['wheel_bitmaps']-0x08000000+phase*128*112
for y in range(132,144):
 assert frame[y*240+28:y*240+156]==rom[bank+(y-44)*128:bank+(y-44+1)*128],y
e.screenshot('panel-bottom-spin.png')
# A displayed control hint covers scores; it does not reserve a permanent row.
e.poke(3,4);write(e,'dirty',struct.pack('<i',1));e.run(60)
frame=read(e,'framebuffer',240*160)
assert set(frame[152*240:])<=set((0,7))
e.screenshot('panel-bottom-hint.png');e.close()
print('PASS: direct mode menu, all five routes, back navigation, wheel clearance, bottom hint overlay')
