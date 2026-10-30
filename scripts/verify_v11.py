"""1.1 controls, fixed answer cells, numeral topology and exact cash playback.

Fixtures select states; inputs and images come from the compiled ROM in mGBA.
--long additionally plays all 100000 bills naturally (about 9.5 emulated min).
"""
from emulator import Emulator,ROOT
from extract import png,EGA
import ctypes as c,struct,json,hashlib,sys,wave

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
e=Emulator();e.run(220)
e.screenshot('title-v11.png')
title_raw=e.raw
e.tap(8)
while e.state()[3]==15:e.tap(8)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))
def read(name,offset=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+offset,4))[0]
def write(name,value,offset=0):c.memmove(e.ram+e.sym[name]-0x02000000+offset,struct.pack('<I',value&0xffffffff),4)
def memory(name,n):return c.string_at(e.ram+e.sym[name]-0x02000000,n)
def asset(name,n):return rom[e.sym[name]-0x08000000:e.sym[name]-0x08000000+n]
def ppu(raw=None):
 colors=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw if raw is None else raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  colors.append(r|(g<<5)|(b<<10))
 return bytes(palette.index(v) for v in colors)
def shot(name):e.run(16);e.screenshot(name)
def turn(fixed=(),word_id=0):
 for i in range(20):e.poke(18+i,int(i in fixed))
 for i in range(32):e.poke(38+i,0)
 for i,v in {3:1,4:0,5:2,6:word_id,70:0,71:0,76:0,79:0,81:1,82:0}.items():e.poke(i,v)
 write('message1',0);write('dirty',1);e.run(10)
def solve(fixed=(),word_id=0):turn(fixed,word_id);e.tap(6);e.tap(8);check('menu opens solve',e.state()[3]==5)
def letter(ch):e.poke(70,ch-128);e.tap(8)
def answer():return c.string_at(e.ramgame+352,21)

title_pixels=ppu(title_raw);font6=asset('font6',256*6)
check('compact version fits the final grid cell',all(title_pixels[(122+y)*240+218+i*4+x]==(0 if font6[ch*6+y]&(128>>x) else 7) for i,ch in enumerate(b'1.1') for y in range(6) for x in range(4)))
check('version keeps the grid cell border intact',all(title_pixels[y*240+234]==6 for y in range(115,134)) and all(title_pixels[134*240+x]==6 for x in range(213,235)))
check('version no longer touches the dedication',all(title_pixels[y*240+x]==7 for y in range(8) for x in range(208,232)))

# Source-independent topology: straight parallel stems and a single closed
# counter, not merely agreement with the asset-generation implementation.
spec=json.loads((ROOT/'assets/wheel-digits.json').read_text())
zero=spec['glyphs']['0'];inside=[row[1:-1] for row in zero]
check('zero has symmetric left/right silhouette',all(row==row[::-1] for row in zero))
check('zero right edge never bulges along the stem',len({row.rfind('#') for row in zero[1:-1]})==1)
check('zero has one continuous open counter',all(row[2]=='.' and row[:2]=='##' and row[-2:]=='##' for row in zero[1:-1]))
check('zero counter is capped at top and bottom',zero[0]==zero[-1]=='.###.')
for key,label in spec['labels'].items():
 check(f'numeral {label["text"]} uses separate digit columns',len(label['text'])==1 or label['gap']>=1)

# Both options remain visible; Start is no longer a hidden alternate action.
turn();shot('turn-menu-v11.png');e.tap(3);check('START opens pause from turn menu',e.state()[3]==11)
e.tap(3);check('START resumes turn menu',e.state()[3]==1)
e.tap(2);check('SELECT no longer pauses normal gameplay',e.state()[3]==1)
e.tap(3);e.tap(2);check('SELECT on pause returns to title',e.state()[3]==0);turn()
e.tap(6);e.tap(6);check('repeated Left keeps Say selected',e.state()[81]==0)
shot('turn-menu-solve-v11.png');e.tap(7);e.tap(7);check('repeated Right keeps Spin selected',e.state()[81]==1)
e.run(32,(8,));check('holding confirmation starts spin without skipping',e.state()[3]==2 and e.state()[74]>0);e.run(1)
spin_clock=read('scene',20);e.tap(3);check('START pauses spinning',e.state()[3]==11)
steps=e.state()[74];e.run(180);check('wheel does not advance while paused',e.state()[74]==steps)
e.tap(3);check('START resumes spinning with its timer shifted',e.state()[3]==2 and read('scene',20)>=spin_clock+180)
turn();e.run(1,(6,));e.run(1);e.run(1,(8,));e.run(1);e.run(30)
check('one-frame Left then A selects Say in order',e.state()[3]==5)
e.poke(3,6);e.poke(77,1);e.poke(78,2);e.tap(8)
check('new human turn resets selection to Spin',e.state()[3]==1 and e.state()[81]==1)
turn();e.poke(5,0);e.run(100);check('AI still starts spin automatically',e.state()[3]==2)

# Revealed I appears in three positions; include the first/last cells too.
word=bytes.fromhex(words[0]['word_hex']);fixed=[i for i,ch in enumerate(word) if ch in (word[0],word[1],word[-1])]
solve(fixed);check('revealed letters prefilled at their original positions',all(answer()[i]==(word[i] if i in fixed else 0) for i in range(len(word))))
before=answer();e.tap(2);check('SELECT pauses full-word input',e.state()[3]==11)
e.tap(3);check('START resumes full-word input without submitting',e.state()[3]==5 and answer()==before)
first=next(i for i in range(len(word)) if i not in fixed)
check('input starts on first hidden position',e.state()[80]==first)
before=answer();e.tap(0);check('B cannot delete the fixed prefix',answer()==before and e.state()[80]==first)
e.tap(3);check('START rejects incomplete answer without submitting',e.state()[3]==5)
before=answer();pos=e.state()[80];letter(word[1]);check('opened letter is blocked on keyboard',answer()==before and e.state()[80]==pos)
e.poke(38+6,1);letter(134);check('previous misses remain available',answer()[first]==134)
e.tap(0);check('B erases only user input',answer()[first]==0 and all(answer()[i]==word[i] for i in fixed))
for i,ch in enumerate(word):
 if i not in fixed:letter(ch)
shot('solve-fixed-v11.png');pixels=ppu();font=asset('font14',256*14);left=(240-len(word)*10)//2
check('fixed and typed glyphs have distinct actual PPU colours',all(pixels[(64+y)*240+left+i*10+x]==(8 if i in fixed else 15) for i,ch in enumerate(word) for y in range(14) for x in range(8) if font[ch*14+y]&(128>>x)))
for ch in set(word[i] for i in fixed):
 index=ch-128;x=8+(index%8)*28;y=86+(index//8)*16
 check(f'fixed key {index} has disabled strike through',all(pixels[(y+7)*240+x+dx]==0 for dx in range(3,23)))
e.tap(0);last=max(i for i in range(len(word)) if i not in fixed)
check('B skips fixed suffix',e.state()[80]==last and answer()[last]==0)
letter(word[last]);e.tap(3);check('prefilled complete word wins normally',e.state()[3]==9)
solve(fixed)
while e.state()[80]<len(word):letter(128)
e.tap(3);check('wrong word still loses',e.state()[3]==6 and e.state()[77]==10)
solve();letter(128);letter(128);check('unrevealed letter can be typed repeatedly',answer()[:2]==bytes((128,128)))
longest=max(range(len(words)),key=lambda i:len(words[i]['word']))
solve((0,len(words[longest]['word'])-1),longest)
check('longest word keeps fixed end cells and input in bounds',answer()[len(words[longest]['word'])]==0 and e.state()[80]==1)

# All 32 moving phases: compare actual ink to explicit hand-hinted masks.
labels=json.loads((ROOT/'build/generated/wheel-labels.json').read_text())
bank=asset('wheel_bitmaps',32*128*112);contact=bytearray(1920*640);numeric_checks=0
for phase in range(32):
 for i,v in {3:11,5:2,7:(12-phase//2)&15,74:100,75:100000,76:0,86:read('video_ticks'),87:2}.items():e.poke(i,v)
 write('scene',phase&1,152);write('scene',read('video_ticks'),20);write('message1',0);e.tap(0);e.run(24)
 pixels=ppu()
 if phase==0:e.screenshot('wheel-native-v11.png')
 for s in (s for s in labels if s['frame']==phase and str(s['resource']) in spec['labels']):
  label=spec['labels'][str(s['resource'])];rows=['']*12
  for digit in label['text']:
   rows=[row+('.'*label['gap'] if row else '')+glyph for row,glyph in zip(rows,spec['glyphs'][digit])]
  rows=[row.center(s['width'],'.') for row in rows]
  errors=0
  for yy,row in enumerate(rows):
   for xx,ch in enumerate(row):
    if ch=='#':
     errors+=pixels[(43+s['y']+yy)*240+32+s['x']+xx]!=label['ink'];numeric_checks+=1
  check(f'phase {phase}, numeral in sector {s["sector"]} retains every stroke',errors==0)
  # The gap and the zero counter must show the original sector, not ink.
  if label['text'].endswith('0'):
   zx=s['width']-5
   check(f'phase {phase} numeral {label["text"]} has clear zero counter',all(pixels[(43+s['y']+yy)*240+32+s['x']+zx+2]==s['expected_background'] for yy in range(1,11)))
 for y in range(160):contact[((phase//8*160+y)*1920+phase%8*240):((phase//8*160+y)*1920+phase%8*240+240)]=pixels[y*240:(y+1)*240]
 if phase==0:e.screenshot('wheel-native-v11.png')
png(ROOT/'build/qa/wheel-phases-v11.png',1920,640,contact,EGA)

# Independent Python compositor uses raw ROM note data, not the skip algorithm.
note=asset('small_data_56',28*18);spans=[]
for yy in range(18):
 x=0
 while x<28:
  if note[yy*28+x]==2:x+=1;continue
  start=x
  while x<28 and note[yy*28+x]!=2:x+=1
  spans.append((yy,start,note[yy*28+start:yy*28+x]))
def composite(canvas,seed,n):
 canvas=bytearray(canvas)
 for _ in range(n):
  seed=(seed*134775813+1)&0xffffffff
  seed=(seed*134775813+1)&0xffffffff;x=((seed>>16)%400)*35//96
  seed=(seed*134775813+1)&0xffffffff;y=((seed>>16)%295)//2
  for yy,xx,data in spans:
   if y+yy>=152:continue
   p=(y+yy)*240+x+xx;canvas[p:p+len(data)]=data
 return bytes(canvas),seed
def cash_fixture(amount):
 for i,v in {3:7,5:2,79:0,81:0,82:1,83:amount}.items():e.poke(i,v)
 e.tap(8);check(f'{amount} rubles opens dedicated payout',e.state()[3]==21 and read('cash')==0)
 return memory('cash_canvas',38400),read('cash',8)
frames=[];timings=[];skip_timings=[]
for amount in (100,1000,100000,1000000):
 canvas,seed=cash_fixture(amount);check(f'{amount} rubles has exact original bill count',read('cash',4)==amount//10)
 if amount==1000:shot('cash-screen-v11.png');frames.append(e.raw)
 if amount>=100000:
  expected=asset('cash_finished_bitmap',38400);end_seed=seed
  for _ in range(amount//10*3):end_seed=(end_seed*134775813+1)&0xffffffff
 else:expected,end_seed=composite(canvas,seed,amount//10)
 e.run(140);drawn=read('cash');check(f'{amount} rubles accumulates bills',drawn>0)
 e.tap(3);paused=memory('cash_canvas',38400);n=read('cash');e.run(120)
 check(f'{amount} rubles pauses without changing bills',e.state()[3]==11 and memory('cash_canvas',38400)==paused and read('cash')==n)
 e.tap(3);e.run(8);check(f'{amount} rubles restores scene from pause',e.state()[3]==21)
 if read('cash')<read('cash',4):
  started=read('video_ticks');e.tap(8)
  e.until(lambda s:read('cash')==read('cash',4),limit=12)
  latency=read('video_ticks')-started
  skip_timings.append(dict(rubles=amount,vblanks=latency))
  if amount>=100000:check(f'{amount} ruble skip completes within twelve VBlanks',latency<=12)
 e.until(lambda s:read('cash')==read('cash',4),limit=3000);e.run(16)
 check(f'{amount} skip uses prepared picture' if amount>=100000 else f'{amount} skip equals every original stamp',memory('cash_canvas',38400)==expected and read('cash',8)==end_seed)
 check(f'{amount} completed screen waits for next A',e.state()[3]==21)
 if amount==1000000:shot('cash-filled-v11.png')
 e.tap(8);check(f'{amount} completed payout proceeds to farewell',e.state()[3]==10 and e.state()[82]==0)

# Natural short payouts plus an animation of actual PPU frames.
canvas,seed=cash_fixture(1000);expected,end_seed=composite(canvas,seed,100)
started=read('cash',12);e.run(120);audio=len(e.audio)
while read('cash')<100:
 e.run(3);frames.append(e.raw)
elapsed=read('video_ticks')-started;timings.append(dict(banknotes=100,vblanks=elapsed,seconds=elapsed/e.fps))
check('natural payout equals exact independent compositor',memory('cash_canvas',38400)==expected and read('cash',8)==end_seed)
check('natural bill rate tracks measured 5000-cycle DOS within rendering tolerance',abs(elapsed/e.fps-100*.005672)<.15)
check('payout audio reaches real mGBA output',any(any(block) for block in e.audio[audio:]))
with wave.open(str(ROOT/'build/qa/cash-v11.wav'),'wb') as w:
 w.setnchannels(2);w.setsampwidth(2);w.setframerate(e.rate);w.writeframes(b''.join(e.audio[audio:]))
shot('cash-natural-v11.png');frames.extend([e.raw]*5)
for i,v in {3:7,5:2,79:0,81:0,82:1,83:1000}.items():e.poke(i,v)
e.run(50,(8,));check('holding accepting A cannot skip opening',e.state()[3]==21 and read('cash')==0)
e.run(250,(8,));check('holding accepting A cannot leave payout',e.state()[3]==21 and read('cash')==100);e.run(1)

if '--long' in sys.argv:
 canvas,seed=cash_fixture(1000000);expected,end_seed=composite(canvas,seed,100000)
 start=read('cash',12);e.run(120);last=0
 while read('cash')<100000:
  e.run(100)
  if read('cash')//10000>last:last=read('cash')//10000;print(f'Natural payout: {read("cash")}/100000',flush=True)
 elapsed=(read('video_ticks')-start)/e.fps
 check('natural million completes every bill without duration cap',memory('cash_canvas',38400)==expected and read('cash',8)==end_seed)
 check('natural million matches DOS duration',abs(elapsed-567.2)<3)
 timings.append(dict(banknotes=100000,seconds=elapsed))

from capture_media import gif
gif(ROOT/'build/qa/cash-v11.gif',frames,e.format,delay=5)
e.close()
report=dict(status='passed',count=len(checks),checks=checks,numeral_pixels=numeric_checks,
 cash_timings=timings,cash_skip_timings=skip_timings,long_cash='--long' in sys.argv,rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/v11-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:v for k,v in report.items() if k!='checks'}))
