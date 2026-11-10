"""mGBA checks for portrait-bound labels, at-risk badges and viewer-owned footer."""
import ctypes as c
import hashlib
import importlib.util
import json
import struct
from emulator import ROOT, symbols
spec=importlib.util.spec_from_file_location('standings',ROOT/'scripts/test-standings.py')
s=importlib.util.module_from_spec(spec);spec.loader.exec_module(s)
# Every persistent text slot avoids the wheel artwork in all 32 phases.
rom=(ROOT/'build/gba/pole.gba').read_bytes();sym=symbols()
wheel=sym['wheel_bitmaps']-0x08000000;stage=sym['stage_background']-0x08000000
slots=[(1,50,62,10),(124,50,62,10),(4,124,40,8),(141,124,40,8),
       (4,152,80,8),(112,152,40,8),(192,150,44,10)]
for phase in range(32):
 for x,y,w,h in slots:
  for yy in range(y,min(y+h,155)):
   for xx in range(max(x,28),min(x+w,156)):
    assert rom[wheel+phase*128*112+(yy-43)*128+xx-28]==rom[stage+yy*240+xx+4],(phase,xx,yy,'text touches wheel')
checks=[]
for rule in range(3):
 e=s.frame(rule,[0,0,0],[1,0,0] if rule==2 else [10000,20000,30000],0)
 for p,name in enumerate(('АЛЕКСАНДРА','КОНСТАНТИН','СВЯТОСЛАВА')):
  c.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',11)
  e.poke(9+p,12345+p*10000);s.put(e,'match',p,11145+p*10000)
 e.poke(3,6);e.poke(71,0);s.write(e,'message1',struct.pack('<I',0))
 def redraw():
  scene=bytearray(s.read(e,'scene',180));struct.pack_into('<I',scene,4,struct.unpack('<I',s.read(e,'video_ticks',4))[0]);s.write(e,'scene',scene)
  s.write(e,'dirty',struct.pack('<I',1));e.run(30)
 labels={};panels={}
 for viewer in (2,0,1):
  s.m['setmp'](e,2,viewer)
  for actor in (2,0,1):
   e.poke(5,actor);redraw()
   panel=s.crop(e,0,150,240,10)
   if viewer in panels:assert panel==panels[viewer],(rule,viewer,'actor changed footer')
   panels[viewer]=panel
   for side,x in enumerate((0,137)):
    who=(viewer+side+1)%3
    pixels=s.read(e,'framebuffer',240*160);nx=125 if side else 2
    name=bytes(pixels[y*240+xx]==15 for y in range(51,59) for xx in range(nx,nx+60))
    label=name+s.crop(e,x+4,124,40,8)
    if who in labels and label!=labels[who]:
     e.screenshot('player-layout-failure.png');print(e.state()[:12]);raise AssertionError((rule,viewer,side,actor,'label detached from identity'))
    labels[who]=label
  e.screenshot(f'player-layout-{rule}-viewer-{viewer}.png')
 assert len(set(panels.values()))==3
 # All wheel artwork survives the shifted draw, including under long names.
 if rule==0:
  for phase in range(0,32,2):
   e.poke(7,((24-phase)//2)&15);redraw();pixels=s.read(e,'framebuffer',240*160)
   for y in range(112):
    for x in range(128):
     value=rom[wheel+phase*128*112+y*128+x]
     if value!=rom[stage+(43+y)*240+32+x]:
      assert pixels[(43+y)*240+28+x]==value,(phase,x,y,'wheel overwritten')
 # Compare the exact badge pixels to a known total-score rendering.
 s.m['setmp'](e,2,2);redraw();badge=s.crop(e,1,63,44,10)
 if rule==0:
  s.put(e,'prefs',4,1);e.poke(9,1200);redraw()
  assert s.crop(e,1,63,44,10)==badge,'protected mode badge must show round points'
  s.put(e,'prefs',4,0);e.poke(9,12345)
 redraw()
 def indexed_name():
  pixels=s.read(e,'framebuffer',240*160)
  return b''.join(pixels[y*240+2:y*240+62] for y in range(51,59))
 normal=indexed_name();s.m['setmp'](e,6,1);redraw()
 assert indexed_name()==bytes(8 if p==15 else p for p in normal)
 e.screenshot(f'player-layout-{rule}-eliminated.png')
 s.m['setmp'](e,6,0)
 for mode in (2,3,4,7,8):
  e.poke(3,mode);e.poke(71,int(mode==3));redraw()
  e.screenshot(f'player-layout-{rule}-mode-{mode}.png')
 e.close();checks.append(dict(rule=rule,perspective_labels=True,viewer_footer=True,round_badge=True))
report=dict(rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),checks=checks,wheel_text_clearance_phases=32,wheel_rendered_phases=16)
(ROOT/'docs/verification/player-layout-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
