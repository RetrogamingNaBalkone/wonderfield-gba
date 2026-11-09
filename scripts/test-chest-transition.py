"""Fast chest dismissal must not draw old chests over a subsequent zero sector."""
import runpy
import struct
from emulator import Emulator, ROOT
m = runpy.run_path(str(ROOT / 'scripts/test-multiplayer.py'))
tap, read, write = m['tap'], m['read'], m['write']

def chest_deadline(e, value=None):
    scene = bytearray(read(e, 'scene', 180))
    if value is None:
        return struct.unpack_from('<I', scene, 28)[0]
    struct.pack_into('<I', scene, 28, value)
    write(e, 'scene', bytes(scene))

def regions(e, humans):
    pixels = read(e, 'framebuffer', 240*160)
    y = 90 if humans > 1 else 96
    return b''.join(pixels[row*240+x:row*240+x+36]
                    for x in (18, 115) for row in range(y, y+38))

def redraw(e):
    write(e, 'dirty', struct.pack('<i', 1)); e.run(5)

for humans in (1, 2, 3):
    e = Emulator(); m['menu'](e, humans - 1)
    if humans > 1:
        for _ in range(humans): m['accept_name'](e)
    e.run(1400)
    # Select the rare bonus state; actual input opens a chest and dismisses it.
    e.poke(3, 8); e.poke(5, 2); e.poke(81, 0)
    tap(e, 8); assert e.state()[3] == 6
    assert struct.unpack('<i', read(e, 'result_reason', 4))[0] == 5
    deadline = chest_deadline(e)
    shown = regions(e, humans)
    chest_deadline(e, 0); redraw(e)
    assert shown != regions(e, humans), 'Chest result must still show the chests'
    chest_deadline(e, deadline); redraw(e)
    tap(e, 8); assert e.state()[3] == 1
    # A real zero-sector resolution immediately after the bonus.
    rom = (ROOT / 'build/gba/pole.gba').read_bytes()
    sectors = struct.unpack_from('<16h', rom, e.sym['wheel_sectors']-0x08000000)
    values = struct.unpack_from('<12h', rom, e.sym['sector_values']-0x08000000)
    zero = next(i for i, v in enumerate(sectors) if values[v-4] == 0)
    scene = bytearray(read(e, 'scene', 180))
    struct.pack_into('<i', scene, 156, zero)
    write(e, 'scene', bytes(scene))
    e.poke(3, 2); tap(e, 8)
    assert e.state()[3] == 6
    assert struct.unpack('<i', read(e, 'result_reason', 4))[0] == 2
    assert struct.unpack_from('<I', read(e, 'scene', 4))[0] < deadline
    before = regions(e, humans)
    e.screenshot(f'chest-next-zero-{humans}.png')
    chest_deadline(e, 0); redraw(e)
    assert before == regions(e, humans), humans
    tap(e, 8)
    assert e.state()[5] == 0
    assert e.state()[3] == (28 if humans > 1 else 1)
    e.close()
print('PASS: quick chest dismissal, zero sector, clean rendering and next-player handoff in all modes')
