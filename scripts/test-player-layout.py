"""mGBA checks for the reviewed native-font layout and viewer-owned HUD."""
import ctypes as c
import hashlib
import importlib.util
import json
import struct
from emulator import ROOT
spec=importlib.util.spec_from_file_location('standings',ROOT/'scripts/test-standings.py')
s=importlib.util.module_from_spec(spec);spec.loader.exec_module(s)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
checks=[]
for rule in range(3):
 e=s.frame(rule,[0,0,0],[1,0,0] if rule==2 else [10000,20000,30000],0)
 names=['АЛЕКСАНДРА','КОНСТАНТИН','СВЯТОСЛАВА']
 for p,name in enumerate(names):
  c.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',11)
  e.poke(9+p,12345+p*10000);s.put(e,'match',p,11145+p*10000)
 e.poke(3,6);e.poke(71,0);s.write(e,'message1',struct.pack('<I',0))
 def redraw():
  scene=bytearray(s.read(e,'scene',180));struct.pack_into('<I',scene,4,struct.unpack('<I',s.read(e,'video_ticks',4))[0]);s.write(e,'scene',scene)
  s.write(e,'dirty',struct.pack('<I',1));e.run(30)
 def check_name(side,who,color):
  x=109 if side else 1;pixels=s.read(e,'framebuffer',240*160);font=e.sym['font8']-0x08000000
  for k,ch in enumerate(names[who].encode('cp866')):
   for y in range(8):
    for col in range(8):
     if rom[font+ch*8+y]&(128>>col):assert pixels[(46+y)*240+x+k*8+col]==color,(rule,who,'native name glyph')
 panels={}
 for viewer in (2,0,1):
  s.m['setmp'](e,2,viewer)
  for actor in (2,0,1):
   e.poke(5,actor);redraw()
   panel=s.crop(e,0,150,240,10)
   if viewer in panels:assert panel==panels[viewer],(rule,viewer,'actor changed footer')
   panels[viewer]=panel
   for side in range(2):check_name(side,(viewer+side+1)%3,7)
  e.screenshot(f'player-layout-{rule}-viewer-{viewer}.png')
 assert len(set(panels.values()))==3
 s.m['setmp'](e,2,2);redraw();badge=s.crop(e,1,63,44,10)
 if rule==0:
  s.put(e,'prefs',4,1);e.poke(9,1200);redraw()
  assert s.crop(e,1,63,44,10)==badge,'protected badge must show round points'
  s.put(e,'prefs',4,0);e.poke(9,12345)
 s.m['setmp'](e,6,1);redraw();check_name(0,0,8)
 e.screenshot(f'player-layout-{rule}-eliminated.png')
 s.m['setmp'](e,6,0)
 for mode in (2,3,4,7,8):
  e.poke(3,mode);e.poke(71,int(mode==3));redraw()
  e.screenshot(f'player-layout-{rule}-mode-{mode}.png')
 e.close();checks.append(dict(rule=rule,native_font=True,perspective_names=True,viewer_hud=True,round_badge=True))
report=dict(rom_sha256=hashlib.sha256(rom).hexdigest(),checks=checks)
(ROOT/'docs/verification/player-layout-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
