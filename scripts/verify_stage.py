"""Side-wall occlusion, turn digits, exact-state spin replay and gift RNG.

The spin audit saves complete mGBA states during natural playback, restores
each one, and presses A. The sector visible before the press is identified
from actual PPU pixels, independently of the logical wheel position.
"""
from emulator import Emulator,ROOT
import ctypes as c,struct,json,hashlib,collections,zlib,binascii

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)
e=Emulator();e.run(220);e.tap(8)
while e.state()[3]==15:e.tap(8)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
palette=struct.unpack_from('<16H',rom,e.sym['palette']-0x08000000)
font8=(ROOT/'assets/font-8.bin').read_bytes()
stage=rom[e.sym['stage_background']-0x08000000:e.sym['stage_background']-0x08000000+38400]
def scene(off):return struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+off,4))[0]
def write_scene(off,value):c.memmove(e.ram+e.sym['scene']-0x02000000+off,struct.pack('<I',value),4)
def poke_rng(seed):e.poke(2,seed if seed<0x80000000 else seed-0x100000000)
def color(v):
 if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
 elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
 else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
 return r|(g<<5)|(b<<10)
def region(raw,x,y,w,h):
 size=4 if e.format==1 else 2;fmt='<I' if size==4 else '<H'
 return tuple(color(v) for yy in range(y,y+h) for v, in struct.iter_unpack(fmt,raw[(yy*240+x)*size:(yy*240+x+w)*size]))
def preview(name):
 pixels=region(e.raw,0,0,240,160);raw=bytearray()
 for y in range(160):
  row=bytearray()
  for v in pixels[y*240:(y+1)*240]:row+=bytes(((v&31)*255//31,((v>>5)&31)*255//31,((v>>10)&31)*255//31))*4
  raw+=(b'\0'+row)*4
 def chunk(t,b):return struct.pack('>I',len(b))+t+b+struct.pack('>I',binascii.crc32(t+b)&0xffffffff)
 (ROOT/'build/qa'/name).write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',960,640,8,2,0,0,0))+chunk(b'IDAT',zlib.compress(raw))+chunk(b'IEND',b''))
def reset_turn(sector=12):
 e.run(12)
 for i in range(20):e.poke(18+i,0)
 for i in range(32):e.poke(38+i,0)
 for i,v in {3:1,4:0,5:2,6:0,7:sector,11:0,70:0,71:0,72:0,76:0,79:0,81:1,82:0}.items():e.poke(i,v)

# A complete genuine reveal, including the partial frame behind the right wall.
reset_turn()
for i,v in {3:2,7:4,74:1,75:1,76:0}.items():e.poke(i,v)
write_scene(152,0);write_scene(156,3);e.until(lambda s:s[3]==3);e.poke(70,8);e.tap(8);e.run(12)
check('assistant waits beside board, beyond left wall',e.state()[3]==16 and scene(44)==32)
preview('assistant-left-wall.png')
left=tuple(palette[stage[y*240+x]] for y in range(12,57) for x in range(15))
right=tuple(palette[stage[y*240+x]] for y in range(12,56) for x in range(225,240))
check('left wall is not painted over by waiting assistant',region(e.raw,0,12,15,45)==left)
wall_ok=True;partial_seen=False;max_actor=32
for frame in range(2000):
 e.run(1);max_actor=max(max_actor,scene(44))
 if e.state()[3]!=16:break
 if scene(0)-scene(12)>=110:
  wall_ok &= region(e.raw,0,12,15,45)==left and region(e.raw,225,12,15,44)==right
  if scene(44)>=217:
   visible=region(e.raw,213,12,12,44)
   base=tuple(palette[stage[y*240+x]] for y in range(12,56) for x in range(213,225))
   if visible!=base:partial_seen=True;preview('assistant-right-wall.png')
else:raise AssertionError('assistant never exits')
check('both walls stay in front throughout assistant walk',wall_ok)
check('assistant is partially hidden at right wall before exit',partial_seen)
check('assistant finishes behind wall at x225, never screen edge x240',e.state()[3]==6 and max_actor==225)
check('wall exit still opens all three matching cells',sum(e.state()[18:38])==3 and e.state()[11]==30)

# The final cell of the longest word must open before the assistant vanishes.
words=json.loads((ROOT/'assets/words.json').read_text(encoding='utf8'));longest=max(range(len(words)),key=lambda i:len(words[i]['word']))
word=bytes.fromhex(words[longest]['word_hex']);chosen=word[-1]
reset_turn();e.poke(6,longest)
for i,ch in enumerate(word):e.poke(18+i,int(ch!=chosen))
for i,v in {3:2,7:1,74:1,75:1,76:0}.items():e.poke(i,v)
write_scene(152,0);write_scene(156,0);e.until(lambda s:s[3]==4);e.poke(70,len(word)-1);e.tap(8)
e.until(lambda s:s[18+len(word)-1]!=0);e.run(6)
font14=(ROOT/'assets/font-14.bin').read_bytes();x=30+((20-len(word))//2+len(word)-1)*9+1;pixels=region(e.raw,x,11,8,14)
expected=tuple(palette[0 if font14[chosen*14+y]&(128>>xx) else 7] for y in range(14) for xx in range(8))
check('last cell of longest word opens visibly before right wall',e.state()[3]==16 and scene(44)<225 and pixels==expected)
e.until(lambda s:s[3]!=16)

# Check complete glyph cells: the old code overprinted 2 or 3 over a printed 1.
reset_turn();write_scene(4,0);e.run(150)
for round_no in range(3):
 # A RAM fixture bypasses new_round()/set_mode(); request the redraw that
 # a real round transition already performs. No idle polling redraw now.
 e.poke(4,round_no);c.memmove(e.ram+e.sym['dirty']-0x02000000,struct.pack('<I',1),4)
 e.run(24);pixels=region(e.raw,186,35,24,8);text=f'{round_no+1}/3'.encode()
 expected=tuple(palette[0 if font8[ch*8+y]&(128>>x) else 7] for y in range(8) for ch in text for x in range(8))
 check(f'turn {round_no+1}/3 is a clean native glyph without overprinting',pixels==expected)
 preview(f'turn-counter-{round_no+1}.png')

# The complete core state includes CPU, IRQ input queue, video and RNG.
e.core.retro_serialize_size.restype=c.c_size_t;state_size=e.core.retro_serialize_size()
e.core.retro_serialize.argtypes=[c.c_void_p,c.c_size_t];e.core.retro_serialize.restype=c.c_bool
e.core.retro_unserialize.argtypes=[c.c_void_p,c.c_size_t];e.core.retro_unserialize.restype=c.c_bool
buffer=c.create_string_buffer(state_size)
bank=rom[e.sym['wheel_bitmaps']-0x08000000:e.sym['wheel_bitmaps']-0x08000000+32*128*112]
phases={tuple(palette[v] for v in bank[f*128*112:f*128*112+28*128]):f for f in range(32)}
check('all 32 wheel phases distinguishable from displayed PPU crop',len(phases)==32)
wheel=struct.unpack_from('<16h',rom,e.sym['wheel_sectors']-0x08000000)
values=struct.unpack_from('<12h',rom,e.sym['sector_values']-0x08000000)
trials=[];durations=[];target_counts=collections.Counter();sample_saved=False
for trial in range(64):
 reset_turn(trial&15);seed=(97531+trial*2654435761)&0xffffffff;poke_rng(seed);e.tap(8)
 check(f'audit spin {trial} starts normally',e.state()[3]==2)
 target=scene(156);target_counts[target]+=1;points=[];invariant=True;total=e.state()[74]
 reference=((trial&15)-64-((((seed*134775813+1)&0xffffffff)>>16)%32))&15
 check(f'audit spin {trial} preserves pre-optimization random outcome',target==reference)
 thresholds=[total-2,total*4//5,total*3//5,total*2//5,total//5,1]
 for frame in range(5000):
  if e.state()[3]!=2:break
  state=e.state();invariant &= ((state[7]-state[74])&15)==target
  if len(points)<6 and state[74]<=thresholds[len(points)]:
   phase=phases.get(region(e.raw,32,43,128,28));assert phase is not None,('unknown PPU wheel',trial,frame)
   if (phase&1)!=(trial&1):e.run(1);continue
   assert e.core.retro_serialize(buffer,state_size)
   points.append((frame,phase,buffer.raw,e.raw))
  e.run(1)
 else:raise AssertionError('natural spin never stops')
 e.run(16);natural=(e.state()[7],e.state()[8],e.state()[2]);durations.append(frame)
 reference_rng=seed
 for step in range(13):reference_rng=(reference_rng*134775813+1)&0xffffffff
 check(f'audit spin {trial} preserves pre-optimization RNG state',natural[2]&0xffffffff==reference_rng)
 check(f'audit spin {trial} keeps target invariant to natural stop',invariant and natural[0]==target and len(points)==6)
 for delay,phase,checkpoint,display in points:
  data=c.create_string_buffer(checkpoint,len(checkpoint));assert e.core.retro_unserialize(data,len(checkpoint))
  e.raw=display;e.keys=set();before=(12-phase//2)&15
  e.run(1,(8,));e.run(1);e.until(lambda s:s[3]!=2,limit=24);e.run(16)
  result=(e.state()[7],e.state()[8],e.state()[2]);same=before==target;same_award=wheel[before]==wheel[target]
  check(f'exact-state spin {trial} skip at frame {delay} equals natural stop',result==natural and scene(156)==target)
  trials.append(dict(trial=trial,seed=seed,delay=delay,visible_phase=phase,visible_sector=before,target=target,
                     visible_value=values[wheel[before]-4],result_value=natural[1],same_sector=same,same_award=same_award,half_phase=bool(phase&1)))
  if not sample_saved and not same and not same_award:
   preview('spin-skip-after.png');e.raw=display;preview('spin-skip-before.png');sample_saved=True
 e.audio.clear()
 if trial%16==15:print(f'Exact-state spin audit: {trial+1}/64 natural spins, {len(trials)} skip comparisons',flush=True)
check('audit includes different actual displayed and awarded sectors',sample_saved)

# Exercise the actual cartridge gift draw 1000 times without reseeding the PRNG.
# Only the initial final-win state is a fixture; no gift values are injected.
poke_rng(1);gift_counts=collections.Counter();repeat_count=0;previous=None
for draw in range(1000):
 before=e.state()[2]&0xffffffff;expected=(before*134775813+1)&0xffffffff
 for i,v in {3:9,4:2,5:2,6:0,11:0,71:0}.items():e.poke(i,v)
 e.tap(8);gift=e.state()[83]
 assert e.state()[3]==19 and (e.state()[2]&0xffffffff)==expected and gift==(expected>>16)%10,('gift draw mismatch',draw)
 gift_counts[gift]+=1;repeat_count+=gift==previous;previous=gift
 if draw%100==99:e.audio.clear()
check('1000 real gift draws each advance original RNG exactly once',sum(gift_counts.values())==1000)
check('all ten original gifts occur in actual RNG stream',set(gift_counts)==set(range(10)))
rng=e.state()[2];gift=e.state()[83]
for page in range(5):e.tap(8);e.tap(0)
check('revisiting gift page never issues a second award or rerolls',e.state()[3]==19 and e.state()[2]==rng and e.state()[83]==gift and scene(184)==0)

even=[t for t in trials if not t['half_phase']]
report=dict(status='passed',count=len(checks),checks=checks,rom_sha256=hashlib.sha256(rom).hexdigest(),
 spin_audit=dict(natural_spins=64,skip_comparisons=len(trials),mismatches=0,target_histogram=dict(target_counts),
                same_displayed_sector=sum(t['same_sector'] for t in trials),same_displayed_award=sum(t['same_award'] for t in trials),
                unambiguous_even_phases=len(even),even_phase_same_sector=sum(t['same_sector'] for t in even),
                natural_duration_frames=[min(durations),max(durations)],natural_duration_seconds=[min(durations)/e.fps,max(durations)/e.fps],trials=trials),
 gift_audit=dict(draws=1000,histogram=dict(gift_counts),consecutive_repeats=repeat_count,repeat_opportunities=999,
                 one_rng_step_per_award=True,page_navigation_rerolls=False))
(ROOT/'build/qa/stage-report.json').write_text(json.dumps(report,indent=2));e.close()
print(json.dumps({k:v for k,v in report.items() if k not in ('checks','spin_audit')})+'\n'+json.dumps({k:v for k,v in report['spin_audit'].items() if k!='trials'}))
