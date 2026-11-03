"""AI spin/answer/chest/reveal chains driven by fast A, without seed fixtures.

The only gameplay fixtures assign human turns to AI and restart at round end.
All decisions between spins execute ROM code, retaining revealed/used letters.
Runs are counted only within the same round and for the same contestant.
"""
from emulator import Emulator,ROOT
from collections import Counter
import argparse,json,hashlib

p=argparse.ArgumentParser();p.add_argument('--build-dir',default='build/gba')
p.add_argument('--output',default='build/qa/rng-ai-sequences.json');args=p.parse_args()
build=ROOT/args.build_dir;e=Emulator(build/'pole.gba',build/'pole.elf');e.run(4);e.tap(8)
awards=Counter();states=set();plus_run=0;longest=0;pairs=triples=0;rounds=1
previous_player=None;rows=[]
for draw in range(2048):
 while e.state()[3]!=1:
  if e.state()[3]==9:
   e.poke(3,0);plus_run=0;previous_player=None;rounds+=1
  e.tap(8)
 if e.state()[5]==2:e.poke(5,0)
 player=e.state()[5]
 e.tap(8);assert e.state()[3]==2
 state=e.state()[2]&0xffffffff
 assert state not in states,'AI spin repeated RNG state'
 states.add(state);e.tap(8);assert e.state()[3]!=2
 value=e.state()[8];awards[value]+=1
 plus_run=(plus_run+1 if player==previous_player else 1) if value==100 else 0
 pairs+=plus_run>=2;triples+=plus_run>=3;longest=max(longest,plus_run)
 if plus_run>=2:rows.append(dict(draw=draw,player=player,run=plus_run,rng=state))
 previous_player=player;e.audio.clear()
e.close()
report=dict(status='passed',rom_sha256=hashlib.sha256((build/'pole.gba').read_bytes()).hexdigest(),
 spins=2048,rounds=rounds,award_counts=dict(awards),unique_spin_states=len(states),
 same_ai_plus_pairs=pairs,same_ai_plus_triples=triples,longest_plus_run=longest,
 repeated_plus=rows,limitation=__doc__)
(ROOT/args.output).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report))
