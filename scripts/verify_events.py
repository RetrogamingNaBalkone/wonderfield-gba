"""mGBA integration regressions for DOS events, spin input and spoken answers.

RAM fixtures select rare sectors; all transitions, timing and PPU images are
produced by the cartridge. Original literals and sprites are the reference.
"""
from emulator import Emulator, ROOT
import ctypes as c, struct, json, hashlib, zlib, binascii

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)

e=Emulator();e.run(220);e.tap(8)
while e.state()[3]==15:e.tap(8)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
def write(name,value,offset=0):
 c.memmove(e.ram+e.sym[name]-0x02000000+offset,struct.pack('<I',value & 0xffffffff),4)
def read(name,offset=0):
 return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+offset,4))[0]
def message(name='message1'):
 address=read(name)
 if address>=0x08000000:return rom[address-0x08000000:].split(b'\0',1)[0]
 return c.string_at(e.ram+address-0x02000000)
def ppu():
 out=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  out.append(r|(g<<5)|(b<<10))
 return out
def preview(name):
 pixels=ppu();data=bytearray()
 for y in range(160):
  row=bytearray()
  for v in pixels[y*240:(y+1)*240]:row+=bytes(((v&31)*255//31,((v>>5)&31)*255//31,((v>>10)&31)*255//31))*4
  data+=(b'\0'+row)*4
 def chunk(tag,b):return struct.pack('>I',len(b))+tag+b+struct.pack('>I',binascii.crc32(tag+b)&0xffffffff)
 (ROOT/'build/qa'/name).write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',960,640,8,2,0,0,0))+chunk(b'IDAT',zlib.compress(data))+chunk(b'IEND',b''))

words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))
original=(ROOT/'originals/Wonderfield/POLE.EXE').read_bytes();header=struct.unpack_from('<H',original,8)[0]*16
def dos_message(off):
 pos=header+off;return original[pos+1:pos+1+original[pos]]
word=bytes.fromhex(words[0]['word_hex']);letter=word[0]-128
# Restrict AI to one still-hidden letter, without replacing AI selection code.
def fixture(sector,player=2,last=False):
 for i in range(20):e.poke(18+i,int(last and i<len(word) and word[i]!=128+letter))
 for i in range(32):e.poke(38+i,int(i!=letter))
 for i,v in {3:2,4:0,5:player,6:0,7:(sector+1)&15,8:0,9:100,10:100,11:100,70:0,71:0,72:0,74:1,75:1,76:0,79:0,81:1,82:0,83:0}.items():e.poke(i,v)
 write('scene',0,152)
 write('scene',sector,156)
 e.until(lambda s:s[3]!=2)

# A new press skips to exactly the outcome already determined by remaining steps.
for target in range(16):
 for half in (0,1):
  for i,v in {3:2,5:2,6:0,7:(target+7)&15,74:23,75:8,76:0}.items():e.poke(i,v)
  write('scene',half,152);write('scene',target,156);e.tap(8)
  check(f'A skip preserves sector {target}, half {half}',e.state()[3]!=2 and e.state()[7]==target and e.state()[74]==0)

# Holding the press which starts the wheel must not skip it immediately.
e.poke(3,1);e.poke(5,2);e.run(6);e.run(28,(8,))
check('starting A held down keeps spinning',e.state()[3]==2 and e.state()[74]>0)
e.run(8);target=(e.state()[7]-e.state()[74])&15;e.tap(8)
check('second A press shows predetermined result',e.state()[3]!=2 and e.state()[7]==target)

# Replay identical real starts, rather than only injecting an ongoing spin.
# Outcome and RNG must match natural playback at every skip time.
def replay_start(seed):
 fixture(3);e.run(24)
 e.poke(3,1);e.poke(2,seed);e.poke(7,11);e.run(6);e.tap(8)
 check(f'replay {seed} starts through keypad',e.state()[3]==2)
 return read('scene',156)
different_current=False
for seed in (1,12345,999999):
 target=replay_start(seed)
 e.until(lambda s:s[3]!=2)
 natural=(e.state()[7],e.state()[8],e.state()[2])
 check(f'natural spin reaches stored outcome for seed {seed}',natural[0]==target)
 for delay in (0,7,30,75):
  check(f'identical start fixes same target for seed {seed}, delay {delay}',replay_start(seed)==target)
  e.run(delay)
  check(f'target unchanged while rotating for seed {seed}, delay {delay}',e.state()[3]==2 and read('scene',156)==target)
  different_current|=e.state()[7]!=target
  e.tap(8)
  check(f'skip equals natural sector, value and RNG for seed {seed}, delay {delay}',e.state()[3]!=2 and (e.state()[7],e.state()[8],e.state()[2])==natural)
check('skip replay includes times with a different sector under arrow',different_current)

# Every early rotation frame, including intermediate handles, reaches the PPU.
e.poke(3,2);e.poke(5,2);e.poke(74,90);e.poke(75,1);e.poke(76,0);write('scene',0,152)
bank=rom[e.sym['wheel_bitmaps']-0x08000000:e.sym['wheel_bitmaps']-0x08000000+32*128*112]
known={tuple(palette[v] for v in bank[f*128*112:f*128*112+28*128]):f for f in range(32)}
phases=set()
for i in range(110):
 e.run(1);pixels=ppu();crop=tuple(pixels[y*240+x] for y in range(43,71) for x in range(32,160))
 if crop in known:phases.add(known[crop])
check('all four original handle frames animate at initial fast speed',len({(f+3)%4 for f in phases})==4 and any(f&1 for f in phases))
check('early fast wheel remains far from slowdown',e.state()[74]>20)

# AI turn preparation uses elapsed VBlank time, not costly render iterations.
e.poke(3,6);e.poke(5,2);e.poke(77,1);e.poke(78,0);e.tap(8)
start=read('scene',4);e.until(lambda s:s[3]==2)
elapsed=read('video_ticks')-start
check('AI starts wheel within one second',30<=elapsed<=60)

# DOS Plus branches on player before reading the keyboard (1fd6 -> 226d).
# Replay the same seed with early human input: it must not select for the AI.
def ai_plus(player,seed,interfere):
 fixture(0,player)
 e.poke(2,seed)
 for i in range(len(word)):e.poke(18+i,int(i%3==0))
 before=e.state();cursor=before[70]
 for key in (7,6,8):
  e.run(8,(key,) if interfere else ())
  e.run(1)
  check(f'AI {player} Plus seed {seed}: early {key} leaves choice pending ({interfere})',e.state()[3]==4 and e.state()[70]==cursor and e.state()[18:70]==before[18:70] and e.state()[9:12]==before[9:12])
 pixels=ppu();left=30+((20-len(word))//2)*9
 check(f'AI {player} Plus has no human selection marker ({interfere})',all(pixels[25*240+left+i*9+1+x]!=palette[14] for i in range(len(word)) for x in range(8)))
 e.until(lambda s:s[3]==18)
 position=e.state()[70];letter=word[position]-128
 check(f'AI {player} Plus announces a hidden position ({interfere})',not before[18+position] and message()==str(position+1).encode()+dos_message(0x1fc6) and read('scene',144)==letter)
 choice=(position,letter,e.state()[2],message())
 e.run(30);e.tap(8)
 check(f'AI {player} Plus reveals only its announced letter ({interfere})',e.state()[3]==16 and all(read('scene',64+i*4)==int(bool(before[18+i]) or word[i]==word[position]) for i in range(len(word))))
 e.tap(8)
 check(f'AI {player} Plus keeps score and turn ({interfere})',e.state()[3]==1 and e.state()[5]==player and e.state()[9:12]==before[9:12] and all(e.state()[18+i]==int(bool(before[18+i]) or word[i]==word[position]) for i in range(len(word))))
 return choice

for player in (0,1):
 for seed in (1,12345,999999):
  natural=ai_plus(player,seed,False)
  check(f'AI {player} Plus seed {seed}: keypad cannot change random choice',ai_plus(player,seed,True)==natural)

# DOS 1000:1698 has one gameplay call: successful letter/Plus for any player.
# This includes multipliers, declined Prize and the last hidden letter.
for player in (0,1,2):
 for sector,name in ((3,'number'),(12,'x2'),(10,'x4'),(0,'plus'),(6,'declined prize')):
  fixture(sector,player,last=True)
  if e.state()[3]==7:e.tap(8)
  if player==2:
   if e.state()[3]==3:e.poke(70,letter)
   e.tap(8)
  else:
   e.until(lambda s:s[3]==18)
   speech=message();start=read('scene',4)
   check(f'AI {player} announces {name} before award',e.state()[9+player]==100 and not e.state()[38+letter] and bool(speech))
   e.run(65)
   check(f'AI {player} answer remains readable for {name}',e.state()[3]==18 and message()==speech)
   if sector!=0:check(f'AI {player} names actual letter for {name}',bytes([128+letter]) in speech)
   if sector==3:preview(f'ai-answer-{player}.png')
   e.until(lambda s:s[3]!=18)
   check(f'AI {player} answer lasts two seconds for {name}',read('video_ticks')-start>=120)
  check(f'assistant opens final {name} letter for player {player}',e.state()[3]==16 and e.state()[9+player]==100)
  check(f'Plus has no ordinary letter reaction for player {player}' if sector==0 else f'last {name} letter first gets ordinary correct-letter reply for player {player}',(message(),message('message2'))==((b'',b'') if sector==0 else (dos_message(0xe77),dos_message(0xe65))))
  if player==2 and sector==3:e.run(12);preview('round-last-letter.png')
  e.run(25);e.tap(8);e.run(15)
  expected=100+(word.count(128+letter)*10) if sector==3 else 200 if sector==12 else 400 if sector==10 else 100
  check(f'player {player} score awarded after {name} reveal',e.state()[9+player]==expected and e.state()[3]==9)
  ordinal=0xd8c if player==0 else 0xd93 if player==1 else 0xd9a
  check(f'{name} winner announced only after opening for player {player}',(message(),message('message2'))==(dos_message(ordinal)+dos_message(0xe9f),dos_message(0xea6)))
  spoken_at=read('scene',4);e.run(60)
  check(f'{name} winner message is not restarted for player {player}',e.state()[3]==9 and read('scene',4)==spoken_at)
  if player==2 and sector==3:preview('round-winner.png')
  if sector==3 and player!=2:
   pixels=ppu();font=(ROOT/'assets/font-8.bin').read_bytes();x=3 if player==0 else 143
   strokes=[(74+y)*240+x+i*8+xx for i,ch in enumerate(str(expected).encode()) for y in range(8) for xx in range(8) if font[ch*8+y]&(128>>xx)]
   check(f'AI {player} numeric score visible in PPU',all(pixels[p]==palette[0] for p in strokes))
   preview(f'ai-score-{player}.png')

# No assistant for absent letters, zero/bankrupt, accepting Prize or full words.
fixture(3);absent=next(i for i in range(32) if i+128 not in word);e.poke(70,absent);e.poke(38+absent,0);e.tap(8)
check('wrong letter does not summon assistant',e.state()[3]==6)
for sector in (2,14):
 fixture(sector);check(f'sector {sector} does not summon assistant',e.state()[3]==6)
fixture(6);e.run(24);preview('prize-choice.png');e.tap(6);e.run(24);preview('prize-choice-left.png')
e.tap(6);check('left on left option keeps Prize selected',e.state()[81]==0)
e.tap(7);e.tap(7);check('right on right option keeps Play selected',e.state()[81]==1)
e.tap(6);e.tap(8)
offers=[e.state()[83]]
for i in range(3):e.tap(8);offers.append(e.state()[83])
check('cash amounts match all four original spoken offers',offers==[100,1000,100000,1000000])
e.run(24);preview('prize-million.png');e.tap(6);e.run(24);preview('prize-money.png');e.tap(8)
check('accepted cash enters dedicated scene without letter or assistant',e.state()[3]==21 and e.state()[82]==5)
e.tap(8);e.until(lambda s:read('cash')==read('cash',4));e.run(20)
check('cash skip holds completed picture',e.state()[3]==21)
e.tap(8);e.run(20)
farewell=('К сожалению Вы'.encode('cp866'),'покидаете игру..'.encode('cp866'))
check('cash Prize followed by original farewell',(message(),message('message2'))==farewell)
preview('farewell.png')
fixture(6);e.tap(6);e.tap(8)
for i in range(4):e.tap(8)
check('four refusals yield gift and end game',e.state()[3]==10 and e.state()[82]==6)
e.tap(8);check('Prize gift opens original gift certificate',e.state()[3]==19)
for page in range(3):e.tap(8)
check('gift certificate followed by original farewell',(message(),message('message2'))==farewell)
fixture(6);e.tap(8)
check('declined Prize retains original reply',(message(),message('message2'))==('Если так, то'.encode('cp866'),'назовите букву.'.encode('cp866')))
e.poke(3,9);e.poke(5,0);e.tap(8)
check('AI victory followed by original farewell',(message(),message('message2'))==farewell)
e.poke(3,6);e.poke(77,10);e.poke(78,2);e.tap(8)
check('wrong full word followed by original farewell',(message(),message('message2'))==farewell)
e.poke(3,5);e.poke(5,2);e.poke(71,1);e.poke(80,len(word));c.memmove(e.ramgame+88*4,word+b'\0',len(word)+1);e.tap(3)
check('full-word success bypasses assistant as in DOS',e.state()[3]==9)

font14=(ROOT/'assets/font-14.bin').read_bytes()
matches=[i for i,ch in enumerate(word) if ch==136] # three occurrences of И
def select_reveal(sector):
 fixture(sector);e.poke(38+8,0);e.poke(70,matches[0] if sector==0 else 8);e.tap(8)
 check(f'keypad selects repeated letter in sector {sector}',e.state()[3]==16)
def visible_cell(i):
 pixels=ppu();x=30+((20-len(word))//2)*9+i*9+1
 return all(pixels[(11+y)*240+x+xx]==palette[0 if font14[word[i]*14+y]&(128>>xx) else 7] for y in range(14) for xx in range(8))

# The first reaction used to leave the assistant off-screen for 90 VBlank.
# Inspect the whole source sprite during that reaction, before she starts walking.
meta=json.loads((ROOT/'assets/sprites.json').read_text());sw=round(meta[23]['width']*35/96);sh=round(meta[23]['height']/2)
standing=rom[e.sym['small_data_23']-0x08000000:e.sym['small_data_23']-0x08000000+sw*sh]
for sector,name in ((3,'ordinary'),(0,'plus')):
 select_reveal(sector);e.run(12);pixels=ppu()
 if sector==0:
  check('Plus starts walking immediately without ordinary host reaction',e.state()[3]==16 and read('scene',44)>32 and (message(),message('message2'))==(b'',b''))
 else:
  check(f'{name} assistant is already on-screen during host reaction',e.state()[3]==16 and read('scene')-read('scene',12)<90 and all(pixels[(12+y)*240+32+x]==palette[v] for y in range(sh) for x in range(sw) if (v:=standing[y*sw+x])!=2))
 check(f'{name} waiting assistant has not opened cells early',not any(e.state()[18:38]))
 preview(f'assistant-waiting-{name}.png');e.tap(8)
 check(f'{name} new A skips the visible assistant straight to turn',e.state()[3]==1 and all(e.state()[18+i] for i in matches))

# Check the moment each cell turns in the real PPU, not only the final RAM mask.
for sector,name in ((3,'ordinary'),(0,'plus')):
 select_reveal(sector)
 for order,i in enumerate(matches):
  e.until(lambda s:read('scene',48)==6)
  check(f'{name} cell {i} is closed until assistant stops',e.state()[18+i]==0)
  e.until(lambda s:s[18+i]!=0);e.run(6)
  check(f'{name} cell {i} glyph visible beside stopped assistant',visible_cell(i))
  check(f'{name} later matches wait for their own stops',all(not e.state()[18+j] for j in matches[order+1:]))
  if order==0:preview('assistant-opens-letter.png' if sector==3 else 'assistant-opens-plus.png')
  # Leave this stop before looking for the next arrival.
  e.until(lambda s:read('scene',48)==0)
 e.until(lambda s:s[3]!=16);e.run(18)
 check(f'{name} complete walk leaves every matching glyph visible',all(visible_cell(i) for i in matches))
 check(f'{name} score is awarded once after walk',e.state()[11]==(130 if sector==3 else 100))

for sector in (3,0):
 select_reveal(sector);e.tap(8);e.run(16)
 check(f'immediate second A skips assistant in sector {sector}',e.state()[3]==1 and all(e.state()[18+i] for i in matches) and e.state()[11]==(130 if sector==3 else 100))
 check(f'immediate A exposes all PPU glyphs in sector {sector}',all(visible_cell(i) for i in matches))
 select_reveal(sector);e.until(lambda s:s[18+matches[0]]!=0);e.tap(8);e.run(16)
 check(f'A during walk opens remaining matches in sector {sector}',e.state()[3]==1 and all(visible_cell(i) for i in matches))
fixture(3);e.poke(38+8,0);e.poke(70,8);e.run(6);e.run(45,(8,))
check('holding selection A does not also skip assistant',e.state()[3]==16 and not any(e.state()[18:38]))
e.run(6);e.tap(8)
check('fresh A skips held-key reveal directly to turn without starting spin',e.state()[3]==1 and sum(e.state()[18:38])==3)

# Feet touch the upper floor edge immediately below the board, not the players.
fixture(3);e.poke(70,letter);e.tap(8)
e.until(lambda s:read('scene',48)>2 and read('scene',44)>30)
e.run(6);preview('assistant-ground.png')
meta=json.loads((ROOT/'assets/sprites.json').read_text());h=round(meta[23]['height']/2);w=round(meta[23]['width']*35/96)
source=rom[e.sym['small_data_23']-0x08000000:e.sym['small_data_23']-0x08000000+w*h]
pixels=ppu();actor=read('scene',44)
ink=[(xx,yy,v) for yy in range(h) for xx in range(w) if (v:=source[yy*w+xx])!=2]
check('entire assistant sprite reaches PPU with feet at upper floor edge',len(ink)>100 and all(pixels[(12+yy)*240+actor+xx]==palette[v] for xx,yy,v in ink) and 12+h-1==56)

# Source 42/45 change the mouth; 43/44 are eye strips. Compare the unobscured
# lower face to actual source pixels, and count event-driven mouth pulses.
face_templates={}
for id in (42,45):
 sw=round(meta[id]['width']*35/96);sh=round(meta[id]['height']/2)
 data=rom[e.sym[f'small_data_{id}']-0x08000000:e.sym[f'small_data_{id}']-0x08000000+sw*sh]
 face_templates[id]=tuple(palette[data[y*sw+x]] for y in range(28,51) for x in range(30))
def face_frame():
 pixels=ppu();sample=tuple(pixels[(57+y)*240+196+x] for y in range(28,51) for x in range(30))
 return next((id for id,template in face_templates.items() if template==sample),None)
e.poke(3,1);e.poke(5,2);write('scene',0,4);e.run(150)
check('idle host uses original closed-mouth face 45',face_frame()==45)
fixture(3);e.poke(71,0);mouth_sequence=[]
for frame in range(220):
 e.run(1);face=face_frame()
 if face is not None and (not mouth_sequence or mouth_sequence[-1]!=face):mouth_sequence.append(face)
 if face==42 and len(mouth_sequence)==2:preview('host-speaking.png')
if mouth_sequence and mouth_sequence[0]==42:mouth_sequence=mouth_sequence[1:]
check(f'host line uses three original mouth pulses then holds speaking face: {mouth_sequence}',mouth_sequence==[45,42,45,42,45,42])
fixture(3,0);e.until(lambda s:s[3]==18);e.run(12)
listening=[]
for frame in range(60):e.run(1);listening.append(face_frame())
check('host keeps mouth closed throughout AI answer',set(listening)=={45})
preview('host-listening.png')
e.poke(3,1);e.poke(5,2);e.run(6);e.tap(8);e.run(12)
spinning=[]
for frame in range(60):e.run(1);spinning.append(face_frame())
check('host keeps mouth closed while wheel spins',set(spinning)=={45})
select_reveal(3);e.until(lambda s:read('scene')-read('scene',12)>=100);e.run(12)
walking=[]
for frame in range(60):e.run(1);walking.append(face_frame())
check('host does not replay speech while assistant walks',set(walking)=={45})

# Transparency below the host balloon must preserve the underlying stage.
e.poke(3,1);e.poke(5,2);write('scene',0,4);e.run(150);base=ppu()
e.poke(3,6);write('message1',e.sym['msg_e77']);write('message2',e.sym['msg_e65']);write('scene',read('video_ticks'),4);write('dirty',1);e.run(24);pixels=ppu()
sprite=rom[e.sym['sprite_data_35']-0x08000000:e.sym['sprite_data_35']-0x08000000+117*40]
check('balloon transparency leaves no blue stripe below speech',all(pixels[(71+y)*240+4+x]==(palette[sprite[(30+y)*117+x*117//232]] if sprite[(30+y)*117+x*117//232]!=1 else base[(71+y)*240+4+x]) for y in range(10) for x in range(181)))
preview('speech-clean.png')

e.close()
report=dict(status='passed',count=len(checks),checks=checks,early_wheel_phases=sorted(phases),ai_start_vblanks=elapsed,prize_rubles=offers,rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/events-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps(report))
