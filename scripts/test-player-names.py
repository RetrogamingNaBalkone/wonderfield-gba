"""Name-entry regressions against the built ROM (mGBA libretro)."""
import struct
from emulator import Emulator
from importlib.machinery import SourceFileLoader
from pathlib import Path
m = SourceFileLoader('multiplayer_tests', str(Path(__file__).with_name('test-multiplayer.py'))).load_module()

def enter(e, name):
    if struct.unpack('<i', m.read(e, 'mp_name_error', 4))[0]:
        before = m.read(e, 'game', 400)
        m.tap(e, 8 if name == ' АННА ' else 0)
        after = m.read(e, 'game', 400)
        assert before[80*4:81*4] == after[80*4:81*4]
        assert before[70*4:71*4] == after[70*4:71*4]
        assert before[88*4:88*4+21] == after[88*4:88*4+21]
    raw = name.encode('cp866')
    assert len(raw) <= 10
    # Populate the input buffer, then exercise the real START handler.
    data = bytearray(m.read(e, 'game', 400))
    struct.pack_into('<i', data, 80 * 4, len(raw))
    data[88 * 4:88 * 4 + 21] = raw.ljust(21, b'\0')
    m.write(e, 'game', bytes(data))
    m.tap(e, 3)

def names(e):
    raw = m.read(e, 'mp', 61)[28:]
    return [raw[p*11:p*11+11].split(b'\0')[0].decode('cp866') for p in range(3)]

for humans in (2, 3):
    e = Emulator(); m.menu(e, humans - 1)
    enter(e, '  АННА  ')
    assert e.state()[3] == 33 and names(e)[2] == 'АННА'
    m.tap(e, 8)
    for duplicate in ('АННА', ' АННА '):
        enter(e, duplicate)
        assert e.state()[3] == 27 and names(e)[0] == '2-ой ИГРОК'
    e.screenshot(f'name-conflict-{humans}.png')
    enter(e, 'БАГИРА')
    assert e.state()[3] == (27 if humans == 2 else 33)
    if humans == 2:
        enter(e, '   ')
        assert names(e)[0] == '2-ой ИГРОК'
    m.tap(e, 8)
    if humans == 3:
        enter(e, 'АННА'); assert e.state()[3] == 27
        enter(e, 'А  Б'); assert names(e)[1] == 'А Б'
        m.tap(e, 0); assert e.state()[3] == 27  # back from avatar
        enter(e, 'А Б'); assert e.state()[3] == 33  # own name allowed
        m.tap(e, 8)
    assert struct.unpack('<3i', m.read(e, 'avatars', 12)) == (0, 0, 0)
    e.run(1400); assert e.state()[3] == 1
    e.close()
print('PASS: name/space collisions, AI reservation, blank fallback, own-name edit, shared avatars, game start')
