"""1.1 menus, compact help, result deadlines and real muted mGBA output.

Rare-state fixtures edit emulated RAM; transitions execute cartridge code.
"""
import ctypes as c,hashlib,json,struct
from emulator import Emulator,ROOT

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)

e=Emulator()
rom=(ROOT/'build/gba/pole.gba').read_bytes()
words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf8'))
word=bytes.fromhex(words[0]['word_hex'])
def read(name,off=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+off,4))[0]
def write(name,value,off=0):c.memmove(e.ram+e.sym[name]-0x02000000+off,struct.pack('<I',value&0xffffffff),4)
def memory(name,n):return c.string_at(e.ram+e.sym[name]-0x02000000,n)
def boot():e.core.retro_reset();e.run(220);e.audio.clear()
def fixture(mode=1,player=2):
 boot()
 for i,v in {3:mode,4:0,5:player,6:0,7:12,8:10,9:100,10:100,11:100,70:0,71:0,72:0,74:20,75:100,79:0,80:0,81:1,82:0}.items():e.poke(i,v)
 write('scene',read('video_ticks'),4);write('scene',read('video_ticks'),20)
 write('scene',read('video_ticks'),16);write('message1',0);write('scene',0,168);write('dirty',1)
def shot(name):e.run(16);e.screenshot(name)
def menu_item(index):
 for _ in range(index):e.tap(5)
 e.tap(8)
def menu_key():return 2 if (read('ui',4) if read('ui') else e.state()[3])==14 else 3

def help_open():e.tap(menu_key());menu_item(1)
def filled_answer(data):
 e.poke(80,len(data));c.memmove(e.ramgame+352,data+b'\0',len(data)+1)

try:
 boot();e.tap(menu_key());check('title START opens menu at Play',e.state()[3]==23 and read('ui',8)==0)
 shot('menu-title-v11.png');menu_item(1)
 check('title help opens',e.state()[3]==11)
 shot('help-v11.png');help_frame=e.raw;draws=read('rendered_frames');e.run(90)
 check('single-screen help waits without redrawing',e.state()[3]==11 and read('rendered_frames')==draws)
 e.tap(7);e.tap(6);e.run(16)
 check('help has no paging or redundant directional redraws',e.raw==help_frame and read('rendered_frames')==draws)
 e.tap(0);check('B from help restores title menu selection',e.state()[3]==23 and read('ui',8)==1)
 e.tap(5);e.tap(8);check('records open through menu',e.state()[3]==12)
 e.tap(0);check('records return to their source menu',e.state()[3]==23 and read('ui',8)==2)
 e.tap(5);e.tap(5);check('title menu wraps after its four entries',e.state()[3]==23 and read('ui',8)==0)
 e.tap(4);check('title menu wraps back to Authors',read('ui',8)==3)
 e.tap(10);check('L only toggles sound in menu',e.state()[3]==23 and read('sound_on')==0)
 e.tap(menu_key());check('START closes nested viewer menu to title',e.state()[3]==0)
 e.tap(10);check('L on title only changes sound',e.state()[3]==0 and read('sound_on')==1)
 e.tap(11);check('R has no title action',e.state()[3]==0)
 e.tap(2);check('SELECT has no title action',e.state()[3]==0)
 e.tap(3);check('START opens title menu',e.state()[3]==23);e.tap(8);check('A begins a new game from menu',e.state()[3]==15)

 # Restart is destructive only after an explicit second choice and A.
 fixture(2);before=e.state();e.tap(menu_key())
 for _ in range(3):e.tap(5)
 e.run(120,(8,));e.run(1)
 check('held menu A cannot accept restart confirmation',e.state()[3]==25 and read('ui',28)==0)
 shot('restart-confirm-v11.png');draws=read('rendered_frames');e.run(300)
 check('restart warning waits without redrawing or advancing the game',e.state()[3]==25 and read('rendered_frames')==draws and e.state()[2]==before[2] and e.state()[74]==before[74])
 e.tap(8);check('default A returns to the selected pause menu item',e.state()[3]==23 and read('ui',8)==3)
 e.tap(8);e.tap(0);check('B cancels restart back to menu',e.state()[3]==23 and read('ui',8)==3)
 e.tap(8);e.tap(menu_key());check('START cancels restart back to menu',e.state()[3]==23 and read('ui',8)==3)
 e.tap(menu_key());check('cancelled restart resumes the same spin and RNG',e.state()[3]==2 and e.state()[2]==before[2] and e.state()[74]==before[74])
 fixture(5);e.poke(80,2);c.memmove(e.ramgame+352,b'AB\0',3);before=c.string_at(e.ramgame+352,21)
 e.tap(menu_key());menu_item(3);e.run(180);e.tap(0);e.tap(menu_key())
 check('cancelled restart preserves typed answer',e.state()[3]==5 and e.state()[80]==2 and c.string_at(e.ramgame+352,21)==before)
 fixture(7);e.poke(81,0);e.poke(82,1);e.poke(83,1000000);e.tap(8);e.run(140)
 e.tap(menu_key());menu_item(3);canvas=memory('cash_canvas',38400);bills=read('cash');e.run(180)
 check('restart warning freezes cash without losing banknotes',e.state()[3]==25 and read('cash')==bills and memory('cash_canvas',38400)==canvas)
 e.tap(menu_key());e.tap(menu_key());e.run(30)
 check('cancelled warning continues the same cash payout',e.state()[3]==21 and read('cash')>bills)

 for mode in (1,3,4,7,8,5,14,15,16,17,18,19,21,22):
  fixture(mode);e.poke(76,23);before=memory('game',376)
  e.tap(menu_key())
  if mode==1:shot('menu-pause-v11.png')
  menu_item(1);e.run(16);body_bytes=150*240*(4 if e.format==1 else 2)
  check(f'mode {mode} opens the same compact help',e.state()[3]==11 and e.raw[:body_bytes]==help_frame[:body_bytes])
  clock=read('scene',4);since=read('ui',16);e.run(180);e.tap(0)
  check(f'mode {mode} B returns to paused menu',e.state()[3]==23)
  e.run(60);e.tap(menu_key())
  shifted=read('scene',4)-clock
  check(f'mode {mode} nested pause shifts clocks exactly once',shifted>=240 and abs(shifted-(read('video_ticks')-since))<=8)
  check(f'mode {mode} restores scene and wait',e.state()[3]==mode and e.state()[76]==23)
  check(f'mode {mode} preserves answer and selection',memory('game',376)[352:373]==before[352:373] and e.state()[70]==0 and e.state()[81]==1)

 fixture();e.tap(2);check('SELECT has no gameplay action',e.state()[3]==1)
 e.tap(6);e.tap(8);e.poke(80,len(word)-1)
 c.memmove(e.ramgame+352,word[:-1]+b'\0\0',len(word)+1);e.poke(70,word[-1]-128)
 e.run(120,(8,));check('holding last letter A cannot submit',e.state()[3]==5 and memory('game',376)[352:352+len(word)]==word)
 e.run(1);e.tap(0);check('B edits the completed word',e.state()[3]==5 and e.state()[80]==len(word)-1)
 e.tap(8);e.tap(3);check('START pauses a complete word without submitting',e.state()[3]==23);e.tap(3);check('START resumes a complete word without submitting',e.state()[3]==5)
 e.tap(8);check('next distinct A submits completed word',e.state()[3]==9)

 def result_case(reason,player):
  fixture(3,player)
  if reason in (2,3):
   e.poke(3,2);write('scene',2 if reason==2 else 14,156);e.tap(8)
  elif reason in (1,4):
   target=next(i for i in range(32) if (128+i in word)==(reason==4))
   e.poke(72,3 if reason==4 else 0)
   if player==2:e.poke(70,target);e.tap(8)
   else:
    e.poke(3,18);write('scene',target,144);write('scene',read('video_ticks')-120,4);e.until(lambda s:s[3]!=18)
   if reason==4:e.tap(8)
  elif reason==5:
   e.poke(3,8 if player==2 else 22)
   if player==2:e.tap(8)
   else:write('scene',read('video_ticks')-90,4);e.until(lambda s:s[3]!=22)
  else:
   e.poke(3,5);filled_answer(b'\x80'*len(word));e.tap(8)
  check(f'result {reason}, player {player} records explicit reason',e.state()[3]==6 and read('result_reason')==reason)

 def deadline(name,duration,mode,destination):
  # Leave headroom for one complete bitmap render before the boundary.
  write('scene',read('video_ticks')-duration+30,4);e.run(8)
  check(name+' waits before deadline',e.state()[3]==mode)
  e.tap(menu_key());e.run(180);e.tap(5);e.tap(8);e.run(90);e.tap(menu_key())
  check(name+' pause preserves remaining deadline',e.state()[3]==mode)
  started=read('scene',4);e.until(lambda s:s[3]!=mode,limit=60)
  elapsed=read('video_ticks')-started
  check(name+' advances at its own deadline',e.state()[3]==destination and duration<=elapsed<=duration+12)

 for player in (0,1):
  for mode,destination in ((1,2),(3,18),(4,18),(8,22),(22,6),(18,16)):
   fixture(mode,player);write('scene',word[0]-128,144)
   deadline(f'AI {player} message in mode {mode}',180,mode,destination)
 fixture(22,0);write('scene',read('video_ticks')-30,4);e.tap(8)
 check('fresh A accelerates AI chest reply without choosing its side',e.state()[3]==6 and e.state()[81]==1)

 for reason,duration in ((1,180),(2,180),(3,240),(4,180),(5,180),(6,240)):
  for player in ((0,1,2) if reason!=6 else (2,)):
   result_case(reason,player);deadline(f'result {reason}, player {player}',duration,6,8 if reason==4 else 10 if reason==6 else 1)
   result_case(reason,player);e.tap(8);check(f'result {reason}, player {player} A accelerates once',e.state()[3]==(8 if reason==4 else 10 if reason==6 else 1))
 fixture(5);e.poke(4,2);filled_answer(word);e.tap(8)
 deadline('final congratulations',300,9,19)
 fixture(7);e.poke(82,4);e.tap(8);deadline('Prize announcement',180,10,19)
 for mode,round_no,deal in ((9,0,0),(9,1,0),(10,0,0)):
  fixture(mode);e.poke(4,round_no);e.poke(82,deal);e.run(900)
  check(f'mode {mode}, round {round_no} still requires A',e.state()[3]==mode)
 fixture(7);e.poke(81,0);e.poke(82,1);e.poke(83,1000);e.tap(8);e.tap(8);e.run(900)
 check('completed payout waits for another A',e.state()[3]==21 and read('cash')==read('cash',4))
 e.tap(8);check('completed payout A reaches farewell once',e.state()[3]==10)

 # Cancel a real qualifying record at several insertion positions. Neither
 # the RAM ranking nor SRAM may retain a half-entered record.
 for position in (0,3,7):
  boot();scores=list(struct.unpack('<8i',memory('record_scores',32)));old_names=memory('record_names',88)
  saved=c.string_at(e.core.retro_get_memory_data(0),128)
  score=scores[position]+1
  for i,v in {3:9,4:2,5:2,6:0,11:score}.items():e.poke(i,v)
  e.tap(8)
  for _ in range(4):e.tap(8)
  check(f'qualifying record at {position} requests name',e.state()[3]==14)
  e.tap(8);e.tap(11);check('R inserts a space in name',e.state()[80]==2 and memory('game',376)[353]==32)
  help_open();check('name help never saves through START',e.state()[3]==11)
  e.tap(3);check('START in help does not save name',e.state()[3]==11)
  e.tap(2);check('SELECT closes nested name help without saving',e.state()[3]==14 and e.state()[80]==2)
  help_open()
  e.tap(0);e.tap(5);e.tap(5);e.tap(8)
  check('pending record remains intact while restart confirmation is open',e.state()[3]==25 and e.state()[80]==2)
  e.tap(5);e.tap(8)
  check(f'cancel record at {position} restores full RAM table',e.state()[3]==0 and memory('record_names',88)==old_names and list(struct.unpack('<8i',memory('record_scores',32)))==scores)
  check(f'cancel record at {position} leaves SRAM unchanged',c.string_at(e.core.retro_get_memory_data(0),128)==saved)

 def silent(name):
  e.run(20);e.audio.clear();e.run(80)
  values=[v for pair in struct.iter_unpack('<hh',b''.join(e.audio)) for v in pair]
  check(name+' produces exact zero stereo samples',bool(values) and not any(values))
  check(name+' has zero synthesized FIFO',memory('fifo',32)==bytes(32))
 fixture(2);e.poke(74,100);e.poke(75,5);e.tap(10);silent('muted repeated wheel tones')
 help_open();e.tap(10);check('L enables sound inside help',read('sound_on')==1)
 e.tap(10);shot('help-muted-v11.png');silent('muted help')
 e.tap(menu_key());check('mute survives nested help and resume',e.state()[3]==2 and read('sound_on')==0)
 fixture(7);e.poke(81,0);e.poke(82,1);e.poke(83,1000000);e.tap(8);e.tap(10);e.run(140)
 silent('muted banknote stream');check('banknote stream still advances while muted',read('cash')>100)
 fixture();e.tap(10);e.poke(81,0);e.tap(8);silent('muted new speech effect')
 # Queue keeps its timeline while muted; turning on reveals only its tail.
 c.memmove(e.ram+e.sym['notes']-0x02000000,struct.pack('<HH',440,500),4)
 for field,value in (('index',0),('remaining',0),('count',1)):write(field,value)
 e.run(10);remaining=read('remaining');e.tap(10);e.audio.clear();e.run(8)
 check('unmute restores current active tone',any(any(b) for b in e.audio) and 0<read('remaining')<remaining)
 e.run(50);e.audio.clear();e.run(30);check('unmute never replays expired notes',not any(any(b) for b in e.audio))
 fixture();e.tap(10);e.tap(menu_key());menu_item(3);e.tap(5);e.tap(8);e.tap(8)
 check('mute persists through title and new game',e.state()[3]==15 and read('sound_on')==0)

 # Actual PPU icon remains confined to its backing on every kind of screen.
 for mode in (0,1,5,11,12,14,19,21,23):
  fixture(mode);e.run(24);before=e.raw;e.tap(10);e.run(24);after=e.raw
  if mode in (1,5,11,12,14,19,23):
   size=4 if e.format==1 else 2
   changed=[p for p in range(240*160) if before[p*size:(p+1)*size]!=after[p*size:(p+1)*size]]
   check(f'mode {mode} mute badge changes only its corner',changed and all(1<=p%240<15 and 1<=p//240<13 for p in changed))
  draws=read('rendered_frames');e.run(90)
  if mode in (5,11,12,14,19,23):check(f'muted mode {mode} remains event rendered',read('rendered_frames')==draws)
  if mode==1:shot('game-muted-v11.png')
  if mode==14:shot('name-controls-v11.png')
finally:e.close()

report=dict(status='passed',count=len(checks),checks=checks,rom_sha256=hashlib.sha256(rom).hexdigest())
(ROOT/'build/qa/controls-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:v for k,v in report.items() if k!='checks'}))
