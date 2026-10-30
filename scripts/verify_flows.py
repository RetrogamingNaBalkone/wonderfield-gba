"""DOS gift certificates, three real successful turns, and short input taps.

Rare initial states/seeds are explicit RAM fixtures. Transitions use cartridge
code and keypad input; certificate references come directly from POLE.EXE.
"""
from emulator import Emulator,ROOT
import ctypes as c,struct,json,hashlib,textwrap,zlib,binascii

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
e=Emulator();e.run(220)
rom=(ROOT/'build/gba/pole.gba').read_bytes();exe=(ROOT/'originals/Wonderfield/POLE.EXE').read_bytes()
header=struct.unpack_from('<H',exe,8)[0]*16
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
font=(ROOT/'assets/font-14.bin').read_bytes();font8=(ROOT/'assets/font-8.bin').read_bytes()
def literal(off):
 p=header+off;return exe[p+1:p+1+exe[p]]
gifts=[]
for i in range(10):
 p=header+0xc790+0x19a+i*25;gifts.append(exe[p+1:p+1+exe[p]])
def read_scene(off):return struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+off,4))[0]
def write_scene(off,value):c.memmove(e.ram+e.sym['scene']-0x02000000+off,struct.pack('<I',value),4)
def ppu():
 out=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  out.append(r|(g<<5)|(b<<10))
 return out
def preview(name):
 pixels=ppu();raw=bytearray()
 for y in range(160):
  row=bytearray()
  for v in pixels[y*240:(y+1)*240]:row+=bytes(((v&31)*255//31,((v>>5)&31)*255//31,((v>>10)&31)*255//31))*4
  raw+=(b'\0'+row)*4
 def chunk(t,b):return struct.pack('>I',len(b))+t+b+struct.pack('>I',binascii.crc32(t+b)&0xffffffff)
 (ROOT/'build/qa'/name).write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',960,640,8,2,0,0,0))+chunk(b'IDAT',zlib.compress(raw))+chunk(b'IEND',b''))

offsets=[0x41d7,0x41fd,0x4224,0x4240,0x4261,0x4285,0x46aa,0x46ca,0x46d2,0x46fc,0x4718,0x4739,0x475d,0x4099,0x40d8,0x478c,0x479e]
for off in offsets:
 pos=e.sym[f'msg_{off:x}']-0x08000000
 check(f'original certificate literal {off:x} retained byte for byte',rom[pos:rom.index(0,pos)]==literal(off))

glyphs_checked=0
def certificate(final,page,gift,score):
 global glyphs_checked
 if page==0:
  paras=[(literal(0x46aa)+str(score).encode()+literal(0x46ca) if final else literal(0x41d7),0),
         (literal(0x46d2 if final else 0x41fd),0),(gifts[gift]+literal(0x46fc if final else 0x4224),15)]
 elif page==1:paras=[(literal(0x4718 if final else 0x4240),0),(literal(0x4739 if final else 0x4261),15),(literal(0x475d if final else 0x4285),0)]
 else:paras=[(literal(0x4099),0),(literal(0x40d8),0)]
 pixels=ppu();y=50;errors=0;clipped=False
 for text,color in paras:
  lines=textwrap.wrap(text.decode('cp866'),width=29,replace_whitespace=False,break_on_hyphens=False)
  for line in lines:
   data=line.encode('cp866');x=(240-len(data)*8)//2;clipped|=y+14>151 or x<4
   for i,ch in enumerate(data):
    for yy in range(14):
     for xx in range(8):
      expected=color if font[ch*14+yy]&(128>>xx) else 1 if color==15 else 7
      errors+=pixels[(y+yy)*240+x+i*8+xx]!=palette[expected]
   glyphs_checked+=len(data);y+=16
  y+=2
 check(f'{"final" if final else "Prize"} gift {gift}, page {page+1}: complete original text in PPU',not clipped and errors==0)
 check(f'page counter {page+1}/3 has no overprinted digit',all(pixels[(152+y)*240+208+i*8+x]==palette[0 if font8[ch*8+y]&(128>>x) else 7] for i,ch in enumerate(f'{page+1}/3'.encode()) for y in range(8) for x in range(8)))

def next_rng(seed):return (seed*134775813+1)&0xffffffff
for gift in range(10):
 seed=next(seed for seed in range(1000) if (next_rng(seed)>>16)%10==gift)
 score=12345+gift*17
 for i,v in {2:seed,3:9,4:2,5:2,6:0,11:score,71:0}.items():e.poke(i,v)
 e.tap(8);e.run(24)
 check(f'final win draws original random gift {gift}',e.state()[3]==19 and e.state()[83]==gift)
 rng=e.state()[2]
 if gift==0:
  e.run(180);check('gift page waits for player instead of disappearing',e.state()[3]==19 and read_scene(184)==0)
 for page in range(3):
  certificate(True,page,gift,score)
  if gift==0:preview(f'finale-page-{page+1}.png')
  if page==1:
   e.tap(0);e.run(24);certificate(True,0,gift,score);e.tap(8);e.run(24)
   check(f'backtracking does not reroll gift {gift}',e.state()[83]==gift and e.state()[2]==rng)
  e.tap(8);e.run(24)
 check(f'gift {gift} pages precede final congratulations and records',e.state()[3]==6 and e.state()[77]==20)
 if gift==0:
  e.tap(8);check('winning score reaches name only after gift and congratulations',e.state()[3]==14)

# The same original gift instructions also occur when choosing sector Prize.
for i,v in {3:7,4:0,5:2,6:0,81:1,82:1,83:100}.items():e.poke(i,v)
for i in range(4):e.tap(8)
gift=e.state()[83];check('refusing all cash offers chooses an original Prize gift',e.state()[3]==10 and e.state()[82]==6)
e.tap(8);e.run(24)
for page in range(3):
 certificate(False,page,gift,e.state()[11])
 if page==0:preview('prize-gift-text.png')
 e.tap(8);e.run(24)
check('Prize certificate finishes with farewell, without winner records',e.state()[3]==10 and e.state()[82]==0)

words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf8'));word=bytes.fromhex(words[0]['word_hex'])
def start_fixture():
 e.run(12)
 for i in range(20):e.poke(18+i,0)
 for i in range(32):e.poke(38+i,0)
 for i,v in {3:1,4:0,5:2,6:0,7:12,11:0,70:0,71:0,72:0,76:0,79:0,82:0}.items():e.poke(i,v)
def spin_to(sector):
 initial=e.state()[7]
 seed=next(s for s in range(1000) if (initial-64-((next_rng(s)>>16)%32))&15==sector)
 e.poke(2,seed);e.tap(8);e.tap(8)
 check(f'keypad spin reaches sector {sector}',e.state()[3]==(4 if sector==0 else 3))
def pick(letter):
 target=letter.encode('cp866')[0]-128
 if e.state()[3]==4:
  while word[e.state()[70]]!=128+target:e.tap(7)
 else:
  while e.state()[70]!=target:e.tap(7)
 e.tap(8);check('correct keypad letter invokes assistant',e.state()[3]==16)
 plus=e.state()[8]==100;e.tap(8)
 check('Plus assistant continues straight to turn' if plus else 'assistant skip retains reaction screen',e.state()[3]==(1 if plus else 6))

# Three actual successful turns: never inject a nonzero streak counter.
for with_plus,choice in ((False,0),(False,1),(True,1)):
 start_fixture();turns=[('Б',3),('И',0 if with_plus else 3),('Л',3)]+([('О',3)] if with_plus else [])
 for index,(letter,sector) in enumerate(turns):
  spin_to(sector);pick(letter)
  last=index==len(turns)-1
  check(f'bonus progression plus={with_plus}, choice={choice}, hit={index+1}',e.state()[77]==(8 if last else 1))
  if e.state()[3]==6:e.tap(8)
 check('three successful ordinary turns open two chests',e.state()[3]==8)
 e.run(24);preview('three-letters-chests.png')
 if choice:e.tap(7)
 check(f'chest {choice} selectable',e.state()[81]==choice)
 seed=next(s for s in range(100) if (next_rng(s)>>16)%2==choice);e.poke(2,seed)
 before=e.state()[11];e.tap(8)
 check(f'chest {choice} awards original 100 points once',e.state()[11]==before+100 and e.state()[77]==1 and e.state()[72]==0)
 e.tap(8);check('continuing chest reward does not add twice',e.state()[11]==before+100 and e.state()[3]==1)
start_fixture();spin_to(3);pick('И')
check('three occurrences of one guessed letter count as one turn',sum(e.state()[18:38])==3 and e.state()[72]==1 and e.state()[77]==1)

# VBlank input: one-frame taps during keyboard drawing, not long tap() holds.
def keyboard_fixture():
 start_fixture()
 for i,v in {3:2,7:4,74:1,75:1,76:0}.items():e.poke(i,v)
 write_scene(152,0);write_scene(156,3);e.until(lambda s:s[3]==3)
for delay in range(10):
 keyboard_fixture();e.run(delay);e.run(1,(7,));e.run(1);e.run(40)
 check(f'one-frame Right tap captured at keyboard appearance +{delay} frames',e.state()[3]==3 and e.state()[70]==1)
keyboard_fixture();e.run(1,(7,));e.run(1);e.run(1,(7,));e.run(1);e.run(40)
check('two quick directional taps both survive rendering',e.state()[70]==2)
keyboard_fixture();e.run(1,(7,));e.run(1);e.run(1,(8,));e.run(1);e.run(40)
check('quick Right then A preserves event order and selects Б',e.state()[3]==16 and e.state()[39]==1 and e.state()[38]==0)
check('queued selection A is not replayed as assistant skip',not any(e.state()[18:38]))

# Winning by the last ordinary letter must take the same certificate route.
start_fixture();e.poke(4,2);e.poke(11,100)
for i,ch in enumerate(word):e.poke(18+i,int(ch!=136))
spin_to(3)
while e.state()[70]!=8:e.tap(7)
e.tap(8);check('last final letter still invokes assistant',e.state()[3]==16)
e.tap(8);check('last final letter settles score before winning screen',e.state()[3]==9 and e.state()[11]==130)
e.tap(8);e.run(24);check('letter-based final win reaches gift screens',e.state()[3]==19)
certificate(True,0,e.state()[83],130)

e.close()
report=dict(status='passed',count=len(checks),checks=checks,certificate_glyphs_checked=glyphs_checked,reference='Original Pascal literals from POLE.EXE; native font-14.bin; actual mGBA PPU',rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/flows-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps(report))
