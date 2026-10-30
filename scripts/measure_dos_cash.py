"""Capture/time the original cash loop at 5000 cycles in an isolated DOSBox.

Only guest RAM is instrumented. A normal spin call is redirected to the
original negotiation; choice prompts accept the second cash offer. The drawing,
RNG, speaker and loop count execute as shipped. Originals are never patched.
"""
import hashlib,json,struct,time
from dos_capture import Api,ROOT,launch

def measure():
 exe=(ROOT/'originals/Wonderfield/POLE.EXE').read_bytes()
 header=struct.unpack_from('<H',exe,8)[0]*16
 signature=exe[header+0xc792:header+0xc7d2]
 with launch(5000,9831):
  api=Api(9831);deadline=time.monotonic()+30
  while True:
   try:info=json.loads(api.get('dosbox/info'));break
   except OSError:
    if time.monotonic()>deadline:raise TimeoutError('DOSBox startup')
    time.sleep(.1)
  ds=None
  while time.monotonic()<deadline:
   try:ram=api.memory(0,655360)
   except OSError:time.sleep(.1);continue
   p=ram.find(signature)
   if p>=0 and (p-2)%16==0:ds=p-2;break
   time.sleep(.1)
  assert ds is not None,'DOS data segment missing'
  cs=(ds-0xc790)//16;base=cs*16
  # Start spinning, decline the first cash offer, accept the second. This
  # gives 100 genuine draws for timing without changing the original loop.
  prompt=bytes.fromhex('5589e506b800708ec0837e0403751226803e060600750a26fe060606b80300eb0231c0075d')
  prompt+=b'\xea'+struct.pack('<HH',0x39fa,cs)
  api.write(0x70800,prompt)
  api.write(base+0x37eb,b'\xea'+struct.pack('<HH',0x800,0x7000))
  api.write(base+0x2c6a,b'\xe9'+struct.pack('<h',0x42b4-0x2c6d))
  original=api.memory(base+0x4431,5)
  assert original==exe[header+0x4431:header+0x4436]
  # Increment a 32-bit counter before each unmodified banknote iteration.
  count=bytes.fromhex('9c5006b800708ec026ff060006750526ff06020607589d')
  count+=original+b'\xea'+struct.pack('<HH',0x4436,cs)
  api.write(0x70200,count);api.write(0x70600,bytes(8))
  api.write(base+0x4431,b'\xea'+struct.pack('<HH',0x200,0x7000))
  # Stop on the completed picture so capture doesn't race the next screen.
  done=bytes.fromhex('5050b800708ec026c606040601ebfe')
  api.write(0x70400,done)
  api.write(base+0x448f,b'\xea'+struct.pack('<HH',0x400,0x7000))
  deadline=time.monotonic()+90;last_key=0;start=None;samples=[]
  while time.monotonic()<deadline:
   n,finished=struct.unpack('<IB',api.memory(0x70600,5))
   now=time.monotonic()
   if n and start is None:start=now
   if start is not None:samples.append((now-start,n))
   if finished:
    api.capture('original-cash-complete');break
   if not n and now-last_key>.7:api.key();last_key=now
   time.sleep(.005)
  else:raise TimeoutError(('original cash not completed',samples[-5:]))
  # Skip the partially observed first draw; no capture interrupts timing.
  first=next((s for s in samples if s[1]>=2),samples[0])
  last=next((s for s in samples if s[1]>=99),samples[-1])
  interval=(last[0]-first[0])/(last[1]-first[1])
  result=dict(original_sha256=hashlib.sha256(exe).hexdigest(),cpu_cycles=5000,
   banknotes=n,rubles=1000,seconds=samples[-1][0],seconds_per_banknote=interval,
   samples=samples,dosbox_info=info,method='RAM loop counter at 1000:4431; second cash offer; unmodified drawing loop; no captures during timing')
  (ROOT/'build/reference/dos-cash-timing.json').write_text(json.dumps(result,indent=2))
  print(json.dumps({k:v for k,v in result.items() if k not in ('samples','dosbox_info')}),flush=True)
 assert hashlib.sha256((ROOT/'originals/Wonderfield/POLE.EXE').read_bytes()).hexdigest()==result['original_sha256']
 return result

if __name__=='__main__':measure()
