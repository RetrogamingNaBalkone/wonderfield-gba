"""High-score qualification, ties and SRAM persistence through real end screens."""
import ctypes as c,hashlib,json,struct
from emulator import Emulator,ROOT

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
scores=[8000,7000,6000,5000,4000,3000,2000,1000]
def save_image():
 data=bytearray(b'POL2')
 for i,score in enumerate(scores):data+=f'REC{i+1}'.encode().ljust(11,b'\0')+struct.pack('<I',score)
 h=2166136261
 for byte in data[4:]:h=((h^byte)*16777619)&0xffffffff
 return bytes(data)+struct.pack('<I',h)
original=save_image()
word=bytes.fromhex(json.loads((ROOT/'assets/words.json').read_text(encoding='utf8'))[0]['word_hex'])
e=Emulator();e.run(220)
def boot():
 c.memmove(e.core.retro_get_memory_data(0),original,len(original));e.core.retro_reset();e.run(120)
def records():return list(struct.unpack('<8i',c.string_at(e.ram+e.sym['record_scores']-0x02000000,32)))
def sram():return c.string_at(e.core.retro_get_memory_data(0),128)
def finish(score):
 for index,value in {3:5,4:2,5:2,6:0,11:score,80:len(word)}.items():e.poke(index,value)
 c.memmove(e.ramgame+352,word+b'\0',len(word)+1)
 e.tap(3)
 check(f'{score} final solved in studio before gift',e.state()[3]==9 and e.state()[79]==1)
 for name in ('message1','message2'):
  address=struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000,4))[0]
  check(f'{score} studio shows final congratulations {name}',address==e.sym['msg_f7b' if name=='message1' else 'msg_f8a'])
 e.run(100);check(f'{score} congratulations wait for confirmation',e.state()[3]==9)
 e.tap(8);check(f'{score} result shows gift before qualification',e.state()[3]==19)
 for _ in range(3):e.tap(8)
 check(f'{score} gift leads directly to qualification without studio return',e.state()[3] in (12,14))
 e.run(24)

for score in (0,100,600,999,1000):
 boot();finish(score)
 check(f'{score} does not request name at or below eighth place',e.state()[3]==12)
 check(f'{score} leaves all eight records unchanged',records()==scores)
 check(f'{score} leaves saved records unchanged',sram()==original)
 e.tap(8);check(f'{score} records return to title',e.state()[3]==0)
for score in (1001,5000,9000):
 boot();finish(score);position=sum(old>=score for old in scores)
 expected=(scores[:position]+[score]+scores[position:])[:8]
 check(f'{score} requests name only after entering top eight',e.state()[3]==14)
 check(f'{score} is inserted at correct position, after ties',records()==expected)
 e.tap(8);e.tap(3);e.run(24)
 check(f'{score} name confirmation returns to records',e.state()[3]==12)
 e.tap(8);check(f'{score} saved records return to title',e.state()[3]==0)
 saved=sram();e.core.retro_reset();e.run(120)
 check(f'{score} ranking survives console reset',records()==expected and sram()==saved)
 if score==9000:
  finish(1001)
  check('next result is compared with updated eighth place',e.state()[3]==12 and records()==expected and sram()==saved)

# A loss and a Prize exit do not accidentally use a previous winning entry.
boot()
for index,value in {3:6,5:2,11:9000,77:10,78:2}.items():e.poke(index,value)
e.tap(8);check('loss follows farewell without name input',e.state()[3]==10)
e.tap(8);check('loss returns to title without editing records',e.state()[3]==0 and sram()==original)
boot()
for index,value in {3:7,5:2,81:0,82:1,83:1000000}.items():e.poke(index,value)
e.tap(8);e.tap(8);e.until(lambda s:s[3]==21)
e.tap(8);check('cash exit shows farewell rather than requesting name',e.state()[3]==10)
e.tap(8);check('cash exit leaves high-score SRAM intact',e.state()[3]==0 and sram()==original)
e.close()
rom=(ROOT/'build/gba/pole.gba').read_bytes()
report=dict(status='passed',count=len(checks),checks=checks,rom_sha256=hashlib.sha256(rom).hexdigest(),
 initial_scores=scores,qualification='strictly above eighth place; equal results do not displace it')
(ROOT/'build/qa/records-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:v for k,v in report.items() if k!='checks'}))
