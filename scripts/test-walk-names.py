"""Replay identical mGBA states with/without names to check walking visibility."""
import ctypes as c
import hashlib
import importlib.util
import json
import struct
from emulator import ROOT
spec=importlib.util.spec_from_file_location('standings',ROOT/'scripts/test-standings.py')
s=importlib.util.module_from_spec(spec);spec.loader.exec_module(s)

def setup(sector,age):
 e=s.frame(0,[0]*3,[100,200,300],2)
 for p,name in enumerate(('АЛЕКСАНДРА','КОНСТАНТИН','СВЯТОСЛАВА')):
  c.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name.encode('cp866')+b'\0',11)
 e.poke(3,16);e.poke(5,2);e.poke(8,sector);e.poke(79,0)
 s.write(e,'message1',struct.pack('<I',0))
 scene=bytearray(s.read(e,'scene',180));now=struct.unpack('<I',s.read(e,'video_ticks',4))[0]
 for offset,value in ((12,now-age),(16,now),(36,1),(40,0),(44,32),(48,0),(148,300)):
  struct.pack_into('<I',scene,offset,value&0xffffffff)
 scene[64:144]=b'\0'*80
 s.write(e,'scene',scene);s.write(e,'dirty',struct.pack('<I',1))
 return e

def compare(e,visible,label):
 checkpoint=e.checkpoint();e.run(30)
 names=[s.crop(e,x,46,80,8) for x in (1,109)]
 footer=s.crop(e,0,150,240,10)
 badges=[s.crop(e,x,63,44,10) for x in (1,141)]
 e.screenshot(f'walk-names-{label}.png')
 e.restore(checkpoint)
 for p in (0,1):c.memset(e.ram+e.sym['mp']-0x02000000+28+11*p,0,11)
 s.write(e,'dirty',struct.pack('<I',1));e.run(30)
 empty=[s.crop(e,x,46,80,8) for x in (1,109)]
 assert all((a!=b)==visible for a,b in zip(names,empty)),(label,'name visibility')
 assert footer==s.crop(e,0,150,240,10),(label,'own HUD changed')
 assert badges==[s.crop(e,x,63,44,10) for x in (1,141)]
 e.restore(checkpoint)

checks=[]
for sector,age,visible,label in ((25,0,True,'intro'),(25,180,False,'walking'),(100,0,False,'plus')):
 e=setup(sector,age);compare(e,visible,label)
 s.tap(e,8);assert e.state()[3]!=16
 s.write(e,'message1',struct.pack('<I',0));s.write(e,'dirty',struct.pack('<I',1))
 compare(e,True,label+'-skip-restored');e.close()
 checks.append(dict(case=label,visible=visible,skip_restores=True))
e=setup(25,0)
e.run(120);assert e.state()[3]==16
compare(e,True,'before-walk')
e.run(100);assert e.state()[3]==16
compare(e,False,'after-start')
e.until(lambda state:state[3]!=16,2000)
s.write(e,'message1',struct.pack('<I',0));s.write(e,'dirty',struct.pack('<I',1))
compare(e,True,'natural-finish');e.close()
checks.append(dict(natural_intro_walk_finish=True))
report=dict(rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),checks=checks)
(ROOT/'docs/verification/walk-names-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
