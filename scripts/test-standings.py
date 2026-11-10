"""Check sorted intermediate standings and movement indicators in actual mGBA frames."""
import ctypes as c
import hashlib
import json
import runpy
import struct
from emulator import Emulator, ROOT

m = runpy.run_path(str(ROOT / 'scripts/test-multiplayer.py'))
read, write, tap = m['read'], m['write'], m['tap']


def put(e, name, index, value):
    data = bytearray(read(e, name, 64 if name == 'match' else 24))
    struct.pack_into('<i', data, index * 4, value)
    write(e, name, data)


def crop(e, x, y, width, height):
    size = 4 if e.format == 1 else 2
    return b''.join(e.raw[((y + row) * 240 + x) * size:
                          ((y + row) * 240 + x + width) * size]
                    for row in range(height))


def frame(rule, before, after, winner=-1, shootout=False):
    e = Emulator()
    m['options'](e, 3)
    put(e, 'prefs', 4, rule)
    put(e, 'prefs', 5, 5 if rule == 2 else 3)
    tap(e, 8)
    for _ in range(3):
        m['accept_name'](e)
    for p in range(3):
        put(e, 'match', 3 + p, before[p] if rule != 2 else 0)
        put(e, 'match', 6 + p, before[p] if rule == 2 else 0)
        e.poke(9 + p, after[p] if rule != 2 else (3 - p) * 10000)
    put(e, 'match', 9, int(shootout))
    e.poke(5, winner if winner >= 0 else 2)
    e.poke(79, int(winner >= 0))
    e.poke(3, 9)
    tap(e, 8)  # Real settlement and transition into MP_SUMMARY.
    assert e.state()[3] == 36
    if rule == 2:
        assert list(struct.unpack('<3i', read(e, 'match', 36)[24:36])) == after
    return e


# Capture each player's real name at the known all-zero, player-number order.
e = frame(0, [0, 0, 0], [0, 0, 0])
reference = {p: crop(e, 16, 48 + place * 28, 80, 14)
             for place, p in enumerate((2, 0, 1))}
background = crop(e, 210, 140, 1, 1)
e.close()
checks = []
cases = [
    ('points-rise', 0, [200, 100, 300], [500, 100, 300], 0, False),
    ('risk-bankrupt', 1, [200, 100, 300], [200, 100, 0], 0, False),
    ('points-tie', 0, [200, 100, 300], [300, 300, 300], 1, False),
    ('unchanged', 0, [200, 100, 300], [250, 150, 350], 2, False),
    ('wins-rise', 2, [1, 0, 1], [2, 0, 1], 0, False),
    ('wins-tie', 2, [1, 0, 0], [1, 0, 1], 2, False),
    ('wins-no-winner', 2, [1, 0, 1], [1, 0, 1], -1, False),
    ('repeat-shootout', 0, [500, 100, 500], [500, 100, 500], -1, True),
    ('five-digits', 1, [10000, 20000, 30000], [99999, 20000, 30000], 0, False),
]
for name, rule, before, after, winner, shootout in cases:
    e = frame(rule, before, after, winner, shootout)
    old = sorted((2, 0, 1), key=lambda p: -before[p])
    order = sorted((2, 0, 1), key=lambda p: -after[p])
    for place, p in enumerate(order):
        y = 48 + place * 28
        assert crop(e, 16, y, 80, 14) == reference[p], (name, 'name order', p)
        direction = (old.index(p) > place) - (old.index(p) < place)
        for row in range(5):
            half = row if direction > 0 else 4 - row
            for x in range(216, 225):
                filled = direction != 0 and abs(x - 220) <= half
                assert (crop(e, x, y + 3 + row, 1, 1) != background) == filled, (name, 'triangle', p)
    state = read(e, 'match', 64)
    e.run(120)
    assert read(e, 'match', 64) == state, (name, 'redraw changed standings')
    e.screenshot(f'standings-{name}.png')
    tap(e, 8)
    assert e.state()[3] == (15 if shootout else 17), (name, 'continuation')
    e.close()
    checks.append(dict(case=name, order=order, triangles=True))

report = dict(rom_sha256=hashlib.sha256((ROOT / 'build/gba/pole.gba').read_bytes()).hexdigest(), checks=checks)
(ROOT / 'docs/verification/standings-tests.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps(report, indent=2))
