"""Compare a clean release and a three-frame contact break in cartridge code."""
import json
import runpy
import struct
from emulator import Emulator, ROOT

helpers = runpy.run_path(str(ROOT / 'scripts/test-multiplayer.py'))
read, write = helpers['read'], helpers['write']
word = bytes.fromhex(json.loads((ROOT/'assets/words.json').read_text(encoding='utf-8'))[0]['word_hex'])
e = Emulator()

def setup(mode):
    e.core.retro_reset()
    e.run(90)
    for index, value in {3: mode, 5: 2, 6: 0, 8: 10, 81: 1}.items():
        e.poke(index, value)
    write(e, 'dirty', struct.pack('<I', 1))
    e.run(6)

def field(name, offset):
    return struct.unpack_from('<I', read(e, name, offset + 4), offset)[0]

def mode():
    return e.state()[3]

def compare(button, observe, expected):
    start = e.checkpoint()
    for bounce in (False, True):
        e.restore(start)
        e.run(6, (button,))
        e.run(3)
        e.run(6, (button,) if bounce else ())
        e.run(8)
        result = observe()
        assert result == expected, (button, bounce, result, expected)

try:
    for screen in (5, 14, 27):
        setup(screen)
        compare(8, lambda: e.state()[80], 1)
    setup(5)
    e.poke(80, len(word)-1)
    compare(8, lambda: (mode(), e.state()[80]), (5, len(word)))
    setup(14)
    e.poke(80, 3)
    compare(0, lambda: e.state()[80], 2)
    for screen, expected in ((8, 6), (4, 16), (3, 16), (28, 1), (24, 24)):
        setup(screen)
        if screen == 3:
            e.poke(70, word[0]-128)
        compare(8, mode, expected)
    setup(19)
    compare(8, lambda: field('scene', 184), 1)
    setup(1)
    compare(3, mode, 23)
    setup(1)
    compare(10, lambda: field('sound_on', 0), 0)
    setup(26)
    compare(5, lambda: helpers['mp'](e)[5], 1)
    # Same screen number, but an event from an earlier visit to the menu.
    setup(26)
    context = field('presentation_event', 0)
    write(e, 'input_events', struct.pack('<H', 128 | 1))
    write(e, 'input_context', struct.pack('<I', (context - 1) & 0xffffffff))
    write(e, 'input_read', bytes([0]))
    write(e, 'input_write', bytes([1]))
    e.run(10)
    assert mode() == 26 and helpers['mp'](e)[5] == 0
    # If the queue lost the A release, the sampled up state ends the title wait.
    setup(0)
    e.run(8, (8,))
    assert mode() == 0
    write(e, 'fast_input', bytes([0]))  # Suppress delivery of A_RELEASE.
    e.run(10)
    assert mode() == 26
    # No input. Start just past counter rollover with the deadline still ahead.
    setup(1)
    write(e, 'video_ticks', struct.pack('<I', 0xfffffffe))
    e.poke(3, 2)
    e.poke(74, 24)
    e.poke(75, 1)
    scene = bytearray(read(e, 'scene', 188))
    struct.pack_into('<I', scene, 20, 1)
    write(e, 'scene', scene)
    e.run(2)
    assert mode() == 2 and e.state()[74] == 24
    e.run(20)
    assert mode() == 2 and e.state()[74] < 24
finally:
    e.close()
print('PASS: contact breaks, action transitions and wheel deadline across rollover')
