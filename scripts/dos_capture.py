"""Run an isolated original under DOSBox's existing local debug HTTP service."""
from pathlib import Path
import os,subprocess,shutil,time,urllib.request,json,struct,tempfile
from contextlib import contextmanager, ExitStack
ROOT=Path(__file__).resolve().parents[1]
DIR=ROOT/'build/reference'
class Api:
 def __init__(self,port=9819):self.url=f'http://127.0.0.1:{port}/api/v1/'
 def get(self,path):
  with urllib.request.urlopen(self.url+path,timeout=5) as r:return r.read()
 def put(self,path,data):
  req=urllib.request.Request(self.url+path,data=data,method='PUT',headers={'Content-Type':'application/octet-stream'})
  with urllib.request.urlopen(req,timeout=5) as r:return r.read()
 def memory(self,address,n):return self.get(f'memory/{address}/{n}')
 def write(self,address,b):return self.put(f'memory/{address}',b)
 def key(self,ascii=32,scan=0x39):
  head,tail=struct.unpack('<HH',self.memory(0x41a,4));self.write(0x400+tail,bytes((ascii,scan)));tail+=2
  if tail>=0x3e:tail=0x1e
  self.write(0x41c,struct.pack('<H',tail))
 def capture(self,name):
  # Temporary IRQ8 shim copies the EGA read planes while guest drawing is stopped.
  # Only the isolated emulator's RAM is touched; original files stay unchanged.
  old=self.memory(0x20,4);code=bytearray.fromhex('fa505152535556571e06fc')
  code+=bytes.fromhex('31c08ed8c7062000')+old[:2]+bytes.fromhex('c7062200')+old[2:]
  for plane in range(4):
   code+=bytes.fromhex('bace03b004ee42b0')+bytes([plane])+bytes.fromhex('eeb800a08ed8b8')+struct.pack('<H',0x8000+1750*plane)+bytes.fromhex('8ec031f631ffb9606df3a4')
  code+=bytes.fromhex('bace03b004ee42b000ee31c08ed8c606000301071f5f5e5d5b5a5958ea')+old
  self.write(0x70300,b'\0');self.write(0x70000,code);self.write(0x20,struct.pack('<HH',0,0x7000))
  for _ in range(100):
   if self.memory(0x300,1)==b'\1':break
   time.sleep(.02)
  else:raise TimeoutError('EGA capture IRQ did not run')
  self.write(0x300,b'\0');planes=[self.memory(0x80000+28000*p,28000) for p in range(4)]
  pixels=[sum(((planes[p][y*80+x//8]>>(7-x%8))&1)<<p for p in range(4)) for y in range(350) for x in range(640)]
  from extract import png,EGA
  DIR.mkdir(parents=True,exist_ok=True)
  png(DIR/(name+'.png'),640,350,pixels,EGA);(DIR/(name+'.idx')).write_bytes(bytes(pixels))
@contextmanager
def launch(cycles=5000,port=9819):
 # Keep only captures/reports; copied games, configs and logs are temporary.
 DIR.mkdir(parents=True,exist_ok=True)
 with tempfile.TemporaryDirectory(prefix='dosbox-',dir=DIR) as temporary, ExitStack() as stack:
  directory=Path(temporary);game=directory/'game';game.mkdir()
  for p in (ROOT/'originals/Wonderfield').iterdir():shutil.copy2(p,game/p.name)
  cfg=directory/'dosbox.conf'
  cfg.write_text(f'''[dosbox]
machine = ega
[cpu]
core = normal
cpu_cycles = {cycles}
[mixer]
nosound = true
[webserver]
webserver_enabled = on
webserver_bind_address = 127.0.0.1
webserver_port = {port}
[autoexec]
mount c "{game}"
c:
pole.exe
''',encoding='ascii')
  exe=Path(os.environ['LOCALAPPDATA'])/'Programs/DOSBox-Staging/wasdify-webserver-20261024/dosbox.exe'
  env=dict(os.environ,SDL_VIDEODRIVER='dummy',SDL_AUDIODRIVER='dummy')
  logs=[stack.enter_context((directory/f'{s}.log').open('wb')) for s in ('stdout','stderr')]
  proc=subprocess.Popen([str(exe),'--noprimaryconf','--nolocalconf','-conf',str(cfg),'-noconsole'],env=env,cwd=directory,stdout=logs[0],stderr=logs[1],creationflags=subprocess.CREATE_NO_WINDOW)
  try:
   yield proc
  finally:
   if proc.poll() is None:
    proc.terminate()
    try:proc.wait(timeout=10)
    except subprocess.TimeoutExpired:proc.kill();proc.wait(timeout=5)
if __name__=='__main__':
 with launch():
  a=Api()
  for _ in range(50):
   try:print(a.get('dosbox/info').decode());break
   except OSError:time.sleep(.1)
  for route in ['video','video/info','video/screenshot','screenshot','openapi.json','debug','cpu/registers']:
   try:
    b=a.get(route);print(route,len(b),b[:150])
   except OSError as ex:print(route,str(ex))
