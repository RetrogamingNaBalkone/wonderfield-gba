"""Rendering, clock and bit-exact speaker regressions for the optimized ROM.

If build/performance-baseline contains the previous ROM/ELF, compare settled
PPU frames against that actual cartridge as well as checking idle draw counts.
"""
import contextlib,ctypes as c,hashlib,io,json,struct,zlib
from emulator import Emulator,ROOT
from audit_idle import profile
from measure_pacing import measure as measure_pacing

checks=[]
def check(name,ok):
 assert ok,name
 checks.append(name)

with contextlib.redirect_stdout(io.StringIO()):current=profile()
for row in current['results']:
 check(row['name']+' has no redundant full redraws',row['rendered_frames']==0)
 check(row['name']+' keeps exactly one PPU image',row['unique_ppu_frames']==1)
 check(row['name']+' polls the main loop every VBlank',row['main_updates']>=299)
 check(row['name']+' takes the empty-audio fast path',row['fast_silent_buffers']>=row['audio_irqs']-1)

baseline=None;directory=ROOT/'build/performance-baseline'
if (directory/'pole.gba').exists() and (directory/'pole.elf').exists():
 with contextlib.redirect_stdout(io.StringIO()):
  baseline=profile(directory/'pole.gba',directory/'pole.elf',directory/'idle-profile-normalized.json')
 for old,new in zip(baseline['results'],current['results']):
  if new['name']=='title-settled':
   check('baseline and current title fixtures agree',old['name']==new['name'])
  else:check(new['name']+' has identical pixels to previous ROM',old['name']==new['name'] and old['ppu_crc32']==new['ppu_crc32'])
 # Compare actual PPU pixels: only the smaller version caption and blue ink
 # in the two large logo bounds may differ. Background/grid pixels must match
 # wherever neither version draws blue ink, even inside those bounds.
 def title_pixels(rom_path,elf_path):
  em=Emulator(rom_path,elf_path)
  try:
   em.run(300);pixels=[]
   for v, in struct.iter_unpack('<I' if em.format==1 else '<H',em.raw):
    if em.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
    elif em.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
    else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
    pixels.append(r|(g<<5)|(b<<10))
   data=c.string_at(em.info.data,em.info.size)
   blue=struct.unpack_from('<H',data,em.sym['palette']-0x08000000+2)[0]
   return pixels,blue
  finally:em.close()
 old_pixels,old_blue=title_pixels(directory/'pole.gba',directory/'pole.elf')
 new_pixels,new_blue=title_pixels(ROOT/'build/gba/pole.gba',ROOT/'build/gba/pole.elf')
 def allowed_title_change(p,a,b):
  x,y=p%240,p//240
  if 206<=x<234 and 120<=y<134:return True
  in_logo=(9<=x<102 and 23<=y<111) or (104<=x<213 and 23<=y<131)
  return in_logo and (a==old_blue or b==new_blue)
 check('title changes only approved blue logo strokes and version caption',
       all(a==b or allowed_title_change(p,a,b) for p,(a,b) in enumerate(zip(old_pixels,new_pixels))))

reference=json.loads((ROOT/'analysis/pacing-reference.json').read_text())
pacing=measure_pacing();previous=reference['timings']
for old,new in zip(previous['spins'],pacing['spins']):
 check(f'spin seed {new["seed"]} retains pre-optimization duration',old['seed']==new['seed'] and abs(old['vblanks']-new['vblanks'])<=2)
for old,new in zip(previous['reveals'],pacing['reveals']):
 check(f'reveal sector {new["sector"]} retains pre-optimization walking speed',old['sector']==new['sector'] and abs(old['vblanks']-new['vblanks'])<=4)
check('host keeps every pre-optimization face phase',[p[1] for p in previous['host_phases']]==[p[1] for p in pacing['host_phases']])
check('host face cadence remains within four VBlanks of previous ROM',all(abs(a[0]-b[0])<=4 for a,b in zip(previous['host_phases'],pacing['host_phases'])))
for old,new in zip(previous['ai'],pacing['ai']):
 check('AI '+new['event']+' retains pre-optimization delay',old['event']==new['event'] and abs(old['vblanks']-new['vblanks'])<=2)

e=Emulator();e.run(220)
rom=(ROOT/'build/gba/pole.gba').read_bytes()
def read(name,offset=0):return struct.unpack('<I',c.string_at(e.ram+e.sym[name]-0x02000000+offset,4))[0]
def write(name,value,offset=0):c.memmove(e.ram+e.sym[name]-0x02000000+offset,struct.pack('<I',value&0xffffffff),4)
def block(name,n):return c.string_at(e.ram+e.sym[name]-0x02000000,n)
def asset(name,n):
 p=e.sym[name]-0x08000000;return rom[p:p+n]
def fixture(mode):
 for i in range(20):e.poke(18+i,0)
 for i in range(32):e.poke(38+i,0)
 for i,value in {3:mode,4:0,5:2,6:0,7:12,9:0,10:0,11:0,12:0,13:1,70:0,71:0,72:0,76:0,79:0,80:0,81:1,82:0}.items():e.poke(i,value)
 write('message1',0);write('scene',0,168);write('dirty',1);e.run(16)
def pixel_indices():
 palette=struct.unpack('<16H',asset('palette',32));out=[]
 for v, in struct.iter_unpack('<I' if e.format==1 else '<H',e.raw):
  if e.format==1:r,g,b=(v>>19)&31,(v>>11)&31,(v>>3)&31
  elif e.format==2:r,g,b=(v>>11)&31,(v>>6)&31,v&31
  else:r,g,b=(v>>10)&31,(v>>5)&31,v&31
  out.append(palette.index(r|(g<<5)|(b<<10)))
 return out
def actor_matches(id,x,y,half=True):
 meta=json.loads((ROOT/'assets/sprites.json').read_text())[id]
 w=round(meta['width']*35/(96 if half else 48));h=round(meta['height']/2) if half else meta['height']
 data=asset(('small_data_' if half else 'sprite_data_')+str(id),w*h);pixels=pixel_indices()
 return all(pixels[(y+yy)*240+x+xx]==v for yy in range(h) for xx in range(w) if (v:=data[yy*w+xx])!=(2 if half else 7))

# A held direction must use elapsed video time even with a static main loop.
fixture(13);start=read('video_ticks');e.run(16,(7,))
check('held Right selects once before the repeat deadline',e.state()[84]==1)
e.run(8,(7,));check('held Right repeats after eighteen VBlanks',e.state()[84]>=2)
e.run(1);at_release=e.state()[84];e.run(60)
check('release cancels directional repeat',e.state()[84]==at_release)
fixture(1);write('scene',0,4);e.run(140);draws=read('rendered_frames');e.run(180,(7,));e.run(1)
check('holding the already selected menu option does not redraw',e.state()[81]==1 and read('rendered_frames')==draws)

# Turn speech disappears on its deadline, even when nothing else changes.
fixture(1);write('message1',e.sym['msg_e77']);write('message2',e.sym['msg_e65']);write('scene',read('video_ticks'),4);write('dirty',1)
e.run(60);spoken=zlib.crc32(e.raw);e.run(110)
settled=next(row for row in current['results'] if row['name']=='human-turn-settled')
check('turn speech disappears and restores the original board/theme',spoken!=zlib.crc32(e.raw) and [zlib.crc32(e.raw)]==settled['ppu_crc32'])

# Original introduction frames 53/54/55 and the final contestant still appear.
fixture(15);write('scene',1,32);write('scene',read('video_ticks'),16);write('dirty',1)
e.run(12);check('introduction displays appearance frame 53',actor_matches(53,3,83))
e.run(18);check('introduction displays appearance frame 54',actor_matches(54,3,83))
e.run(18);check('introduction displays appearance frame 55',actor_matches(55,3,83))
e.run(18);check('introduction restores the actual contestant after appearance',actor_matches(asset('opponent_sprites',6)[0],3,83))

# A chest must stop animating at 90 VBlank, then stay genuinely static.
fixture(8);write('scene',read('video_ticks'),4);frames=set()
for _ in range(30):e.run(2);frames.add(zlib.crc32(e.raw))
check('chest still animates before ninety VBlanks',len(frames)>=2)
e.run(110);check('chests settle into the original closed sprites',actor_matches(36,18,96,False) and actor_matches(36,115,96,False))
draws=read('rendered_frames');e.run(180);check('settled chests do not redraw',read('rendered_frames')==draws)
fixture(6);e.poke(81,0);write('scene',read('video_ticks')+60,28);write('dirty',1)
e.run(20);reward=zlib.crc32(e.raw);e.run(90)
check('reward chest disappears at its deadline',zlib.crc32(e.raw)!=reward)
draws=read('rendered_frames');e.run(180);check('expired reward remains static',read('rendered_frames')==draws)

# Preserve the measured old AI chest wait: 41 render-bound updates * 8 VBlank.
fixture(6);e.poke(5,0);e.poke(77,8);e.poke(78,0);e.tap(8);e.until(lambda s:s[3]==8)
entered=read('scene',4);e.run(250)
check('AI chest waits instead of accelerating with the main loop',e.state()[3]==8)
e.until(lambda s:s[3]!=8);elapsed=read('video_ticks')-entered
check('AI chest decision retains approximately 5.5 seconds',328<=elapsed<=340)

# Pause retains visual deadlines, not just game.mode.
fixture(8);write('scene',read('video_ticks'),4);e.run(25);e.tap(3);check('START pauses animated chest',e.state()[3]==11)
clock=read('scene',4);e.run(180);e.tap(3)
check('resuming shifts chest animation clock by the pause duration',e.state()[3]==8 and read('scene',4)>=clock+180)

# Model the old sample loop independently, then compare all FIFO bytes and
# oscillator/queue fields after actual GBA audio IRQs, including empty tails.
fixture(11);e.run(30)
def audio_boundary():
 # retro_run can stop between filling a FIFO block and incrementing its
 # IRQ counter. Compare at completed IRQ boundaries (startup fills 64
 # samples before IRQ accounting starts), not halfway through a block.
 for _ in range(60):
  if (read('speaker_diag',4)-read('speaker_diag')*16)&0xffffffff==64:return
  e.run(1)
 raise AssertionError('No completed audio IRQ boundary')
def increment_for(hz):
 if hz<=18:return hz,0
 pit=1193181//hz;hz=1193181//pit
 return hz,((hz*1024+(1193181-hz*pit)*1024//pit)*128)&0xffffffff
audio_cases=[
 ('empty',[],0,0,1),('short tail',[],0,3,1),('exact buffer tail',[],0,16,1),
 ('tail into next buffer',[],0,17,1),('zero-length note',[(440,0)],0,0,1),
 ('tone',[(440,25)],0,0,1),('low-frequency pause',[(18,4),(100,7)],0,0,1),
 ('queued tones',[(440,3),(880,1),(0,2),(110,6)],0,0,1),
 ('muted queue',[(440,3),(880,1),(0,2),(110,6)],0,0,0),
 ('muted active note',[(500,20)],1,700,0),
]
for name,notes,index,remaining,enabled in audio_cases:
 audio_boundary()
 data=b''.join(struct.pack('<HH',hz,ms) for hz,ms in notes)
 if data:c.memmove(e.ram+e.sym['notes']-0x02000000,data,len(data))
 fields=dict(count=len(notes),index=index,remaining=remaining,phase=0x12345678,increment=1234567,enabled=enabled,buffer=0)
 for field,value in fields.items():write(field,value)
 c.memmove(e.ram+e.sym['fifo']-0x02000000,bytes(32),32)
 write('speaker_diag',317,12)
 before_irq=read('speaker_diag');before_samples=read('speaker_diag',4);before_transitions=read('speaker_diag',8)
 model=fields.copy();expected=bytearray(32);hz=317;transitions=0
 e.run(2);audio_boundary();interrupts=read('speaker_diag')-before_irq
 for _ in range(interrupts):
  base=model['buffer']*16
  for i in range(16):
   if not model['remaining']:
    if model['index']<model['count']:
     hz,ms=notes[model['index']];model['index']+=1
     model['remaining']=max(1,(ms*32768+500)//1000)
     hz,model['increment']=increment_for(hz);transitions+=1
    else:model['increment']=0
   if model['remaining']:model['remaining']-=1
   model['phase']=(model['phase']+model['increment'])&0xffffffff
   expected[base+i]=(64 if model['phase']&0x80000000 else 192) if enabled and model['increment'] else 0
  model['buffer']^=1
 check(name+' preserves every FIFO byte',block('fifo',32)==bytes(expected))
 check(name+' preserves queue and oscillator state',all(read(k)==model[k] for k in fields))
 actual=(read('speaker_diag',4)-before_samples,read('speaker_diag',8)-before_transitions,read('speaker_diag',12))
 expected_diag=(interrupts*16,transitions,hz)
 if actual!=expected_diag:print(name,'diagnostics',actual,'expected',expected_diag,flush=True)
 check(name+' preserves sample/transition diagnostics',actual==expected_diag)
write('enabled',1);e.close()

report=dict(status='passed',count=len(checks),checks=checks,rom_sha256=hashlib.sha256(rom).hexdigest(),
 ai_chest_vblanks=elapsed,audio_cases=len(audio_cases),idle_profile=current,baseline_profile=baseline,
 pacing_reference=reference,pacing_actual=pacing)
(ROOT/'build/qa/performance-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps({k:v for k,v in report.items() if k not in ('checks','idle_profile','baseline_profile','pacing_reference','pacing_actual')}))
