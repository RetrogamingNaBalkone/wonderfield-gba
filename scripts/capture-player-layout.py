"""Capture mGBA screenshots with explicit names, scores and scene RAM fixtures."""
import sys,struct,ctypes,importlib.util
from pathlib import Path
sys.path.insert(0,'scripts')
spec=importlib.util.spec_from_file_location('s','scripts/test-standings.py');s=importlib.util.module_from_spec(spec);spec.loader.exec_module(s)
for rule in range(3):
 for long in (False,True):
  e=s.frame(rule,[0]*3,[1,0,0] if rule==2 else [10000,20000,30000],0)
  for p,name in enumerate(('АЛЕКСАНДРА','КОНСТАНТИН','СВЯТОСЛАВА') if long else ('АЛЕКС','МАРИНА','ДЕНИС')):
   ctypes.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',len(name)+1)
   e.poke(9+p,12345+p*1000);s.put(e,'match',p,11145+p*1000)
  s.put(e,'prefs',2,0);s.write(e,'avatars',struct.pack('<3i',5,6,1))
  e.poke(3,6);
  scene=bytearray(s.read(e,'scene',180));struct.pack_into('<I',scene,4,struct.unpack('<I',s.read(e,'video_ticks',4))[0]);s.write(e,'scene',scene);e.poke(71,0);s.write(e,'message1',struct.pack('<I',0));s.write(e,'dirty',struct.pack('<I',1));e.run(30)
  e.screenshot(f'clean-layout-{rule}-{"long" if long else "short"}.png')
  e.close()
e=s.frame(2,[0,0,0],[1,0,0],0,humans=2)
s.put(e,'prefs',2,1);s.write(e,'mp_ai_index',struct.pack('<i',0));pool=bytearray(s.read(e,'opponent_pool',32));struct.pack_into('<i',pool,0,6);s.write(e,'opponent_pool',pool)
for p,name in ((0,'АЛЕКСАНДРА'),(2,'ДЕНИС')):
 ctypes.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',len(name)+1)
for p in range(3):e.poke(9+p,12345+p*1000);s.put(e,'match',6+p,p)
e.poke(3,6);e.poke(71,0);s.write(e,'message1',struct.pack('<I',0))
scene=bytearray(s.read(e,'scene',180));struct.pack_into('<I',scene,4,struct.unpack('<I',s.read(e,'video_ticks',4))[0]);s.write(e,'scene',scene)
s.write(e,'dirty',struct.pack('<I',1));e.run(30);e.screenshot('clean-layout-fr-bok.png');e.close()
