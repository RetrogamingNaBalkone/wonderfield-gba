"""Measure event clocks against the saved pre-optimization ROM."""
import ctypes as c,json,struct
from emulator import Emulator,ROOT


def measure(rom_path=None,elf_path=None):
 e=Emulator(rom_path,elf_path);e.run(220)
 def read(name,off=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+off,4))[0]
 def write(name,value,off=0):c.memmove(e.ram+e.sym[name]-0x02000000+off,struct.pack('<I',value&0xffffffff),4)
 def fixture():
  e.run(12)
  for i in range(20):e.poke(18+i,0)
  for i in range(32):e.poke(38+i,0)
  for i,v in {2:42,3:1,4:0,5:2,6:0,7:12,9:0,10:0,11:100,12:0,13:1,70:0,71:0,72:0,74:1,75:1,76:0,79:0,81:1,82:0}.items():e.poke(i,v)
  write('message1',0);write('scene',0,168);write('dirty',1);e.run(30)
 def sector(index,player=2):
  fixture()
  for i,v in {3:2,5:player,7:(index+1)&15,74:1,75:1}.items():e.poke(i,v)
  write('scene',0,152);write('scene',index,156);write('scene',read('video_ticks'),20)
  e.until(lambda s:s[3]!=2)
 results={}
 try:
  spins=[]
  for seed in (0,1,2,5,17,31):
   fixture();e.poke(2,seed);e.tap(8);start=read('scene',4);last=None;trace=[]
   while e.state()[3]==2:
    s=e.state();state=(s[7],read('scene',152),s[74],s[75])
    if state!=last:trace.append([read('video_ticks')-start,*state]);last=state
    e.run(1)
   spins.append(dict(seed=seed,vblanks=read('video_ticks')-start,trace=trace))
  results['spins']=spins
  reveals=[]
  for index in (3,0):
   sector(index);e.poke(70,1 if index==0 else 8);e.tap(8);start=read('scene',12);last=None;trace=[]
   while e.state()[3]==16:
    state=(read('scene',44),read('scene',48),sum(e.state()[18:38]))
    if state!=last:trace.append([read('video_ticks')-start,*state]);last=state
    e.run(1)
   reveals.append(dict(sector=index,vblanks=read('video_ticks')-start,trace=trace))
  results['reveals']=reveals
  # Use the same ordinary-letter line without the keyboard covering the face.
  sector(3);e.poke(71,0);start=read('scene',4);last=None;trace=[]
  for _ in range(240):
   phase=read('scene',172)
   if phase!=last:trace.append([read('video_ticks')-start,phase]);last=phase
   e.run(1)
  results['host_phases']=trace
  ai=[]
  fixture();e.poke(3,6);e.poke(5,0);e.poke(77,1);e.poke(78,0);e.tap(8);start=read('scene',4)
  e.until(lambda s:s[3]==2);ai.append(dict(event='turn',vblanks=read('video_ticks')-start))
  sector(3,0);start=read('scene',4);e.until(lambda s:s[3]==18);ai.append(dict(event='letter',vblanks=read('video_ticks')-start))
  fixture();e.poke(3,18);e.poke(5,0);e.poke(8,10);write('scene',8,144);write('scene',read('video_ticks'),4);start=read('scene',4)
  e.until(lambda s:s[3]!=18);ai.append(dict(event='answer',vblanks=read('video_ticks')-start))
  fixture();e.poke(3,18);e.poke(5,0);e.poke(8,10);write('scene',6,144);write('scene',read('video_ticks')-120,4)
  e.until(lambda s:s[3]==6);start=read('scene',4);e.until(lambda s:s[3]!=6);ai.append(dict(event='result',vblanks=read('video_ticks')-start))
  results['ai']=ai
  return results
 finally:e.close()


if __name__=='__main__':
 before=measure(ROOT/'build/performance-baseline/pole.gba',ROOT/'build/performance-baseline/pole.elf')
 after=measure()
 (ROOT/'build/qa/pacing-comparison.json').write_text(json.dumps(dict(before=before,after=after),indent=2))
 print(json.dumps(dict(before={k:([{x:v for x,v in row.items() if x!='trace'} for row in value] if k!='host_phases' else value) for k,value in before.items()},after={k:([{x:v for x,v in row.items() if x!='trace'} for row in value] if k!='host_phases' else value) for k,value in after.items()})))
