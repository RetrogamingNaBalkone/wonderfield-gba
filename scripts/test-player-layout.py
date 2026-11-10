"""mGBA checks for portrait-bound labels, at-risk badges and viewer-owned footer."""
import ctypes as c
import hashlib
import importlib.util
import json
import struct
from emulator import ROOT
spec=importlib.util.spec_from_file_location('standings',ROOT/'scripts/test-standings.py')
s=importlib.util.module_from_spec(spec);spec.loader.exec_module(s)
checks=[]
for rule in range(3):
 e=s.frame(rule,[0,0,0],[1,0,0] if rule==2 else [10000,20000,30000],0)
 for p,name in enumerate(('АЛЕКСАНДРА','КОНСТАНТИН','СВЯТОСЛАВА')):
  c.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',11)
  e.poke(9+p,12345+p*10000);s.put(e,'match',p,11145+p*10000)
 e.poke(3,1);e.poke(71,0);s.write(e,'message1',struct.pack('<I',0))
 def redraw():s.write(e,'dirty',struct.pack('<I',1));e.run(30)
 labels={};panels={}
 for viewer in (2,0,1):
  s.m['setmp'](e,2,viewer)
  for actor in (2,0,1):
   e.poke(5,actor);redraw()
   panel=s.crop(e,0,144,240,16)
   if viewer in panels:assert panel==panels[viewer],(rule,viewer,'actor changed footer')
   panels[viewer]=panel
   for side,x in enumerate((0,105)):
    who=(viewer+side+1)%3;label=s.crop(e,x,112,80,8 if rule==1 else 16)
    if who in labels and label!=labels[who]:
     e.screenshot('player-layout-failure.png');print(e.state()[:12]);raise AssertionError((rule,viewer,side,actor,'label detached from identity'))
    labels[who]=label
  e.screenshot(f'player-layout-{rule}-viewer-{viewer}.png')
 assert len(set(panels.values()))==3
 # Compare the exact badge pixels to a known total-score rendering.
 s.m['setmp'](e,2,2);redraw();badge=s.crop(e,1,73,44,10)
 if rule==0:
  s.put(e,'prefs',4,1);e.poke(9,1200);redraw()
  assert s.crop(e,1,73,44,10)==badge,'protected mode badge must show round points'
  s.put(e,'prefs',4,0);e.poke(9,12345)
 redraw()
 def indexed_name():
  pixels=s.read(e,'framebuffer',240*160)
  return b''.join(pixels[y*240:y*240+80] for y in range(112,120))
 normal=indexed_name();s.m['setmp'](e,6,1);redraw()
 assert indexed_name()==bytes(8 if p==0 else p for p in normal)
 e.screenshot(f'player-layout-{rule}-eliminated.png')
 s.m['setmp'](e,6,0)
 for mode in (2,3,4,7,8):
  e.poke(3,mode);e.poke(71,int(mode==3));redraw()
  e.screenshot(f'player-layout-{rule}-mode-{mode}.png')
 e.close();checks.append(dict(rule=rule,perspective_labels=True,viewer_footer=True,round_badge=True))
report=dict(rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),checks=checks)
(ROOT/'docs/verification/player-layout-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
