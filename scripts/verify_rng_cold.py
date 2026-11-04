"""First-round fast-A samples, resetting SRAM to FF before EVERY cold boot.

Human samples force 16 successive human turns. AI samples convert human turns
to AI, then run actual answers/reveals until the first round ends (64 spin cap).
Neither fixture changes RNG, entropy, timers, or the previous wheel position.
Libretro input is frame-granular; this does not simulate sub-frame human timing.
"""
from emulator import Emulator, ROOT
from collections import Counter
import argparse, ctypes as c, hashlib, json

p=argparse.ArgumentParser()
p.add_argument('--build-dir',default='build/gba')
p.add_argument('--output',default='build/qa/rng-cold.json')
args=p.parse_args();build=ROOT/args.build_dir

def sample(kind,boot_delay,gap):
 e=Emulator(build/'pole.gba',build/'pole.elf')
 e.core.retro_get_memory_size.argtypes=[c.c_uint]
 e.core.retro_get_memory_size.restype=c.c_size_t
 c.memset(e.core.retro_get_memory_data(0),255,e.core.retro_get_memory_size(0))
 e.core.retro_reset();e.run(boot_delay);e.tap(8)
 assert e.state()[3]==15
 initial=e.state();values=[];seeds=[];sectors=[]
 def tap():e.run(gap);e.tap(8)
 for draw in range(16 if kind=='human' else 64):
  if kind=='human':
   for index,value in ((3,1),(5,2),(81,1)):e.poke(index,value)
  else:
   for _ in range(1000):
    if e.state()[3] in (1,9):break
    tap()
   else:raise AssertionError('AI first round stalled')
   if e.state()[3]==9:break
   if e.state()[5]==2:e.poke(5,0)
  tap();assert e.state()[3]==2
  seeds.append(e.state()[2]&0xffffffff)
  tap();assert e.state()[3]!=2
  values.append(e.state()[8]);sectors.append(e.state()[7]);e.audio.clear()
 assert len(seeds)==len(set(seeds))
 e.close();runs=Counter();previous=None;length=0
 for value in values:
  length=length+1 if value==previous else 1
  runs[value]=max(runs[value],length);previous=value
 return dict(kind=kind,boot_delay=boot_delay,gap=gap,word=initial[6],
             opponents=initial[12:18],values=values,sectors=sectors,rng=seeds,
             longest=dict(runs),pairs=max(0,len(values)-1),
             repeats=sum(a==b for a,b in zip(values,values[1:])))

rows=[]
for kind in ('human','ai'):
 for boot_delay in (4,5,6,8,12,20):
  for gap in (0,1,2):rows.append(sample(kind,boot_delay,gap))
 print(kind,dict(spins=sum(len(r['values']) for r in rows if r['kind']==kind),
                repeats=sum(r['repeats'] for r in rows if r['kind']==kind)),flush=True)
replay=sample('human',4,0)
assert replay==rows[0], 'same blank SRAM and identical input must replay'
report=dict(status='passed',rom_sha256=hashlib.sha256((build/'pole.gba').read_bytes()).hexdigest(),
            identical_blank_save_replay=True,samples=rows,limitation=__doc__)
(ROOT/args.output).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
