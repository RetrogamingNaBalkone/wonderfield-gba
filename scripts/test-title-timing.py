"""Check the title's real rendered timeline and input before prompts appear."""
import hashlib,json,runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
read=m['read'];tap=m['tap']
def integer(e,name):return struct.unpack('<I',read(e,name,4))[0]
def drawn_age(e):
 scene=struct.unpack('<8I',read(e,'scene',32))
 return (scene[2]-scene[6])&0xffffffff
def displayed(e):
 palette=struct.unpack_from('<16H',(ROOT/'build/gba/pole.gba').read_bytes(),e.sym['palette']-0x08000000)
 pixels=[]
 for (v,) in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  pixels.append(r|(g<<5)|(b<<10))
 return pixels,palette[1]
checks=[];e=Emulator()
for threshold in (6,18,24,36):
 for _ in range(100):
  e.run(1)
  age=(integer(e,'video_ticks')-struct.unpack('<8I',read(e,'scene',32))[6])&0xffffffff
  pixels,blue=displayed(e)
  logo=pixels[23*240:120*240].count(blue)
  prompt=pixels[139*240:147*240].count(blue)
  if threshold<=age<100 and (threshold<24 or (logo if threshold==24 else prompt)):break
 else:raise AssertionError('Title stage never displayed')
 assert bool(logo)==(threshold>=24),(age,logo)
 assert bool(prompt)==(threshold>=36),(age,prompt)
 assert age<=threshold+8,(threshold,age)
 e.screenshot(f'title-timing-{threshold}.png')
 checks.append({'stage':threshold,'displayed_age':age,'logo':bool(logo),'prompt':bool(prompt)})
ready=e.raw
# A normal game-over return must immediately draw the complete title.
e.poke(3,10);e.poke(82,0);tap(e,8)
assert e.state()[3]==0 and drawn_age(e)>=36
assert e.raw==ready
e.screenshot('title-return-ready.png');e.close()
for button,target in ((8,26),(3,23)):
 e=Emulator()
 for _ in range(20):
  e.run(1)
  if integer(e,'rendered_frames'):break
 assert drawn_age(e)<24
 e.run(2,(button,));e.run(8)
 assert e.state()[3]==target,(button,e.state()[:12])
 e.close()
report={'rom_sha256':hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),'timeline':checks,'immediate_complete_return':True,'early_A_and_START':True}
(ROOT/'docs/verification/title-timing-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
