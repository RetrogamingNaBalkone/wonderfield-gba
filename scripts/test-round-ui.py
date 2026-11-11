"""Exercise round introductions and render compact counters in mGBA."""
import hashlib,json,runpy,struct
from emulator import Emulator,ROOT
m=runpy.run_path(str(ROOT/'scripts/test-multiplayer.py'))
read,write,tap=m['read'],m['write'],m['tap']
def put(e,name,offset,value):
 data=bytearray(read(e,name,180 if name=='scene' else 64 if name=='match' else 24));struct.pack_into('<I',data,offset,value&0xffffffff);write(e,name,data)
def integer(e,name):return struct.unpack('<I',read(e,name,4))[0]
rom=(ROOT/'build/gba/pole.gba').read_bytes()
def message(e,name):
 offset=integer(e,name)-0x08000000
 return rom[offset:rom.index(b'\0',offset)].decode('cp866')
checks=[]
for rule,round_no in ((0,1),(0,3),(1,2),(2,1),(2,10),(2,14)):
 e=Emulator();m['options'](e,3);put(e,'prefs',16,rule);tap(e,8)
 for _ in range(3):m['accept_name'](e)
 if round_no>1:
  e.poke(4,round_no-2);e.poke(3,17)
  put(e,'scene',12,integer(e,'video_ticks')-601);e.run(8)
 assert e.state()[3]==15 and e.state()[4]==round_no-1
 if round_no==1:
  assert integer(e,'message1')==e.sym['msg_1011']
  assert integer(e,'message2')==e.sym['msg_101d']
 else:
  assert message(e,'message1')=='Следующий'
  assert message(e,'message2')=='раунд'
 e.screenshot(f'round-ui-{rule}-{round_no}-intro.png')
 e.poke(3,1);write(e,'message1',struct.pack('<I',0));put(e,'scene',168,0)
 write(e,'dirty',struct.pack('<I',1));e.run(10)
 e.screenshot(f'round-ui-{rule}-{round_no}-board.png')
 if rule==2 and round_no==14:
  put(e,'match',52,2);put(e,'match',56,2);e.poke(3,36)
  write(e,'dirty',struct.pack('<I',1));e.run(10);e.screenshot('round-ui-winner.png')
 checks.append(dict(rule=rule,round=round_no,original_intro=round_no==1));e.close()
report=dict(rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),checks=checks)
(ROOT/'docs/verification/round-ui-tests.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps(report,indent=2))
