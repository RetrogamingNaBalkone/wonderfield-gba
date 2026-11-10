"""Minimal headless libretro frontend; all emulation is performed by mGBA."""
import ctypes as c,struct,zlib,binascii,os
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
class MemoryDescriptor(c.Structure):_fields_=[('flags',c.c_uint64),('ptr',c.c_void_p),('offset',c.c_size_t),('start',c.c_size_t),('select',c.c_size_t),('disconnect',c.c_size_t),('length',c.c_size_t),('addrspace',c.c_char_p)]
class MemoryMap(c.Structure):_fields_=[('descriptors',c.POINTER(MemoryDescriptor)),('count',c.c_uint)]
class Info(c.Structure):_fields_=[('path',c.c_char_p),('data',c.c_void_p),('size',c.c_size_t),('meta',c.c_char_p)]
class Variable(c.Structure):_fields_=[('key',c.c_char_p),('value',c.c_char_p)]
class Geometry(c.Structure):_fields_=[('width',c.c_uint),('height',c.c_uint),('max_width',c.c_uint),('max_height',c.c_uint),('aspect',c.c_float)]
class Timing(c.Structure):_fields_=[('fps',c.c_double),('rate',c.c_double)]
class AVInfo(c.Structure):_fields_=[('geometry',Geometry),('timing',Timing)]
ENV=c.CFUNCTYPE(c.c_bool,c.c_uint,c.c_void_p)
VIDEO=c.CFUNCTYPE(None,c.c_void_p,c.c_uint,c.c_uint,c.c_size_t)
AUDIO=c.CFUNCTYPE(None,c.c_int16,c.c_int16)
BATCH=c.CFUNCTYPE(c.c_size_t,c.POINTER(c.c_int16),c.c_size_t)
POLL=c.CFUNCTYPE(None)
INPUT=c.CFUNCTYPE(c.c_int16,c.c_uint,c.c_uint,c.c_uint,c.c_uint)
def symbols(path=None):
 b=Path(path or ROOT/'build/gba/pole.elf').read_bytes();off=struct.unpack_from('<I',b,32)[0];size,n=struct.unpack_from('<HH',b,46);ss=[struct.unpack_from('<10I',b,off+i*size) for i in range(n)];result={}
 for s in ss:
  if s[1]!=2:continue
  t=ss[s[6]];strings=b[t[4]:t[4]+t[5]]
  for q in range(s[4],s[4]+s[5],s[9]):
   name,value,sz,info,other,ndx=struct.unpack_from('<IIIBBH',b,q)
   if name:result[strings[name:strings.index(0,name)].decode()]=value
 return result
class Emulator:
 def __init__(self,rom_path=None,elf_path=None):
  core=os.environ.get('MGBA_LIBRETRO')
  if not core:
   if os.name=='nt':core=str(Path(os.environ['LOCALAPPDATA'])/'Programs/mGBA/libretro-20261024/mgba_libretro.dll')
   else:core=str(Path(os.environ.get('WONDERFIELD_MGBA_DIR','/workspace/.tools/mgba'))/'mgba_libretro.so')
  if not Path(core).is_file():raise RuntimeError('mGBA core not found; set MGBA_LIBRETRO to its full path')
  self.core=c.CDLL(core);self.keys=set();self.format=0;self.raw=b'';self.variables={};self.samples=0;self.nonzero=0;self.errors=[];self.audio=[]
  self.directory=os.fsencode(str(ROOT/'build/gba'))
  self.callbacks=[ENV(self.env),VIDEO(self.video),AUDIO(lambda l,r:None),BATCH(self.batch),POLL(lambda:None),INPUT(lambda p,d,i,b:int(p==0 and d==1 and b in self.keys))]
  for name,cb in zip(('environment','video_refresh','audio_sample','audio_sample_batch','input_poll','input_state'),self.callbacks):
   fn=getattr(self.core,'retro_set_'+name);fn.argtypes=[type(cb)];fn(cb)
  self.core.retro_get_memory_data.argtypes=[c.c_uint];self.core.retro_get_memory_data.restype=c.c_void_p
  self.core.retro_load_game.argtypes=[c.POINTER(Info)];self.core.retro_load_game.restype=c.c_bool
  self.core.retro_init();rom=Path(rom_path or ROOT/'build/gba/pole.gba');data=rom.read_bytes();self.buf=c.create_string_buffer(data);self.info=Info(os.fsencode(str(rom)),c.cast(self.buf,c.c_void_p),len(data),None);assert self.core.retro_load_game(c.byref(self.info))
  self.ram=self.core.retro_get_memory_data(2) or self.mapped_ram;self.sym=symbols(elf_path);self.game_address=self.sym['game'];self.ramgame=self.ram+self.game_address-0x02000000
  av=AVInfo();self.core.retro_get_system_av_info.argtypes=[c.POINTER(AVInfo)];self.core.retro_get_system_av_info(c.byref(av));self.rate=int(av.timing.rate);self.fps=av.timing.fps
 def env(self,cmd,data):
  try:
   if cmd in (36,0x10024):
    maps=c.cast(data,c.POINTER(MemoryMap))[0]
    for i in range(maps.count):
     d=maps.descriptors[i]
     if d.start==0x02000000 and d.ptr:self.mapped_ram=d.ptr+d.offset
    return True
   if cmd in (9,31):c.cast(data,c.POINTER(c.c_char_p))[0]=self.directory;return True
   if cmd==10:self.format=c.cast(data,c.POINTER(c.c_int))[0];return True
   if cmd==16:
    v=c.cast(data,c.POINTER(Variable));i=0
    while v[i].key:self.variables[v[i].key]=v[i].value.split(b'; ')[1].split(b'|')[0];i+=1
    self.variables.update({b'mgba_use_bios':b'OFF',b'mgba_skip_bios':b'ON',b'mgba_frameskip':b'disabled'});return True
   if cmd==15:
    v=c.cast(data,c.POINTER(Variable))[0]
    if v.key not in self.variables:return False
    v.value=self.variables[v.key];return True
   if cmd in (17,3):c.cast(data,c.POINTER(c.c_bool))[0]=cmd==3;return True
   if cmd in (39,52):c.cast(data,c.POINTER(c.c_uint))[0]=0;return True
   return cmd in (11,18)
  except Exception as ex:self.errors.append(str(ex));return False
 def batch(self,data,n):
  raw=c.string_at(data,n*4);self.audio.append(raw);self.samples+=n;self.nonzero+=int(any(raw));return n
 def video(self,data,w,h,pitch):
  if data:self.w=w;self.h=h;self.raw=b''.join(c.string_at(data+y*pitch,w*(4 if self.format==1 else 2)) for y in range(h))
 def run(self,n=1,keys=()):
  self.keys=set(keys)
  for i in range(n):self.core.retro_run()
  assert not self.errors,self.errors
 def tap(self,button):
  previous=self.state()[1]
  for i in range(300):
   self.run(1,(button,))
   if self.state()[1]!=previous:break
  else:raise AssertionError('CPU stopped while pressing button')
  previous=self.state()[1]
  for i in range(300):
   self.run(1)
   if self.state()[1]!=previous:break
  else:raise AssertionError('CPU stopped while releasing button')
 def poke(self,index,value):c.memmove(self.ramgame+index*4,struct.pack('<i',value),4)
 def checkpoint(self):
  self.core.retro_serialize_size.restype=c.c_size_t
  self.core.retro_serialize.argtypes=[c.c_void_p,c.c_size_t];self.core.retro_serialize.restype=c.c_bool
  size=self.core.retro_serialize_size();data=c.create_string_buffer(size)
  assert self.core.retro_serialize(data,size)
  return data.raw,self.raw,set(self.keys)
 def restore(self,checkpoint):
  data,raw,keys=checkpoint;buffer=c.create_string_buffer(data,len(data))
  self.core.retro_unserialize.argtypes=[c.c_void_p,c.c_size_t];self.core.retro_unserialize.restype=c.c_bool
  assert self.core.retro_unserialize(buffer,len(data))
  self.raw=raw;self.keys=set(keys)
 def tap_seeded(self,button,seed):
  """RAM seed fixture at the draw boundary, retaining real timed key input.

  Replay the same full core state to measure the captured timing salt, then
  compensate the pre-input seed. Production input mixing stays enabled.
  Use only for TITLE/new-game or TURN/spin draws that mix input once.
  """
  if 'input_entropy' not in self.sym: # Archived ROMs used by pacing comparisons.
   value=seed&0xffffffff;self.poke(2,value if value<0x80000000 else value-0x100000000)
   self.tap(button);return
  checkpoint=self.checkpoint();self.tap(button)
  # Releases can update entropy after the draw; compensate the salt actually
  # consumed at seed_from_input, not the later input accumulator.
  salt_symbol=self.sym.get('input_seed_salt',self.sym['input_entropy'])
  salt=struct.unpack('<I',c.string_at(self.ram+salt_symbol-0x02000000,4))[0]
  self.restore(checkpoint)
  value=seed&0xffffffff
  if 'input_seed_counter' in self.sym:
   # Invert the production avalanche for an explicit effective-seed fixture.
   value^=value>>16
   value=value*pow(0x846ca68b,-1,1<<32)&0xffffffff
   value^=(value>>15)^(value>>30)
   value=value*pow(0x7feb352d,-1,1<<32)&0xffffffff
   value^=value>>16
  value^=salt;self.poke(2,value if value<0x80000000 else value-0x100000000)
  self.tap(button)
  assert struct.unpack('<I',c.string_at(self.ram+salt_symbol-0x02000000,4))[0]==salt
 def until(self,predicate,limit=5000):
  for i in range(limit):
   if predicate(self.state()):return
   self.run(1)
  raise AssertionError(('state timeout',self.state()[:12]))
 def state(self):return struct.unpack('<100i',c.string_at(self.ramgame,400))
 def screenshot(self,name):
  rgb=bytearray()
  for v, in struct.iter_unpack('<I' if self.format==1 else '<H',self.raw):
   if self.format==1:rgb.extend(((v>>16)&255,(v>>8)&255,v&255))
   else:
    g=6 if self.format==2 else 5;rgb.extend((((v>>(5+g))&31)*255//31,((v>>5)&((1<<g)-1))*255//((1<<g)-1),(v&31)*255//31))
  def chunk(t,d):return struct.pack('>I',len(d))+t+d+struct.pack('>I',binascii.crc32(t+d)&0xffffffff)
  raw=b''.join(b'\0'+rgb[y*self.w*3:(y+1)*self.w*3] for y in range(self.h))
  p=ROOT/'build/qa'/name;p.parent.mkdir(exist_ok=True)
  p.write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',self.w,self.h,8,2,0,0,0))+chunk(b'IDAT',zlib.compress(raw))+chunk(b'IEND',b''))
 def close(self):self.core.retro_unload_game();self.core.retro_deinit()
if __name__=='__main__':
 e=Emulator();e.run(90);print('title',e.state()[:12]);e.screenshot('title.png');e.tap(8);print('turn',e.state()[:12]);e.run(60);e.screenshot('turn.png');e.tap(8);e.run(600);print('after spin',e.state()[:12]);e.screenshot('after-spin.png');e.close()
