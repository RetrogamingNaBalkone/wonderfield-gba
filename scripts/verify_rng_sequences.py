"""Fast-A sequences with real input entropy and no injected RNG state.

Fixtures shorten gameplay by entering the next human turn / credits;
they preserve RNG, entropy, clocks, previous sector and selected records.
These are deterministic scenario samples, not independent random trials.
"""
from emulator import Emulator, ROOT
from collections import Counter
import ctypes as c
import hashlib
import json
import struct
import argparse

parser=argparse.ArgumentParser()
parser.add_argument('--build-dir',default='build/gba')
parser.add_argument('--output',default='build/qa/rng-sequences.json')
parser.add_argument('--parties',type=int,default=128)
parser.add_argument('--spins-per-party',type=int,default=4)
args=parser.parse_args()
build=ROOT/args.build_dir

words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))
furniture=words[494]['topic']
assert furniture=='\u041c\u0415\u0411\u0415\u041b\u042c'
def peek(e,name,offset=0):
 return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+offset,4))[0]
def poke(e,name,offset,value):
 c.memmove(e.ram+e.sym[name]-0x02000000+offset,struct.pack('<I',value&0xffffffff),4)

samples=[]
for delay in (0,1,2,4,8):
 e=Emulator(build/'pole.gba',build/'pole.elf');e.run(4);e.tap(8)
 topics=Counter();round_repeats=0;seeds=[];spins=[];awards=[];same_sector=same_award=0
 value_pairs=Counter();value_triples=Counter();value_longest=Counter()
 for party in range(args.parties):
  if party:
   e.poke(3,0);e.run(delay);e.tap(8)
  selected=[e.state()[6]]
  for round_no in (1,2):
   e.poke(3,17)  # Credits -> actual new_round(), preserving round/selected_words.
   poke(e,'scene',12,peek(e,'video_ticks')-40)
   e.run(delay);e.tap(8)
   assert e.state()[4]==round_no and e.state()[3]==15
   selected.append(e.state()[6]);seeds.append(e.state()[2]&0xffffffff)
  assert len(set(selected))==3,selected
  ts=[words[i]['topic'] for i in selected];topics.update(ts)
  round_repeats+=sum(a==b for a,b in zip(ts,ts[1:]))
  value_run=0;previous_value=None
  for spin in range(args.spins_per_party):
   for i,v in ((3,1),(5,2),(81,1)):e.poke(i,v)
   e.run(delay);e.tap(8)
   assert e.state()[3]==2
   seeds.append(e.state()[2]&0xffffffff)
   e.tap(8);assert e.state()[3]!=2
   if spin:
    same_sector+=spins[-1]==e.state()[7]
    same_award+=awards[-1]==e.state()[8]
   spins.append(e.state()[7]);awards.append(e.state()[8])
   value=awards[-1];value_run=value_run+1 if value==previous_value else 1
   value_pairs[value]+=value_run>=2;value_triples[value]+=value_run>=3
   value_longest[value]=max(value_longest[value],value_run);previous_value=value
  e.audio.clear()
 assert len(set(seeds))==len(seeds),'repeated RNG state in fast-A sequence'
 samples.append(dict(delay=delay,parties=args.parties,rounds=args.parties*3,
  furniture=topics[furniture],adjacent_topic_repeats=round_repeats,topic_pairs=args.parties*2,
  spins=len(spins),spin_pairs=args.parties*(args.spins_per_party-1),same_sector=same_sector,same_award=same_award,
  consecutive_awards=dict(pairs=dict(value_pairs),triples=dict(value_triples),longest=dict(value_longest)),
  unique_rng_states=len(set(seeds)),observed_rng_states=len(seeds)))
 e.close()
 print(samples[-1],flush=True)
report=dict(status='passed',rom_sha256=hashlib.sha256((build/'pole.gba').read_bytes()).hexdigest(),
 samples=samples,topic_records=dict(Counter(w['topic'] for w in words)),
 limitation=__doc__)
out=ROOT/args.output
out.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
