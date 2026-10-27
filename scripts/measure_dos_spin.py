"""Time the original spin in isolated, hidden DOSBox instances.

A RAM-only trampoline marks entry to 1000:2c6a. Its six original prologue
bytes execute unchanged. The original write to DS:084e marks the final sector.
No executable/resource files are patched, and the user emulator is untouched.
"""
from pathlib import Path
import struct,time,json,hashlib
from dos_capture import Api,ROOT,launch

base=ROOT/'build/reference/spin-timing';base.mkdir(parents=True,exist_ok=True)
original=ROOT/'originals/Wonderfield';exe=(original/'POLE.EXE').read_bytes()
header=struct.unpack_from('<H',exe,8)[0]*16;signature=exe[header+0xc792:header+0xc792+64]
results=[]
for index,cycles in enumerate((5000,20000)):
 port=9827+index
 with launch(cycles,port):
  api=Api(port);deadline=time.monotonic()+30
  while True:
   try:info=json.loads(api.get('dosbox/info'));break
   except OSError:
    if time.monotonic()>deadline:raise TimeoutError('DOSBox debug API startup')
    time.sleep(.1)
  ds=None
  while time.monotonic()<deadline:
   memory=api.memory(0,655360);position=memory.find(signature)
   while position>=0:
    if (position-2)%16==0:ds=position-2;break
    position=memory.find(signature,position+1)
   if ds is not None:break
   time.sleep(.1)
  if ds is None:raise AssertionError('Original DOS data segment not found')
  cs=(ds-0xc790)//16;entry=cs*16+0x2c6a;prologue=api.memory(entry,6)
  assert prologue==exe[header+0x2c6a:header+0x2c70],('prologue mismatch',prologue.hex())
  # Save flags/AX/ES, mark DS:084e as pending and ES:00f0 as entered, restore.
  shim=bytes.fromhex('9c5006b800708ec0c7064e08fe7f26c606f0000107589d')+prologue+bytes.fromhex('ea702c')+struct.pack('<H',cs)
  api.write(0x70000,shim);api.write(0x700f0,b'\0');api.write(entry,bytes.fromhex('ea0000007090'))
  deadline=time.monotonic()+60;last_key=0
  while api.memory(0x700f0,1)!=b'\1':
   if time.monotonic()>deadline:raise TimeoutError('Could not reach original spin from menus')
   if time.monotonic()-last_key>.75:api.key();last_key=time.monotonic()
   time.sleep(.02)
  start=time.monotonic();player=struct.unpack('<h',api.memory(ds+0x856,2))[0]
  print(f'DOS {cycles} cycles: entered original spin, player {player}',flush=True)
  samples=0;phases=set();deadline=start+120
  while True:
   value=struct.unpack('<h',api.memory(ds+0x84e,2))[0]
   if value!=0x7ffe:break
   phases.add(struct.unpack('<h',api.memory(ds+0x970,2))[0]);samples+=1
   if time.monotonic()>deadline:raise TimeoutError('Original spin did not finish')
   time.sleep(.01)
  elapsed=time.monotonic()-start
  result=dict(cpu_cycles=cycles,seconds=elapsed,player=player,sector_value=value,phase_samples=samples,
              distinct_phases=len(phases),dosbox_info=info,measurement='1000:2c6a entry to original DS:084e write, host monotonic clock, ~20 ms polling')
  results.append(result);print(json.dumps({k:v for k,v in result.items() if k!='dosbox_info'}),flush=True)
 assert hashlib.sha256((original/'POLE.EXE').read_bytes()).digest()==hashlib.sha256(exe).digest()
(base/'dos-spin-timing.json').write_text(json.dumps(dict(original_sha256=hashlib.sha256(exe).hexdigest(),results=results),indent=2))
