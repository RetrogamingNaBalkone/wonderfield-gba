"""Integration checks execute the cartridge in mGBA, including audio IRQs.

Normal keypad playthrough and explicitly labelled RAM fixtures are separate.
Fixtures reach rare sectors deterministically without replacing console code.
"""
from emulator import Emulator,ROOT
import json,ctypes as c,struct,hashlib,wave
checks=[]
def check(name,condition):
 assert condition,name
 checks.append(name)
words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))
sprites=json.loads((ROOT/'assets/sprites.json').read_text())
originals=json.loads((ROOT/'analysis/originals.json').read_text())
for name,entry in originals.items():check('original unchanged: '+name,hashlib.sha256((ROOT/'originals/Wonderfield'/name).read_bytes()).hexdigest()==entry['sha256'])
check('495 original records',len(words)==495)
check('57 decoded images',len(sprites)==57)
check('all words fit board',all(1<=len(x['word'])<=20 for x in words))
check('all glyphs retained',sum((ROOT/f'assets/font-{h}.bin').stat().st_size for h in (6,8,14))==7168)
check('font bytes are lossless',b''.join((ROOT/f'assets/font-{h}.bin').read_bytes() for h in (6,8,14))==(ROOT/'originals/Wonderfield/POLE.FNT').read_bytes())
e=Emulator();e.run(220);e.screenshot('title.png');check('cartridge boots',e.state()[0]==0x504f4c45 and e.state()[3]==0)
def skip_intro():
 for i in range(12):
  if e.state()[3]==17:
   e.run(50);e.screenshot('credits.png');e.tap(8);e.run(10);continue
  if e.state()[3]!=15:return
  e.tap(8)
 e.run(30)
e.tap(2);e.run(30);e.screenshot('help.png');check('help opens',e.state()[3]==11);e.tap(0);check('help returns',e.state()[3]==0)
e.tap(8);e.run(40);check('DOS player introduction restored',e.state()[3]==15);e.screenshot('introduction.png');skip_intro();e.screenshot('turn.png');check('first round human turn',e.state()[3:6]==(1,0,2))
e.tap(8);e.until(lambda s:s[3] not in (1,2));e.run(30);check('wheel stops',0<=e.state()[7]<16)
# Selected seed may produce a special sector; use deterministic rare-branch fixtures below.
def fixture_sector(sector,score=100,streak=0):
 for i in range(20):e.poke(18+i,0)
 for i in range(32):e.poke(38+i,0)
 for i,v in {3:2,5:2,6:0,7:(sector+1)%16,11:score,72:streak,74:1,75:1,76:0,79:0,81:1,82:0,83:10}.items():e.poke(i,v)
 c.memmove(e.ram+e.sym['scene']-0x02000000+156,struct.pack('<I',sector),4)
 e.until(lambda s:s[3]!=2);e.run(30)
def select(letter):
 target=ord(letter)-ord('А')
 while e.state()[70]!=target:
  cur=e.state()[70];e.tap(6 if cur%8>target%8 else 7) if cur//8==target//8 else e.tap(5)
 e.tap(8);e.run(25)
 if e.state()[3]==16:
  e.run(90);e.screenshot('assistant-reveal.png');e.until(lambda s:s[3]!=16)
  e.run(25)
fixture_sector(3)
check('numeric sector uses original table',e.state()[8]==10 and e.state()[3]==3)
e.screenshot('keyboard.png');before=e.state();e.tap(0);e.run(25)
check('B keeps letter keyboard open without selecting a letter',e.state()[3]==3 and e.state()[71]==1 and e.state()[70]==before[70] and e.state()[38:70]==before[38:70])
e.tap(7);check('letter navigation remains available immediately after B',e.state()[70]==(before[70]+1)%32)
e.tap(0);check('repeated B keeps keyboard and cursor visible',e.state()[3]==3 and e.state()[71]==1 and e.state()[70]==(before[70]+1)%32)
e.tap(3);check('START pauses letter selection',e.state()[3]==11)
e.tap(3);check('pause resumes directly into letter selection',e.state()[3]==3 and e.state()[71]==1 and e.state()[70]==(before[70]+1)%32)
select('И');check('all repeated letters revealed',sum(e.state()[18:38])==3);check('points per occurrence',e.state()[11]==130);check('hit continues directly to same player turn',e.state()[3]==1 and e.state()[5]==2)
e.screenshot('correct-letter.png')
fixture_sector(10);check('x4 sector value',e.state()[8]==204);select('И');check('x4 multiplies score once',e.state()[11]==400)
fixture_sector(12);select('И');check('x2 multiplies score once',e.state()[11]==200)
fixture_sector(14);check('bankrupt clears score',e.state()[11]==0 and e.state()[3]==6);e.tap(8);check('bankrupt passes turn',e.state()[5]==0)
fixture_sector(2);check('zero sector keeps bank',e.state()[11]==100 and e.state()[3]==6)
fixture_sector(0);check('plus opens board selector',e.state()[3]==4);e.screenshot('plus.png');e.tap(8);e.run(30);e.until(lambda s:s[3]!=16);check('plus reveals chosen position',e.state()[18]==1);check('plus does not award numeric points',e.state()[11]==100)
fixture_sector(6);check('prize offers choice',e.state()[3]==7);e.screenshot('prize.png');e.tap(8);check('declining prize continues game',e.state()[3]==3)
fixture_sector(6);e.tap(6);e.tap(8);check('prize negotiation begins at original 100 rubles',e.state()[82:84]==(1,100));e.tap(6);e.tap(8);check('cash offer enters dedicated scene',e.state()[3]==21 and e.state()[82]==5);e.screenshot('cash-prize.png')
fixture_sector(6);e.tap(6);e.tap(8)
offers=[]
for i in range(3):e.tap(8);offers.append(e.state()[83])
check('original prize offer sequence',offers==[1000,100000,1000000]);e.tap(8);check('refusing money yields original gift',e.state()[3]==10 and e.state()[82]==6 and 0<=e.state()[83]<10);e.screenshot('gift-prize.png')
fixture_sector(3,streak=2);select('И');check('third successful turn offers bonus',e.state()[3]==6 and e.state()[77]==8);e.tap(8);e.run(30);check('bonus chests enter',e.state()[3]==8);e.screenshot('chests.png');before=e.state()[11];e.tap(8);check('chest award is original 100 or zero',e.state()[11]-before in (0,100))
check('emulated audio is audible',e.nonzero>0)
diag=struct.unpack('<4I',c.string_at(e.ram+e.sym['speaker_diag']-0x02000000,16));check('FIFO audio interrupts execute',diag[0]>100 and diag[1]>1000)
with wave.open(str(ROOT/'build/qa/speaker.wav'),'wb') as wav:
 wav.setnchannels(2);wav.setsampwidth(2);wav.setframerate(e.rate);wav.writeframes(b''.join(e.audio))
# Keep an easily playable excerpt of actual original-effect playback.
raw=b''.join(e.audio);mono=[v[0] for v in struct.iter_unpack('<hh',raw)]
start=next(i for i,v in enumerate(mono) if abs(v)>100)
start=max(0,start-e.rate//10)
with wave.open(str(ROOT/'build/qa/speaker-demo.wav'),'wb') as wav:
 wav.setnchannels(2);wav.setsampwidth(2);wav.setframerate(e.rate);wav.writeframes(raw[start*4:(start+e.rate*5)*4])
# Pitch fixture drives the real DMA synthesis path with a known PIT input.
e.poke(3,3);e.poke(5,2)
def tone_fixture():
 c.memmove(e.ram+e.sym['notes']-0x02000000,struct.pack('<HH',440,1000),4)
 for name,value in [('index',0),('remaining',0),('count',1)]:c.memmove(e.ram+e.sym[name]-0x02000000,struct.pack('<I',value),4)
tone_fixture();offset=len(e.audio);e.run(75)
mono=[v[0] for v in struct.iter_unpack('<hh',b''.join(e.audio[offset:]))][e.rate//5:e.rate*4//5]
cross=[i for i in range(1,len(mono)) if mono[i-1]<=0<mono[i]]
hz=(len(cross)-1)*e.rate/(cross[-1]-cross[0]);check('PIT 440 Hz pitch in emulated output',abs(hz-440.125784)<2)
e.tap(10);tone_fixture();e.run(20);offset=len(e.audio);e.run(30)
check('L mutes speaker synthesis',all(abs(v[0])<=16 and abs(v[1])<=16 for v in struct.iter_unpack('<hh',b''.join(e.audio[offset:]))));e.tap(10)
# Explicit credits-transition fixtures cover every DOS starting bank for both
# opponents, independent rolls, replacement of the old banks, and human carry.
for round_no,allowed in ((1,{5,20,35,50}),(2,{10,40,70,100})):
 seen=[set(),set()];pairs=set()
 for seed in range(32):
  for i,v in {2:seed*9973,3:17,4:round_no-1,9:777,10:888,11:1234}.items():e.poke(i,v)
  ticks=struct.unpack('<I',c.string_at(e.ram+e.sym['video_ticks']-0x02000000,4))[0]
  c.memmove(e.ram+e.sym['scene']-0x02000000+12,struct.pack('<I',(ticks-40)&0xffffffff),4)
  e.tap(8);s=e.state()
  check(f'round {round_no+1} seed {seed}: credits start next round',s[3:5]==(15,round_no))
  check(f'round {round_no+1} seed {seed}: DOS opponent banks and human carry',all(v in allowed for v in s[9:11]) and s[11]==1234)
  for i in range(2):seen[i].add(s[9+i])
  pairs.add(s[9:11])
 check(f'round {round_no+1}: both opponents can receive every DOS bank',all(values==allowed for values in seen))
 check(f'round {round_no+1}: opponents roll their banks independently',any(a!=b for a,b in pairs))

# Start a fresh game using only menu and keypad; solve three original words.
e.tap(3);e.tap(2);e.run(30);e.tap(8);e.run(30);skip_intro()
played=[]
for round_no in range(3):
 check(f'round {round_no+1} enters',e.state()[3]==1 and e.state()[4]==round_no)
 check(f'round {round_no+1} starts with original opponent banks',all(v in ({0},{5,20,35,50},{10,40,70,100})[round_no] for v in e.state()[9:11]))
 entry=words[e.state()[6]];played.append(entry['id']);e.tap(6);e.tap(8);check('turn menu enters full-word input',e.state()[3]==5)
 for letter in entry['word']:select(letter)
 e.screenshot(f'solve-round-{round_no+1}.png');e.tap(3);e.run(30);check(f'round {round_no+1} solved',e.state()[3]==9 and e.state()[5]==2)
 e.tap(8);e.run(30);skip_intro()
check('three different original questions',len(set(played))==3)
check('three-round win reaches original gift text',e.state()[3]==19)
for page in range(3):
 e.run(24);e.screenshot(f'final-gift-{page+1}.png');e.tap(8)
e.run(24);check('three-round gift goes directly to winner records',e.state()[3]==12)
e.tap(8);check('winner records return to title',e.state()[3]==0)
# Controlled final-score fixture reaches original eight-entry name / SRAM path.
e.poke(3,9);e.poke(4,2);e.poke(5,2);e.poke(11,30000);e.tap(8)
for page in range(3):e.tap(8)
check('highscore name entry follows gift screens directly',e.state()[3]==14)
select('Я');e.tap(0);check('B still erases a typed name character',e.state()[3]==14 and e.state()[80]==0 and c.string_at(e.ramgame+352,1)==b'\0')
select('Я');e.tap(3);e.run(30);check('record table after name',e.state()[3]==12);e.screenshot('records.png')
saveptr=e.core.retro_get_memory_data(0);savebytes=c.string_at(saveptr,128)
check('SRAM signature',savebytes[:4]==b'POL2');check('SRAM score stored',struct.unpack_from('<I',savebytes,15)[0]==30000)
e.core.retro_reset();e.run(100);check('SRAM score survives console reset',e.state()[85]==30000)
e.tap(8);e.run(30);skip_intro();e.tap(6);e.tap(8)
entry=words[e.state()[6]];wrong='Я' if entry['word'][0]!='Я' else 'А'
for letter in wrong*len(entry['word']):select(letter)
e.tap(3);e.run(30);check('wrong full word rejected',e.state()[3]==6);e.tap(8);e.run(30);check('wrong full word eliminates human',e.state()[3]==10)
e.screenshot('game-over.png');e.close()
report=dict(status='passed',checks=checks,count=len(checks),emulator='mGBA 0.10.5 libretro',normal_keypad_rounds=played,rare_branch_tests='Explicit RAM fixtures in scripts/verify.py',speaker=dict(irqs=diag[0],samples=diag[1],transitions=diag[2],measured_test_hz=hz),rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest())
(ROOT/'build/qa/report.json').write_text(json.dumps(report,ensure_ascii=False,indent=2),encoding='utf-8')
print(json.dumps(report,ensure_ascii=True))
