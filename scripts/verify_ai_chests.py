"""Exercise AI chest dialogue, real PPU text, independent input and pause clocks.

RAM fixtures enter the bonus through end_result; the cartridge performs the
random choice, dialogue, opening and scoring. Seeds cover both choices/prizes.
"""
import ctypes as c, hashlib, json, struct
from emulator import Emulator, ROOT

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)

e=Emulator();e.run(220)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
font=(ROOT/'assets/font-14.bin').read_bytes()
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
def read(name,offset=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+offset,4))[0]
def write(name,value,offset=0):c.memmove(e.ram+e.sym[name]-0x02000000+offset,struct.pack('<I',value&0xffffffff),4)
def message():
 p=read('message1')
 return rom[p-0x08000000:].split(b'\0',1)[0] if p>=0x08000000 else c.string_at(e.ram+p-0x02000000)
def pixels():
 out=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  out.append(palette.index(r|(g<<5)|(b<<10)))
 return out
def next_rng(seed):return (seed*134775813+1)&0xffffffff
def chest_pixels(choice,money):
 p=pixels()
 for side in (0,1):
  sprite=(38 if money else 37) if side==choice else 36
  w,h,address=struct.unpack_from('<III',rom,e.sym['sprites']-0x08000000+sprite*12)
  data=rom[address-0x08000000:address-0x08000000+w*h];x=115 if side else 18
  check('selected chest opens with matching contents and other stays closed',all(
   p[(96+yy)*240+x+xx]==v for yy in range(h) for xx in range(w) if (v:=data[yy*w+xx])!=7))
def fixture(player,seed):
 e.run(12)
 for i in range(20):e.poke(18+i,0)
 for i,v in {3:6,4:0,5:player,6:0,9:130,10:130,11:130,12:0,13:1,71:0,72:0,77:8,78:player}.items():e.poke(i,v)
 e.tap(8)
 check('bonus enters normal chest prompt',e.state()[3]==8)
 e.poke(2,seed)
 return read('scene',4)
def wait_answer(noisy=False):
 n=0
 while e.state()[3]==8:
  e.run(1,(8,7) if noisy and n%8<4 else (6,) if noisy else ())
  n+=1
 e.run(16)
 check('AI answer has its own scene',e.state()[3]==22)
def reply_pixels(player,choice):
 data=('Правая!' if choice else 'Левая!').encode('cp866');p=pixels()
 x=(141 if player else 1)+(98-len(data)*8)//2
 check('complete reply uses original readable font in opponent balloon',all(
  p[(44+yy)*240+x+i*8+xx]==(0 if font[ch*14+yy]&(128>>xx) else 14)
  for i,ch in enumerate(data) for yy in range(14) for xx in range(8)))
 left=113 if choice else 16;other=16 if choice else 113
 check('announced chest alone has selection frame',all(p[94*240+x]==14 for x in range(left,left+40)) and not any(p[94*240+x]==14 for x in range(other,other+40)))
 check('host rests while opponent answers',read('scene',168)==0)

try:
 # All four random choice/reward combinations, for both opponent positions.
 for player in (0,1):
  for choice in (0,1):
   for money in (False,True):
    seed=next(s for s in range(1000) if (next_rng(s)>>16)%2==choice)
    entered=fixture(player,seed);e.run(105)
    p=pixels()
    check('prompt offers no human selection frame for AI',not any(p[94*240+x]==14 for x in list(range(16,56))+list(range(113,153))))
    wait_answer();answered=read('scene',4)
    check('host prompt completes before AI reply',150<=answered-entered<=162)
    check('AI chooses seeded side and says matching phrase',e.state()[81]==choice and message()==('Правая!' if choice else 'Левая!').encode('cp866'))
    e.screenshot(f'ai-chest-{player}-{choice}.png')
    reply_pixels(player,choice)
    # Reward RNG is seeded separately to cover both outcomes without luck.
    prize_seed=next(s for s in range(100) if ((next_rng(s)>>16)%2==choice)==money)
    e.poke(2,prize_seed);before=e.state()[9+player]
    e.run(40,(8,6,7))
    check('buttons cannot change or prematurely accept AI reply',e.state()[3]==22 and e.state()[81]==choice and e.state()[9+player]==before)
    e.run(1);e.until(lambda s:s[3]!=22)
    check('AI reply stays readable for 1.5 seconds',90<=read('video_ticks')-answered<=102)
    reward=100 if money else 0
    check('opening applies correct reward only to active opponent',e.state()[3]==6 and e.state()[9+player]==before+reward and e.state()[10-player]==130 and e.state()[11]==130)
    check('host receives correct original reward response',read('message1')==e.sym['msg_ef1' if money else 'msg_f07'])
    e.run(16)
    chest_pixels(choice,money)
    e.screenshot(f'ai-chest-open-{player}-{choice}-{int(money)}.png')
    e.tap(8)
    check('bonus returns to same opponent without scoring twice',e.state()[3]==1 and e.state()[5]==player and e.state()[9+player]==before+reward)

 # Same seeds, with/without continual input: choice, RNG and result agree.
 for seed in (1,2,42,12345):
  results=[]
  for noisy in (False,True):
   fixture(0,seed);wait_answer(noisy)
   state=(e.state()[81],e.state()[2],message())
   e.until(lambda s:s[3]!=22)
   results.append((state,e.state()[9],e.state()[2]))
  check(f'input does not affect AI randomness or outcome, seed {seed}',results[0]==results[1])
 check('sample seeds produce both chest choices',len({(next_rng(seed)>>16)%2 for seed in (1,2,42,12345)})==2)

 # Pause during each phase, then ensure its remaining duration is retained.
 for mode in (8,22):
  fixture(1,2)
  if mode==22:wait_answer()
  else:e.run(40)
  e.tap(3);check('START pauses AI chest phase',e.state()[3]==11)
  old=read('scene',4);age=read('video_ticks')-old;choice=e.state()[81];rng=e.state()[2]
  e.run(180)
  check('paused AI chest cannot choose or award',e.state()[3]==11 and e.state()[81]==choice and e.state()[2]==rng and e.state()[10]==130)
  e.tap(3)
  check('resuming retains phase, selection and remaining deadline',e.state()[3]==mode and abs((read('video_ticks')-read('scene',4))-age)<=12 and read('scene',4)>=old+180)
  e.until(lambda s:s[3]!=mode)
  check('resumed AI chest advances automatically',e.state()[3]==(22 if mode==8 else 6))
finally:e.close()

report=dict(status='passed',count=len(checks),checks=checks,rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/ai-chests-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps(dict(status=report['status'],count=len(checks),rom_sha256=report['rom_sha256'])))
