"""Gray native-font UI, author navigation, PPU QR decoding and early AI skip."""
import ctypes as c,hashlib,json,shutil,struct,subprocess
from emulator import Emulator,ROOT

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)

node=shutil.which('node')
assert node,'Node.js is required only for independent QR verification'
e=Emulator();rom=(ROOT/'build/gba/pole.gba').read_bytes()
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
font=rom[e.sym['font14']-0x08000000:e.sym['font14']-0x08000000+256*14]
word=bytes.fromhex(json.loads((ROOT/'assets/words.json').read_text(encoding='utf8'))[0]['word_hex'])
url='https://t.me/RetroGamingNaBalkone'

def read(name,off=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+off,4))[0]
def write(name,value,off=0):c.memmove(e.ram+e.sym[name]-0x02000000+off,struct.pack('<I',value&0xffffffff),4)
def memory(name,n):return c.string_at(e.ram+e.sym[name]-0x02000000,n)
def boot():e.core.retro_reset();e.run(220);e.audio.clear()
def stable():e.run(16)
def body(raw):
 size=4 if e.format==1 else 2
 return raw[14*240*size:151*240*size]
def item(index):
 for _ in range(index):e.tap(5)
 e.tap(8);stable()
def fixture(mode,player=2):
 boot()
 for i,v in {3:mode,4:0,5:player,6:0,7:12,8:10,9:100,10:100,11:100,70:0,71:0,72:0,74:100,75:5,79:0,81:1,82:0}.items():e.poke(i,v)
 write('scene',read('video_ticks'),4);write('scene',word[0]-128,144)
 write('scene',read('video_ticks'),20);write('scene',0,168);write('message1',0);write('dirty',1)
def indices():
 out=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  out.append(palette.index(r|(g<<5)|(b<<10)))
 return out
def decode(name):
 rgba=bytearray()
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>16)&255,(v>>8)&255,v&255
  else:
   bits=6 if e.format==2 else 5;r=((v>>(5+bits))&31)*255//31;g=((v>>5)&((1<<bits)-1))*255//((1<<bits)-1);b=(v&31)*255//31
  rgba+=bytes((r,g,b,255))
 raw=ROOT/'build/qa/authors-qr.rgba';raw.write_bytes(rgba)
 result=json.loads(subprocess.check_output([node,str(ROOT/'scripts/decode_qr.cjs'),str(raw)],text=True))
 check(name+' independently decodes the exact URL',result==dict(data=url,version=3))
def qr_pixels(name):
 p=indices();meta=json.loads((ROOT/'build/generated/channel-qr.json').read_text())
 bits=bytes.fromhex(meta['packed_hex'])
 check(name+' uses V3 M and the exact payload',meta['url']==url and meta['version']==3 and meta['ecc']=='M')
 check(name+' keeps a white four-module quiet zone',all(p[y*240+x]==15 for y in range(24,135) for x in range(8,119) if x<20 or x>=107 or y<36 or y>=123))
 check(name+' preserves all modules at exact 3x scale',all(p[(36+y*3+dy)*240+20+x*3+dx]==(0 if bits[(y*29+x)//8]&(1<<((y*29+x)%8)) else 15) for y in range(29) for x in range(29) for dy in range(3) for dx in range(3)))
 decode(name)

try:
 boot();e.tap(3);stable();e.screenshot('menu-title-v11.png')
 check('title menu uses only grayscale',set(indices())<={0,7,8,15})
 item(1);e.screenshot('help-v11.png');p=indices()
 check('help uses only grayscale',set(p)<={0,7,8,15})
 commands=['Крестовина: Перемещение','A: Подтвердить / Далее','B: Назад / Стереть','START: Меню / Пауза','L: Включить / Выключить звук','Имя: R пробел, SELECT меню','Имя: START - сохранить']
 for row,text in enumerate(commands):
  check(f'help line {row+1} uses complete native 8x14 glyphs',len(text)*8<=224 and all(p[(25+row*16+y)*240+8+i*8+x]==0 for i,ch in enumerate(text.encode('cp866')) for y in range(14) for x in range(8) if font[ch*14+y]&(128>>x)))
 e.tap(0);e.tap(5);e.tap(5);e.tap(8);stable()
 check('title Authors opens DOS author first',e.state()[3]==24 and read('ui',24)==0)
 dos=e.raw;e.screenshot('authors-dos-v11.png');e.run(600)
 check('DOS author waits for input',e.state()[3]==24 and read('ui',24)==0)
 e.tap(8);stable();e.screenshot('authors-gba-v11.png');qr_pixels('menu GBA author')
 e.tap(10);stable();e.screenshot('authors-gba-muted-v11.png');qr_pixels('muted GBA author')
 check('muted GBA author remains entirely grayscale',set(indices())<={0,7,8,15})
 draws=read('rendered_frames');e.run(600)
 check('GBA author waits without repeated rendering',e.state()[3]==24 and read('rendered_frames')==draws)
 e.tap(0);stable();check('B returns to unchanged DOS author',body(e.raw)==body(dos))
 e.tap(8);e.tap(8);check('A from GBA author returns to selected menu entry',e.state()[3]==23 and read('ui',8)==3)
 e.tap(8);e.tap(0);check('B from first author returns to menu',e.state()[3]==23)
 e.tap(8);e.tap(8);e.tap(3);check('START closes nested authors to title',e.state()[3]==0)

 fixture(2);before=e.state();e.tap(3);stable();e.screenshot('menu-pause-v11.png');since=read('ui',16);spin=read('scene',20)
 item(2);e.tap(8);stable();decode('paused GBA author');e.run(240);e.tap(3)
 check('authors in pause restore scene, RNG and spin steps',e.state()[3]==2 and e.state()[2]==before[2] and e.state()[74]==before[74])
 check('authors count as one continuous pause',abs((read('scene',20)-spin)-(read('video_ticks')-since))<=8)
 for mode in (5,14,19):
  fixture(mode);e.poke(80,2);c.memmove(e.ramgame+352,b'AB\0',3)
  write('scene',1,180);write('scene',1,184)
  before=e.state();gift=memory('scene',188)[180:188];saved=c.string_at(e.core.retro_get_memory_data(0),128)
  key=2 if mode==14 else 3
  e.tap(key);item(2);e.tap(8);e.run(180);e.tap(key)
  check(f'authors preserve input and score in mode {mode}',e.state()[3]==mode and e.state()[9:12]==before[9:12] and e.state()[80]==2 and memory('game',376)[352:355]==b'AB\0')
  check(f'authors preserve gift and SRAM in mode {mode}',memory('scene',188)[180:188]==gift and c.string_at(e.core.retro_get_memory_data(0),128)==saved)

 # The new last page belongs to both original gift branches, never to a loss.
 for final in (0,1):
  fixture(19);write('scene',final,180);write('scene',2,184);write('dirty',1);stable()
  check('gift DOS author body matches menu DOS author',body(e.raw)==body(dos))
  rng=e.state()[2];score=e.state()[11];saved=c.string_at(e.core.retro_get_memory_data(0),128)
  e.tap(8);stable();check('GBA author follows existing DOS author',e.state()[3]==19 and read('scene',184)==3)
  if final:e.screenshot('finale-page-4.png')
  qr_pixels(f'gift GBA author, final={final}');e.run(600)
  e.tap(0);check('gift B returns to DOS author without reroll',read('scene',184)==2 and e.state()[2]==rng and e.state()[11]==score)
  e.tap(8);e.tap(8);check('gift keeps its original exit route',e.state()[3]==(12 if final else 10))
  check('viewing attribution never changes SRAM',c.string_at(e.core.retro_get_memory_data(0),128)==saved)
 fixture(10);e.tap(8);check('ordinary farewell returns directly to title',e.state()[3]==0)

 # Capture each AI transition naturally and after an A in the first frames.
 for player in (0,1):
  for mode in (1,3,4,8,18,22):
   outcomes=[]
   for skip in (False,True):
    fixture(mode,player);e.poke(2,12345)
    if skip:
     e.run(40,(8,));e.run(1)
     check(f'AI {player} mode {mode} accepts early A and held A advances once',e.state()[3]=={1:2,3:18,4:18,8:22,18:16,22:6}[mode])
    else:e.until(lambda s:s[3]!=mode)
    state=e.state();outcomes.append((state[2],state[3],state[9:12],state[70],state[81],read('scene',144),read('scene',156)))
   check(f'AI {player} mode {mode} skip preserves seeded outcome',outcomes[0]==outcomes[1])
 fixture(6,0);e.poke(77,1);e.poke(78,0)
 e.run(80,(8,));check('held A from preceding result cannot skip the next AI prompt',e.state()[3]==1)
 e.run(120,(8,));check('held A across prompt timeout cannot also skip the wheel',e.state()[3]==2 and e.state()[74]>0)
finally:e.close()

report=dict(status='passed',count=len(checks),checks=checks,qr=dict(payload=url,version=3,ecc='M',pixels=111,decoder='jsQR 1.4.0'),rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/authors-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:v for k,v in report.items() if k!='checks'}))
