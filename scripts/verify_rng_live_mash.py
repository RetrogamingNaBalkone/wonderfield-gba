"""Read-only mGBA observation of normal games driven by physical button inputs.

Blank SRAM is installed before boot, then only input APIs are used. A repeats
on a fixed cadence; RIGHT advances past used letters and START saves a record
name so play can continue. No mode, player, RNG or timing fixtures are used.
Recorded wheel awards come from the immutable spin target, once per spin.
Input remains frame-granular and does not model all real human timings.
"""
from emulator import Emulator, ROOT
from collections import Counter
import argparse, ctypes as c, hashlib, json, struct

p=argparse.ArgumentParser()
p.add_argument('--build-dir',default='build/gba')
p.add_argument('--output',default='build/qa/rng-live-mash.json')
args=p.parse_args();build=ROOT/args.build_dir;rows=[]
rom=(build/'pole.gba').read_bytes()
for boot_delay,cadence in ((4,2),(4,4),(8,2),(12,4),(20,6),(5,8)):
 e=Emulator(build/'pole.gba',build/'pole.elf')
 e.core.retro_get_memory_size.argtypes=[c.c_uint];e.core.retro_get_memory_size.restype=c.c_size_t
 c.memset(e.core.retro_get_memory_data(0),255,e.core.retro_get_memory_size(0))
 e.core.retro_reset();e.run(boot_delay)
 wheel=struct.unpack_from('<16h',rom,e.sym['wheel_sectors']-0x08000000)
 values=struct.unpack_from('<12h',rom,e.sym['sector_values']-0x08000000)
 game=-1;active=False;previous_mode=e.state()[3];spins=[];button=8
 for frame in range(90000):
  state=e.state();mode=state[3]
  if mode==0:active=False
  if mode==15 and state[4]==0 and not active:
   game+=1;active=True
   if game==3:break
  if mode==2 and previous_mode!=2:
   target=struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+156,4))[0]
   spins.append(dict(game=game,round=state[4],player=state[5],
                     target=target,award=values[wheel[target]-4],rng=state[2]&0xffffffff))
  previous_mode=mode
  if frame%cadence==0:
   button=3 if mode==14 else 7 if mode==3 and state[5]==2 and state[38+state[70]] else 8
  e.run(1,(button,) if frame%cadence<cadence//2 else ())
  if frame%200==0:e.audio.clear()
 else:raise AssertionError(('normal gameplay stalled',boot_delay,cadence,e.state()[:12]))
 e.close()
 for party in range(3):
  selected=[s for s in spins if s['game']==party];awards=[s['award'] for s in selected]
  counts=Counter(awards);positions=[i for i,v in enumerate(awards) if v==202]
  rows.append(dict(boot_delay=boot_delay,cadence=cadence,party=party,
                   counts=dict(counts),spins=selected,
                   x2_distances=[b-a for a,b in zip(positions,positions[1:])]))
 print(dict(boot_delay=boot_delay,cadence=cadence,spins=len(spins)),flush=True)
summary=[]
for party in range(3):
 selected=[r for r in rows if r['party']==party]
 counts=Counter()
 for r in selected:counts.update(r['counts'])
 summary.append(dict(party=party,spins=sum(counts.values()),counts=dict(counts)))
report=dict(status='passed',rom_sha256=hashlib.sha256(rom).hexdigest(),summary=summary,samples=rows,limitation=__doc__)
(ROOT/args.output).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(summary),flush=True)
