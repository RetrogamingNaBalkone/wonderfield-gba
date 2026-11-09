"""ROM integration checks for scoring, match outcomes and repeated shootouts."""
import ctypes as c
import hashlib
import json
import runpy
import struct
from emulator import Emulator, ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
tap,read,write=m['tap'],m['read'],m['write']
WORDS=json.loads((ROOT/'assets/words-expanded.json').read_text())

def ints(e,name,n):return list(struct.unpack('<'+'i'*n,read(e,name,n*4)))
def put(e,name,index,value):
 data=bytearray(read(e,name,64 if name=='match' else 24));struct.pack_into('<i',data,index*4,value);write(e,name,data)
def start(rule=0,rounds=3,humans=3):
 e=Emulator();m['options'](e,humans)
 put(e,'prefs',4,rule);put(e,'prefs',5,rounds)
 tap(e,8)
 for _ in range(humans):m['accept_name'](e)
 assert e.state()[3]==15
 return e

def finish(e,p=2,solved=True):
 # A completed answer enters the actual answer-check and round-end handlers.
 e.poke(5,p);e.poke(3,5)
 if solved and p==1 and m['mp'](e)[0]==2:
  e.poke(79,1);e.poke(3,9);e.run(20)
 elif solved:
  word=WORDS[e.state()[6]]['word'].encode('cp866')
  c.memmove(e.ramgame+88*4,word+b'\0',len(word)+1);e.poke(80,len(word));tap(e,8)
 else:
  m['setmp'](e,6,7);e.poke(79,0);e.poke(3,35);tap(e,8)
 assert e.state()[3]==36,e.state()[:12]
 return ints(e,'match',16)

def advance(e):
 tap(e,8)
 if e.state()[3]==17:e.run(620)
 assert e.state()[3]==15,e.state()[:12]

def sector(e,value):
 rom=(ROOT/'build/gba/pole.gba').read_bytes()
 def table(name,n):return struct.unpack_from('<'+'h'*n,rom,e.sym[name]-0x08000000)
 values=table('sector_values',12);sectors=table('wheel_sectors',16)
 selected=next(i for i,s in enumerate(sectors) if values[s-4]==value)
 scene=bytearray(read(e,'scene',180));struct.pack_into('<i',scene,156,selected);write(e,'scene',scene)
 e.poke(3,2);tap(e,8)

checks=[]
e=Emulator();m['options'](e,3)
assert ints(e,'prefs',6)[4:]==[0,3]
m['select_option'](e,4)
for _ in range(2):tap(e,6)
assert ints(e,'prefs',6)[5]==1
tap(e,6);assert ints(e,'prefs',6)[5]==8
tap(e,7);assert ints(e,'prefs',6)[5]==1
m['select_option'](e,3)
for expected in (1,2,0):tap(e,8);assert ints(e,'prefs',6)[4]==expected
e.close();checks.append({'menu_defaults_round_bounds_and_three_modes':True})

for rule in range(3):
 e=start(rule);e.poke(5,2);e.poke(11,450);put(e,'match',2,330);put(e,'match',5,330);put(e,'match',8,2)
 sector(e,-1)
 assert e.state()[11]==(330 if rule==0 else 0),e.state()[9:12]
 assert ints(e,'match',16)[8]==2
 e.close()
 for factor in (2,4):
  e=start(rule);e.poke(5,2);e.poke(11,450);put(e,'match',2,330);put(e,'match',5,330)
  e.poke(3,3);e.poke(8,200+factor)
  word=WORDS[e.state()[6]]['word'].encode('cp866');e.poke(70,word[0]-128)
  tap(e,8);tap(e,8);e.run(30)
  assert e.state()[11]==(330+120*factor if rule==0 else 450*factor),e.state()[9:12]
  e.close()
 checks.append({'rule':rule,'bankrupt_and_multipliers':True})
# Settle once, protect the completed score without adding it twice, restore roster.
e=start();e.poke(11,450);m['setmp'](e,6,1)
a=finish(e);assert a[8]==1 and a[2]==450
for _ in range(3):e.run(60)
assert ints(e,'match',16)==a and e.state()[11]==450
tap(e,3);assert e.state()[3]==23
e.run(60);tap(e,3);assert e.state()[3]==36 and ints(e,'match',16)==a
advance(e);assert e.state()[5]==2 and m['mp'](e)[6]==0 and e.state()[11]==450
sector(e,-1);assert e.state()[11]==450
e.close();checks.append({'settlement_once_and_return':True})
# Last-round winner is not necessarily match winner; no bonus for solving.
for rule in (0,1,2):
 e=start(rule,1);e.poke(9,900);e.poke(11,120)
 if rule==2:put(e,'match',6,1)
 a=finish(e,2);assert a[13]==0 and e.state()[11]==120
 records=read(e,'record_names',88)+read(e,'record_scores',32)
 sram=e.core.retro_get_memory_data(0);before=c.string_at(sram,128)
 tap(e,8);assert e.state()[3]==19 and e.state()[5]==0
 for _ in range(4):tap(e,8)
 assert e.state()[3]==0 and records==read(e,'record_names',88)+read(e,'record_scores',32)
 assert before==c.string_at(sram,128)
 e.close()
checks.append({'winner_by_standings_and_no_sram':True})
# Tie only between leaders; repeat after elimination, never select by shootout points.
for rule in (0,1,2):
 e=start(rule,1);e.poke(9,500);e.poke(11,500);e.poke(10,10000 if rule==2 else 100)
 if rule==2:put(e,'match',6,1)
 a=finish(e,2);assert a[14]==1 and a[10]==5,a
 first=e.state()[6];advance(e);assert ints(e,'match',16)[9]==1 and e.state()[4]==0
 assert e.state()[5]==2 and m['mp'](e)[6]==2 and e.state()[6]!=first
 second=e.state()[6];a=finish(e,solved=False);assert a[14]==1 and a[10]==5
 advance(e);assert e.state()[6] not in (first,second) and m['mp'](e)[6]==2
 e.poke(9,50000);e.poke(11,510);a=finish(e,2);assert a[13]==2 and a[14]==2
 e.screenshot(f'match-shootout-{rule}.png');e.close()
checks.append({'leader_subset_repeat_and_word_wins_shootout':True})
# Stable order starts with player two when player one is excluded.
e=start(0,1);e.poke(9,500);e.poke(10,500);finish(e,2);advance(e)
assert e.state()[5]==0 and m['mp'](e)[6]==4
e.close()
# Strict early win: a possible tie is not enough.
for wins,early in ((1,False),(2,True)):
 e=start(2,3);e.poke(4,1);put(e,'match',8,wins-1)
 a=finish(e,2);assert (a[14]==2)==early,a
 e.close()
# AI is stable, starts at zero, earns wins and can finish early.
e=start(2,3,2);ai=read(e,'opponent_pool',32);assert e.state()[9:12]==(0,0,0)
finish(e,1);advance(e);assert read(e,'opponent_pool',32)==ai and ints(e,'match',16)[7]==1 and e.state()[10]==0
finish(e,1);assert ints(e,'match',16)[13]==1
e.screenshot('match-ai-early-win.png');e.close()
e=start(0,3,2);ai=read(e,'opponent_pool',32);index=read(e,'mp_ai_index',4)
finish(e,2);advance(e)
assert read(e,'opponent_pool',32)==ai and read(e,'mp_ai_index',4)==index and e.state()[10]==0
e.close()
checks.append({'starting_order_strict_early_finish_fixed_ai':True})
# Last letter, including Plus, is a round win, with no solve bonus.
for value in (100,25):
 e=start();word=WORDS[e.state()[6]]['word'].encode('cp866');letter=word[0]
 for i,ch in enumerate(word):e.poke(18+i,int(ch!=letter))
 e.poke(5,2);e.poke(3,3);e.poke(8,value);e.poke(70,letter-128)
 tap(e,8);tap(e,8);e.run(30)
 assert e.state()[3]==36 and ints(e,'match',16)[8]==1
 assert e.state()[11]==(0 if value==100 else word.count(letter)*25)
 e.close()
checks.append({'last_letter_and_plus_win':True})
# Ordinary all-eliminated round is consumed, awards nobody a win, preserves points.
e=start(2,3);e.poke(11,500);a=finish(e,solved=False)
assert a[6:9]==[0,0,0] and a[12]==-1 and a[14]==0
advance(e);assert e.state()[4]==1 and e.state()[11]==500 and m['mp'](e)[6]==0
e.close();checks.append({'all_eliminated_round':True})
# Three-way tie; risk modes still play all scheduled rounds despite a large lead.
e=start(0,1);a=finish(e,solved=False);assert a[10]==7 and a[14]==1
advance(e);assert m['mp'](e)[6]==0 and e.state()[5]==2
e.close()
for rule in (0,1):
 e=start(rule,8);e.poke(11,1000000);a=finish(e);assert a[14]==0
 e.close()
# Standings ties on wins resolve by the cumulative score without a shootout.
e=start(2,1);put(e,'match',6,1);e.poke(9,100);e.poke(11,200)
a=finish(e);assert a[13]==2 and a[14]==2
e.close()
# AI receives the same third-letter chest opportunity; awarded points persist.
e=start(0,3,2);e.poke(3,6);e.poke(77,1);e.poke(78,1);e.poke(72,3)
tap(e,8);assert e.state()[3]==6 and e.state()[77]==8
assert e.state()[72]==0
e.close()
# Very long totals cannot wrap negative. Every digit remains in its own field.
e=start(1);e.poke(5,2);e.poke(11,2147483640);e.poke(3,3);e.poke(8,25)
e.poke(70,WORDS[e.state()[6]]['word'].encode('cp866')[0]-128)
tap(e,8);tap(e,8);assert e.state()[11]==2147483647
e.close()
for rule in range(3):
 e=start(rule);e.run(1400)
 for p in range(3):
  name=('АБВГДЕЖЗИЙ').encode('cp866')+b'\0'
  c.memmove(e.ram+e.sym['mp']-0x02000000+28+11*p,name,11)
  e.poke(9+p,12345);put(e,'match',p,11145);put(e,'match',6+p,2)
 write(e,'dirty',struct.pack('<i',1));e.run(30);e.screenshot(f'match-panel-{rule}.png')
 if rule==1:
  put(e,'match',5,50000);e.poke(11,0);finish(e);e.screenshot('match-negative-change.png')
 e.close()
checks.append({'three_way_tie_no_early_points_ai_chest_overflow_and_panels':True})
report={'rom_sha256':hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),'checks':checks}
(ROOT/'docs/verification/match-rules-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
