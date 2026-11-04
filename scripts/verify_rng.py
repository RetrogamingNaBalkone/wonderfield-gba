"""Real mGBA input/timer checks; fixtures never replace input entropy.

The seed arithmetic fixtures live in audit_rng.py. These checks exercise
actual timing, persistent boot seeds, held keys and replay/skip behavior.
"""
from emulator import Emulator, ROOT
import ctypes as c
import hashlib
import json
import struct

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
def read(e,name):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000,4))[0]
def fixture_turn(e):
 for index,value in ((3,1),(5,2),(6,0),(7,12),(81,1),(2,12345)):
  e.poke(index,value)
def result(e):return tuple(e.state()[i] for i in (7,8,2))

boots=[]
for delay in range(4,13):
 e=Emulator();e.run(delay);before=e.state();e.tap(8)
 check(f'early A after {delay} VBlank starts game',e.state()[3]==15)
 boots.append(dict(delay=delay,loop_before=before[1],word=e.state()[6],
                   rng=e.state()[2]&0xffffffff,entropy=read(e,'input_entropy')))
 e.close()
groups={frame:[b for b in boots if b['loop_before']==frame] for frame in {b['loop_before'] for b in boots}}
check('early inputs include multiple frames in the same old loop bucket',any(len(g)>1 for g in groups.values()))
check('different early input frames have distinct seeds within each loop bucket',
      all(len({b['rng'] for b in g})==len(g) for g in groups.values()))

# Cold launches with the same rapid input and the previous launch's SRAM.
# Preserve a valid legacy record table and unrelated save bytes throughout.
payload=bytearray([255]*32768)
payload[:4]=b'POL2'
payload[4:124]=bytes(120)
hash_value=2166136261
for byte in payload[4:124]:hash_value=((hash_value^byte)*16777619)&0xffffffff
struct.pack_into('<I',payload,124,hash_value)
launches=[]
for launch in range(12):
 e=Emulator();address=e.core.retro_get_memory_data(0)
 c.memmove(address,bytes(payload),len(payload));e.core.retro_reset();e.run(4);e.tap(8)
 check(f'persistent rapid boot {launch} starts',e.state()[3]==15)
 launches.append((e.state()[2],e.state()[6],tuple(e.state()[12:18])))
 saved=c.string_at(address,len(payload))
 check(f'boot {launch} preserves records and other save bytes',saved[:128]==payload[:128] and saved[140:]==payload[140:])
 count,inverse=struct.unpack_from('<II',saved,132)
 check(f'boot {launch} commits next counter',saved[128:132]==b'RNG\x01' and count==launch+1 and inverse==count^0xffffffff)
 check(f'boot {launch} loads legacy records',e.state()[85]==0 and read(e,'record_scores')==0)
 payload[:]=saved;e.close()
check('identical rapid input across cold boots uses distinct RNG states',len({v[0] for v in launches})==12)
check('identical rapid input across cold boots varies words',len({v[1] for v in launches})>1)
check('identical rapid input across cold boots varies opponents',len({v[2] for v in launches})>1)

for fill in (0,255):
 e=Emulator()
 e.core.retro_get_memory_size.argtypes=[c.c_uint];e.core.retro_get_memory_size.restype=c.c_size_t
 address=e.core.retro_get_memory_data(0);size=e.core.retro_get_memory_size(0)
 c.memset(address,fill,size);e.core.retro_reset();e.run(220)
 stored=c.string_at(address,size);e.tap(8)
 check(f'game starts with invalid SRAM filled with {fill}',e.state()[3]==15 and 0<=e.state()[6]<495 and read(e,'input_entropy')!=0)
 check(f'input seeding does not write SRAM filled with {fill}',c.string_at(address,size)==stored)
 e.close()

e=Emulator();e.run(220)
polls=read(e,'startup_input_polls');entropy=read(e,'input_entropy');e.run(1)
polls_per_frame=(read(e,'startup_input_polls')-polls)&0xffffffff
check('idle title polls buttons more than 100 times per frame',polls_per_frame>100)
check('frequent idle polling does not invent input entropy',read(e,'input_entropy')==entropy)
seed=e.state()[2];e.run(60)
check('idle title does not advance the game RNG',e.state()[2]==seed)
e.run(12,(8,));entropy=read(e,'input_entropy');e.run(60,(8,))
check('held A collects no repeated input edges',read(e,'input_entropy')==entropy)
check('holding startup A waits for release before choosing the game',e.state()[3]==0 and e.state()[6]==-1)
e.run(12)
check('releasing startup A starts the game',e.state()[3]==15)
polls=read(e,'startup_input_polls');e.run(2)
check('starting the game disables frequent polling',read(e,'startup_input_polls')==polls)
e.run(12)
fixture_turn(e);checkpoint=e.checkpoint();timings=[]
for delay in range(8):
 e.restore(checkpoint);e.run(delay)
 check(f'waiting {delay} VBlank before spin leaves draw state unchanged',e.state()[2]==12345)
 e.tap(8)
 check(f'timed human spin {delay} starts',e.state()[3]==2)
 timings.append(dict(delay=delay,rng=e.state()[2]&0xffffffff,entropy=read(e,'input_entropy'),
                     target=struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+156,4))[0]))
check('later human input timings change the RNG',len({t['rng'] for t in timings})==8)
check('timed human spins can select different sectors',len({t['target'] for t in timings})>1)

e.restore(checkpoint);e.tap(8);spin=e.checkpoint()
e.until(lambda s:s[3]!=2);natural=result(e)
for delay in (0,7,30,75):
 e.restore(spin);e.run(delay)
 check(f'skip test {delay} is still spinning',e.state()[3]==2)
 entropy=read(e,'input_entropy');e.tap(8)
 check(f'skip at {delay} captures its own input time',read(e,'input_entropy')!=entropy)
 check(f'skip at {delay} keeps the natural sector, value and RNG',e.state()[3]!=2 and result(e)==natural)

e.restore(checkpoint);e.tap(8);first=(e.state()[2],read(e,'input_entropy'))
e.restore(checkpoint);e.tap(8)
check('complete emulator replay remains deterministic',first==(e.state()[2],read(e,'input_entropy')))

# Ignored gameplay buttons still contribute timing for the next human draw.
e.restore(checkpoint);e.tap(11);fixture_turn(e);e.tap(8);with_input=e.state()[2]
e.restore(checkpoint);e.run(6);fixture_turn(e);e.tap(8)
check('additional input contributes to later RNG state',e.state()[2]!=with_input)
# Keep the press and next draw at the same frames; vary only release time.
e.restore(checkpoint);e.run(1,(11,));held=e.checkpoint();releases=[]
for duration in range(4):
 e.restore(held);e.run(duration,(11,));before=read(e,'input_entropy')
 seed=e.state()[2];e.run(1)
 check(f'release after {duration} frames contributes entropy',read(e,'input_entropy')!=before)
 check(f'release after {duration} frames does not advance active RNG',e.state()[2]==seed)
 e.run(4-duration);e.tap(8)
 releases.append(e.state()[2]&0xffffffff)
check('release timing alone changes the next spin RNG',len(set(releases))==4)
e.poke(3,10);e.poke(82,0);e.tap(8);e.run(120)
check('game over returns to the title',e.state()[3]==0)
polls=read(e,'startup_input_polls');e.run(1)
check('returning to title re-enables frequent polling',read(e,'startup_input_polls')>polls+100)
e.close()

holds=[]
for duration in (1,2,4,8):
 e=Emulator();e.run(220);e.run(duration,(8,))
 check(f'startup hold {duration} does not draw a word',e.state()[6]==-1)
 e.run(12)
 check(f'startup release after {duration} starts',e.state()[3]==15)
 holds.append(e.state()[2]);e.close()
check('startup hold duration changes initial game seed',len(set(holds))==len(holds))

# The original first candidate remains DOS-compatible; only an impending
# third equal award receives exactly one extra five-draw candidate.
from rng_reference import dos_spin
def candidate(seed,sector):
 def random_n(n):
  nonlocal seed
  seed=(seed*134775813+1)&0xffffffff
  return (seed>>16)%n
 limit=10+random_n(20);steps=0
 for divisor in (1,2,3,4):
  steps+=limit//divisor+1;limit=5+random_n(10)
 return (sector-(steps+1)//2)&15,seed
rom=(ROOT/'build/gba/pole.gba').read_bytes()
e=Emulator();e.run(220);e.tap(8)
wheel=struct.unpack_from('<16h',rom,e.sym['wheel_sectors']-0x08000000)
values=struct.unpack_from('<12h',rom,e.sym['sector_values']-0x08000000)
history=e.ram+e.sym['spin_history']-0x02000000
second_matches=0
for seed in range(1,65):
 first,first_seed=dos_spin(seed,12);value=values[wheel[first]-4]
 second,second_seed=candidate(first_seed,12)
 for count in (0,1,2):
  fixture_turn(e);c.memmove(history,struct.pack('<iiI',value,count,0),12)
  e.tap_seeded(8,seed)
  target=struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+156,4))[0]
  expected,expected_seed=(second,second_seed) if count==2 else (first,first_seed)
  check(f'award history {count}, seed {seed} selects expected candidate',target==expected and e.state()[2]&0xffffffff==expected_seed)
  check(f'award history {count}, seed {seed} rerolls at most once',struct.unpack('<I',c.string_at(history+8,4))[0]==(count==2))
 if values[wheel[second]-4]==value:second_matches+=1
check('one reroll can still accept a third equal award',second_matches>0)
fixture_turn(e);e.poke(5,0);c.memmove(history,bytes(12),12)
checkpoint=e.checkpoint();ai_seeds=[]
for delay in range(4):
 e.restore(checkpoint);e.run(delay);e.tap(8)
 check(f'AI spin delay {delay} starts',e.state()[3]==2)
 ai_seeds.append(e.state()[2])
check('timed input also changes AI spin seeds',len(set(ai_seeds))==4)
spin=e.checkpoint();e.until(lambda s:s[3]!=2);natural=result(e)
e.restore(spin);e.tap(8)
check('AI skip preserves sector award and RNG',result(e)==natural)
e.poke(3,17);e.poke(4,0)
ticks=read(e,'video_ticks')
c.memmove(e.ram+e.sym['scene']-0x02000000+12,struct.pack('<I',(ticks-40)&0xffffffff),4)
e.tap(8)
check('new round resets shared award history',struct.unpack('<i',c.string_at(history+4,4))[0]==0)
e.close()
e=Emulator();e.run(220);e.tap(3)
check('title START opens menu',e.state()[3]==23)
e.run(20,(8,))
check('menu game start also waits for A release',e.state()[3]==23 and e.state()[6]==-1)
e.run(12)
check('menu A release starts the game',e.state()[3]==15)
e.close()
e=Emulator();e.run(220);e.tap(8);e.run(12)
idle_entropy=read(e,'input_entropy');automatic=[]
for draw in range(2):
 fixture_turn(e);e.poke(5,0)
 ticks=read(e,'video_ticks')
 c.memmove(e.ram+e.sym['scene']-0x02000000+4,struct.pack('<I',(ticks-200)&0xffffffff),4)
 e.until(lambda s:s[3]==2)
 automatic.append((read(e,'input_seed_salt'),e.state()[2]))
 check(f'automatic AI draw {draw} needs no new input entropy',read(e,'input_entropy')==idle_entropy)
check('automatic AI draws do not reuse the same timing salt',automatic[0][0]!=automatic[1][0])
check('automatic AI draws mix identical starting RNG states differently',automatic[0][1]!=automatic[1][1])
e.close()
report=dict(status='passed',count=len(checks),checks=checks,
 rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),
 early_boots=boots,later_input_timings=timings,release_timing_rng=releases,startup_polls_per_frame=polls_per_frame,
 limitation='Identical complete emulator state and cycle-identical inputs remain reproducible; presses before the first input poll can coalesce.')
out=ROOT/'build/qa/rng-verification.json';out.parent.mkdir(exist_ok=True)
out.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(f'RNG checks passed: {len(checks)}')
print(json.dumps(boots,indent=2))
