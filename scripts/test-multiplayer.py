"""mGBA ROM integration checks. MGBA_LIBRETRO selects the installed core."""
import ctypes as c, json, struct
from emulator import Emulator, ROOT

def read(e,name,n):
 if name=='prefs' and name not in e.sym:return b''.join(c.string_at(e.ram+e.sym[f'prefs.{i}']-0x02000000,4) for i in range(n//4))
 return c.string_at(e.ram+e.sym[name]-0x02000000,n)
def write(e,name,data):
 if name=='prefs' and name not in e.sym:
  for i in range(len(data)//4):c.memmove(e.ram+e.sym[f'prefs.{i}']-0x02000000,bytes(data[i*4:i*4+4]),4)
 else:c.memmove(e.ram+e.sym[name]-0x02000000,bytes(data),len(data))
def mp(e):return struct.unpack('<7i',read(e,'mp',28))
def setmp(e,index,value):
 data=bytearray(read(e,'mp',64));struct.pack_into('<i',data,index*4,value);write(e,'mp',bytes(data))
def tap(e,k):e.run(15,(k,));e.run(15)
def accept_name(e):
 if not e.state()[80]:
  for _ in range((mp(e)[4]+1)%3):tap(e,7)
  tap(e,8)
 tap(e,3);assert e.state()[3]==33
 tap(e,8)
def options(e,humans=1,link=False):
 e.run(100);tap(e,8);assert e.state()[3]==26
 for _ in range(0 if humans==1 else 2 if link else 1):tap(e,5)
 tap(e,8)
 if humans>1 and not link:
  assert e.state()[3]==34
  if humans==3:tap(e,5)
  tap(e,8)
 assert e.state()[3]==32

def select_option(e,setting):
 for _ in range(6):
  if struct.unpack('<4i',read(e,'prefs',16))[3]==setting:return
  tap(e,5)
 raise AssertionError('Setting not reachable')

def menu(e,choice):
 options(e,1 if choice==0 else 2+(choice-1)%2,choice>=3)
 tap(e,8)
def check(humans):
 e=Emulator();menu(e,humans-1)
 assert e.state()[3]==27
 # 10-character bound, deletion, space, and START accept.
 for _ in range(12):tap(e,8)
 assert e.state()[80]==10,e.state()[85:100] # 10-character Pascal name limit
 tap(e,0);tap(e,11);accept_name(e)
 assert mp(e)[4]==0
 accept_name(e)
 if humans==3:assert mp(e)[4]==1;accept_name(e)
 assert mp(e)[0]==humans
 assert e.state()[5]==2, "Player one must start multiplayer"
 # Fixtures isolate subsequent human turns.
 e.poke(3,1);e.poke(5,2);setmp(e,2,2);e.run(30)
 assert mp(e)[2]==2
 # Wrong full-word guess excludes just player one, then turns to player two.
 e.poke(3,5);e.poke(5,2);e.poke(80,20) # confirm through completed-input fixture
 # Get actual answer length from generated word table via word id.
 words=json.loads((ROOT/'assets/words-expanded.json').read_text());n=len(words[e.state()[6]]['word'])
 e.poke(80,n)
 tap(e,8);assert mp(e)[6]&4,mp(e)
 e.run(280);assert e.state()[3]==35 and e.state()[5]==2,e.state()[:12]
 e.run(200);assert e.state()[5]==0,e.state()[:12]
 assert e.state()[3]==28,e.state()[:12]
 assert mp(e)[2]==0
 tap(e,8);assert e.state()[3]==1
 e.screenshot(f'mp-{humans}-perspective-player2.png')
 # Next participant is AI in two-human mode; third human rotates in three-human mode.
 e.poke(3,6);e.poke(77,1);e.poke(78,1);tap(e,8)
 assert e.state()[5]==1,e.state()[:12]
 assert mp(e)[2]==(1 if humans==3 else 0)
 assert e.state()[3]==(28 if humans==3 else 1)
 e.screenshot(f'mp-{humans}-third-turn.png')
 e.close()
 return {'humans':humans,'name_limit':True,'wrong_word_elimination':True,'perspective':True,'ai_third':humans==2}
if __name__=='__main__':
 print(check(2));print(check(3))

def tournament():
 e=Emulator();options(e,3)
 select_option(e,4) # rounds
 for _ in range(5):tap(e,7)
 select_option(e,5);tap(e,8);accept_name(e);accept_name(e);accept_name(e)
 records=read(e,'record_names',88)+read(e,'record_scores',32)
 picked=[]
 for stage in range(8):
  assert e.state()[4]==stage,e.state()[:12]
  picked.append(e.state()[6]);assert 0<=picked[-1]<686
  e.poke(3,9);e.poke(5,0);e.poke(9,9000);e.poke(79,1)
  e.run(20);assert e.state()[3]==9
  tap(e,8);assert e.state()[3]==36
  tap(e,8)
  if stage<7:
   assert e.state()[3]==17;e.run(620)
  else:assert e.state()[3]==19
 assert len(set(picked))==8
 for _ in range(4):tap(e,8)
 assert e.state()[3]==0,e.state()[:12]
 assert read(e,'record_names',88)+read(e,'record_scores',32)==records
 e.close();return {'eight_rounds':True,'unique_words':picked,'no_multiplayer_records':True}

def plus_series(humans):
 e=Emulator()
 if humans==1:
  options(e);tap(e,8)
 else:
  menu(e,humans-1);accept_name(e);accept_name(e)
  if humans==3:accept_name(e)
 # Third spin is Plus; stop_spin must count it only in multiplayer.
 e.poke(3,2);e.poke(5,2);e.poke(6,0);e.poke(72,2)
 for i in range(20):e.poke(18+i,0)
 for i in range(32):e.poke(38+i,0)
 # Original wheel sector with value 100, from generated ROM table.
 rom=(ROOT/'build/gba/pole.gba').read_bytes()
 def table(name,n):return struct.unpack_from('<'+'h'*n,rom,e.sym[name]-0x08000000)
 sectors=table('wheel_sectors',16);values=table('sector_values',12)
 sector=next(i for i,s in enumerate(sectors) if values[s-4]==100)
 data=bytearray(read(e,'scene',180));struct.pack_into('<i',data,156,sector);write(e,'scene',bytes(data))
 tap(e,8);assert e.state()[3]==4,e.state()[:12]
 assert e.state()[72]==(2 if humans==1 else 3)
 tap(e,8);e.run(300)
 if humans==1:assert e.state()[3]==1,e.state()[:12]
 else:assert e.state()[3] in (6,8),e.state()[:12]
 e.close();return {'humans':humans,'plus_count_and_bonus':True}
if __name__=='__main__':
 print(tournament())
 print(plus_series(1));print(plus_series(2));print(plus_series(3))

def parameters(humans):
 e=Emulator();options(e,humans)
 assert e.state()[3]==32
 defaults=struct.unpack('<4i',read(e,'prefs',16));assert defaults==(int(humans>1),int(humans>1),int(humans>1),5 if humans>1 else 3)
 e.screenshot(f'parameters-{humans}-defaults.png')
 for setting in range(3):
  select_option(e,setting);tap(e,7)
 custom=struct.unpack('<4i',read(e,'prefs',16));assert custom[:3]==(int(humans==1),)*3
 select_option(e,5 if humans>1 else 3)
 tap(e,8)
 if humans>1:
  accept_name(e);accept_name(e)
  if humans==3:accept_name(e)
 assert e.state()[3]==15
 assert 0<=e.state()[6]<(686 if humans==1 else 495)
 e.close();return {'humans':humans,'defaults':defaults[:3],'overrides':custom[:3]}
if __name__=='__main__':
 for humans in (1,2,3):print(parameters(humans))

def cancel_cable_wait():
 e=Emulator();options(e,2,True);tap(e,8);tap(e,8);tap(e,3);tap(e,8)
 records=read(e,'record_names',88)+read(e,'record_scores',32)
 for delay in (1,120):
  assert e.state()[3]==30
  e.run(delay)
  assert e.state()[3]==30
  e.run(4,(0,))  # B must interrupt the SIO wait, not wait for its timeout.
  assert e.state()[3]==26
  assert read(e,'link_active',1)==b'\0'
  e.run(40,(0,));e.run(10)
  assert e.state()[3]==26  # No queued B tap escapes to the title screen.
  assert mp(e)[5]==2  # Keep the cable mode selected for another attempt.
  assert read(e,'record_names',88)+read(e,'record_scores',32)==records
  if delay==1:
   tap(e,8);assert e.state()[3]==32
   tap(e,8);tap(e,8);tap(e,3);tap(e,8)
 e.close();return {'cable_wait_cancel':True,'retry':True,'records_unchanged':True}

if __name__=='__main__':
 print(cancel_cable_wait())
