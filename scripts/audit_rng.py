"""Audit RNG math, original DOS spin instructions and actual mGBA draws.

This does not modify the cartridge or original executable. Emulator fixtures
set seeds and modes explicitly; the cartridge performs every audited draw.
"""
from emulator import Emulator, ROOT
from rng_reference import dos_spin
from collections import Counter
from itertools import product
import ctypes as c
import hashlib
import json
import struct

MASK = 0xffffffff
def step(seed): return (seed * 134775813 + 1) & MASK
def advance(seed, count):
 for _ in range(count): seed = step(seed)
 return seed

# Independently evaluate the 16-bit instructions at 1ad9:119f.
exe = (ROOT/'originals/Wonderfield/POLE.EXE').read_bytes()
header = struct.unpack_from('<H', exe, 8)[0]*16
multiplier = struct.unpack_from('<H', exe, header+0xad90+0x11d5)[0]
assert multiplier == 0x8405
def dos_step(seed):
 ax, bx = seed & 0xffff, seed >> 16
 cx = (ax << 3) & 0xffff
 cx = (cx + ((cx & 255) << 8)) & 0xffff
 value = ax * multiplier
 dx = ((value >> 16) + cx + bx) & 0xffff
 bx = (bx << 2) & 0xffff
 dx = (dx + bx + ((bx & 255) << 8)) & 0xffff
 bx = (bx << 5) & 0xffff
 dx = (dx + ((bx & 255) << 8) + ((value & 0xffff) == 0xffff)) & 0xffff
 return (dx << 16) | ((value+1) & 0xffff)
assert all(dos_step(seed) == step(seed) for seed in range(0, 1 << 32, 65537))

# Exact distribution over all possible 16-bit outputs, not a random sample.
word_counts = Counter(x % 495 for x in range(65536))
words = json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))
duplicates = {w: ids for w in {x['word'] for x in words}
              if len(ids := [x['id'] for x in words if x['word'] == w]) > 1}

# DOS 1000:2c6a..2fa2: 32 half-sector phases, four speed stages.
# First limit Random(20)+10; subsequent limits Random(10)+5.
# A stage processes counters 0..limit inclusive and moves when counter %
# divisor == 0. At rest an odd phase is rounded upwards to an even phase.
def dos_phase_increment(limits):
 phase = 0
 for limit, divisor in zip(limits, (1, 2, 3, 4)):
  for counter in range(limit+1):
   if counter % divisor == 0: phase = (phase+1) & 31
 if phase & 1: phase = (phase+1) & 31
 return phase // 2
ideal_dos = Counter(dos_phase_increment(v) & 15 for v in
                    product(range(10,30), range(5,15), range(5,15), range(5,15)))
# Correlated draws of the actual LCG, at evenly spaced 32-bit entry states.
dos_counts = Counter()
for trial in range(100000):
 seed = advance(trial*42949 & MASK,6)  # DOS 0936 -> 08e4 noise before Random(20).
 limits = []
 for bound, offset in ((20,10),(10,5),(10,5),(10,5)):
  seed = step(seed); limits.append((seed >> 16) % bound + offset)
 dos_counts[dos_phase_increment(limits) & 15] += 1

e = Emulator(); e.run(220)
actual_words, actual_sectors = Counter(), Counter()
for trial in range(512):
 seed = trial*2654435761 & MASK
 # Explicit effective-seed fixture, after mixing the real input timestamp.
 e.poke(3,0); e.poke(2, seed if seed < 0x80000000 else seed-0x100000000)
 expected = (advance(seed,41) >> 16) % 495
 e.tap_seeded(8,seed)
 assert e.state()[6] == expected, (trial, e.state()[6], expected)
 actual_words[expected] += 1
 # Force a human turn, then start the original cartridge spin using A.
 for index, value in ((3,1),(5,2),(7,trial & 15),(81,1),(2,12345+trial)):
  e.poke(index,value)
 expected, expected_seed = dos_spin(12345+trial, trial & 15)
 e.tap_seeded(8,12345+trial)
 target = struct.unpack('<I',c.string_at(e.ram+e.sym['scene']-0x02000000+156,4))[0]
 assert e.state()[3] == 2 and target == expected
 assert e.state()[2] & MASK == expected_seed
 actual_sectors[target] += 1
# Force rejection of both prior record IDs in the third round. The ROM
# must draw again, rather than checking a theme or accepting a duplicate.
for trial in range(64):
 seed=trial*2654435761 & MASK
 prior=[(step(seed)>>16)%495,(advance(seed,2)>>16)%495]
 c.memmove(e.ram+e.sym['selected_words']-0x02000000,struct.pack('<3i',*prior,-1),12)
 e.poke(3,17);e.poke(4,1)
 ticks=struct.unpack('<I',c.string_at(e.ram+e.sym['video_ticks']-0x02000000,4))[0]
 c.memmove(e.ram+e.sym['scene']-0x02000000+12,struct.pack('<I',(ticks-40)&MASK),4)
 expected_seed=seed
 while True:
  expected_seed=step(expected_seed);expected=(expected_seed>>16)%495
  if expected not in prior:break
 e.tap_seeded(8,seed)
 assert e.state()[4]==2 and e.state()[6]==expected
replays = []
for seed in (1,12345,999999):
 outcomes = []
 for skip in (False,True):
  for index,value in ((3,1),(5,2),(7,12),(81,1),(2,seed)):
   e.poke(index,value)
  e.tap_seeded(8,seed)
  if skip: e.tap(8)
  else: e.until(lambda s:s[3] != 2)
  outcomes.append(tuple(e.state()[i] for i in (7,8,2)))
 assert outcomes[0] == outcomes[1], (seed,outcomes)
 replays.append(dict(seed=seed,sector=outcomes[0][0],value=outcomes[0][1],skip_matches=True))
e.close()
boots = []
for delay in (220,220,221):
 e = Emulator(); e.run(delay); e.tap(8)
 boots.append(dict(vblanks_before_A=delay,word_id=e.state()[6],rng=e.state()[2] & MASK))
 e.close()
assert boots[0] == boots[1]

report = dict(
 status='passed',rom_sha256=hashlib.sha256((ROOT/'build/gba/pole.gba').read_bytes()).hexdigest(),
 original_sha256=hashlib.sha256(exe).hexdigest(),
 dos_rng_instruction_comparisons=65536,
 word_output_space=dict(records=495, high_word_values=65536,
  quotient=65536//495, remainder=65536%495,
  favored_record_ids=[0,65536%495-1], min_count=min(word_counts.values()),
  max_count=max(word_counts.values()), duplicate_spellings=duplicates),
 gba_sector_output_space=dict(model="DOS four-stage spin; see dos_spin displacement counts"),
 dos_spin=dict(model='1000:2c6a..2fa2, initial even phase; counts are relative sector displacements',
  ideal_independent_duration_combinations=20000,
  ideal_counts=[ideal_dos[i] for i in range(16)],
  lcg_entry_states=100000, lcg_counts=[dos_counts[i] for i in range(16)]),
 cartridge_checks=dict(first_word_draws=512, spin_targets=512, duplicate_rejection_draws=64,
  distinct_first_records=len(actual_words), sector_counts=[actual_sectors[i] for i in range(16)],
  natural_vs_skip=replays, cold_boots=boots))
out = ROOT/'build/qa/rng-audit.json'; out.parent.mkdir(exist_ok=True)
out.write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,ensure_ascii=False,indent=2))
