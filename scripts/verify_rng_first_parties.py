"""Compare first and later parties in one session after an explicitly blank save.

Human fixtures assign each spin to the human. AI fixtures assign human turns
to AI and otherwise execute real answers/reveals, stopping at the round end.
The next-party fixture returns to TITLE instead of playing a full three-round
game. No fixture replaces RNG, entropy, timers or wheel history. Input is
frame-granular, not independent random trials or physical absent-SRAM testing.
"""
from emulator import Emulator, ROOT
from collections import Counter
import argparse, ctypes as c, hashlib, json

p=argparse.ArgumentParser()
p.add_argument('--build-dir',default='build/gba')
p.add_argument('--output',default='build/qa/rng-first-parties.json')
args=p.parse_args();build=ROOT/args.build_dir;rows=[]
for kind in ('human','ai'):
 for delay in (4,5,6,8,12,20):
  for gap in (0,1,2):
   e=Emulator(build/'pole.gba',build/'pole.elf')
   e.core.retro_get_memory_size.argtypes=[c.c_uint]
   e.core.retro_get_memory_size.restype=c.c_size_t
   c.memset(e.core.retro_get_memory_data(0),255,e.core.retro_get_memory_size(0))
   e.core.retro_reset();e.run(delay)
   def tap():e.run(gap);e.tap(8)
   for party in range(3):
    if party:e.poke(3,0)
    tap();assert e.state()[3]==15
    initial=e.state();awards=[];seeds=[]
    for draw in range(24):
     if kind=='human':
      for i,v in ((3,1),(5,2),(81,1)):e.poke(i,v)
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
     awards.append(e.state()[8]);e.audio.clear()
    assert len(set(seeds))==len(seeds)
    rows.append(dict(kind=kind,delay=delay,gap=gap,party=party,word=initial[6],
                     awards=awards,rng=seeds,x2_count=awards.count(202),
                     x2_pairs=sum(a==b==202 for a,b in zip(awards,awards[1:]))))
   e.close()
 print(kind,'completed',flush=True)
summary=[]
for kind in ('human','ai'):
 for party in range(3):
  selected=[r for r in rows if r['kind']==kind and r['party']==party]
  counts=Counter(v for r in selected for v in r['awards'])
  summary.append(dict(kind=kind,party=party,spins=sum(counts.values()),
                      award_counts=dict(counts),x2_pairs=sum(r['x2_pairs'] for r in selected)))
report=dict(status='passed',rom_sha256=hashlib.sha256((build/'pole.gba').read_bytes()).hexdigest(),
            summary=summary,samples=rows,limitation=__doc__)
(ROOT/args.output).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(summary),flush=True)
