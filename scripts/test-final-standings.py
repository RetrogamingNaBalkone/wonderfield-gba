"""Verify final table order, winner prominence, columns and gift transition in mGBA."""
import ctypes as c
import hashlib
import importlib.util
import json
import struct
from emulator import ROOT

spec = importlib.util.spec_from_file_location('standings', ROOT / 'scripts/test-standings.py')
s = importlib.util.module_from_spec(spec)
spec.loader.exec_module(s)

# Reference full-size names from the unchanged intermediate table.
e = s.frame(0, [0]*3, [0]*3)
names = {p: s.crop(e, 50, 80 + row*22, 80, 14) for row, p in enumerate((2, 0, 1))}
e.close()
checks = []
# Expected ordering is explicit, including tie order and score-independent wins.
cases = [
    ('points', 0, [0, 0, 0], [99999, 20000, 30000], 2, False, [0, 2, 1]),
    ('risk-tied-runners', 1, [0, 0, 0], [20000, 99999, 20000], 2, False, [1, 2, 0]),
    ('wins', 2, [4, 2, 2], [5, 2, 2], 0, False, [0, 2, 1]),
    ('shootout-lower-score-winner', 0, [500, 500, 100], [99999, 500, 100], 1, True, [1, 0, 2]),
]
for name, rule, before, after, round_winner, shootout, order in cases:
    e = s.frame(rule, before, after, round_winner, shootout, rounds=5 if rule == 2 else 1)
    match = struct.unpack('<16i', s.read(e, 'match', 64))
    assert match[13:15] == (order[0], 2), (name, match)
    # Large winner heading uses the very same full-size glyphs as the table.
    size = 4 if e.format == 1 else 2
    winner_name = b''.join(names[order[0]][row*80*size:(row*80+8)*size] for row in range(14))
    assert s.crop(e, 116, 30, 8, 14) == winner_name, (name, 'winner heading')
    for row, p in enumerate(order):
        assert s.crop(e, 50, 80 + row*22, 80, 14) == names[p], (name, 'name order', row)
    if rule != 2:
        blank = s.crop(e, 140, 50, 30, 8)
        assert s.crop(e, 140, 64, 30, 8) == blank, (name, 'unexpected wins column')
    else:
        assert s.crop(e, 140, 64, 30, 8) != s.crop(e, 140, 50, 30, 8)
    e.screenshot(f'final-standings-{name}.png')
    # Both stages must share headers, column positions and place labels.
    headers = s.crop(e, 12, 64, 212, 8)
    places = [s.crop(e, 22, 80 + row*22, 8, 14) for row in range(3)]
    s.put(e, 'match', 14, 0)
    s.write(e, 'dirty', struct.pack('<i', 1));e.run(20)
    assert s.crop(e, 12, 64, 212, 8) == headers, (name, 'inconsistent headers')
    assert [s.crop(e, 22, 80 + row*22, 8, 14) for row in range(3)] == places
    s.put(e, 'match', 14, 2)
    s.write(e, 'dirty', struct.pack('<i', 1));e.run(20)
    s.tap(e, 8)
    assert e.state()[3] == 19 and e.state()[5] == order[0], (name, 'gift recipient')
    e.close()
    checks.append(dict(case=name, order=order, winner_and_gift=True))

# AI winner and maximum-length names are inspected in a real rendered frame.
e = s.frame(2, [2, 4, 2], [2, 5, 2], 1, rounds=5, humans=2)
assert struct.unpack('<16i', s.read(e, 'match', 64))[13:15] == (1, 2)
for p, name in ((0, 'АЛЕКСАНДРА'), (2, 'КОНСТАНТИН')):
    c.memmove(e.ram + e.sym['mp'] - 0x02000000 + 28 + 11*p, name.encode('cp866') + b'\0', 11)
s.write(e, 'dirty', struct.pack('<i', 1));e.run(20)
e.screenshot('final-standings-ai-long-names.png')
s.tap(e, 8)
assert e.state()[3] == 19 and e.state()[5] == 1
e.close()
checks.append(dict(case='ai-winner-long-names', winner_and_gift=True))
report = dict(rom_sha256=hashlib.sha256((ROOT / 'build/gba/pole.gba').read_bytes()).hexdigest(), checks=checks)
(ROOT / 'docs/verification/final-standings-tests.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report, indent=2))
