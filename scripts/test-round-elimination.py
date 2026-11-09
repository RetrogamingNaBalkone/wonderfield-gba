"""Exercise real departure handlers across all eight multiplayer stages.

RAM fixtures select Prize offers or a wrong answer; button presses perform
cash/prize acceptance, departures, and the round transition in the ROM.
"""
import json
import runpy
from emulator import Emulator, ROOT

m = runpy.run_path(str(ROOT / 'scripts/test-multiplayer.py'))
tap, read, mp = m['tap'], m['read'], m['mp']
words = json.loads((ROOT / 'assets/words-expanded.json').read_text())


def depart(e, reason):
    if e.state()[3] == 28:
        tap(e, 8)
    if reason == 'wrong':
        e.poke(3, 5)
        e.poke(80, len(words[e.state()[6]]['word']))
        for i in range(88, 94):
            e.poke(i, 0)  # Empty bytes cannot match a full word.
        tap(e, 8)
        if e.state()[3] == 6:
            tap(e, 8)
    else:
        e.poke(3, 7)
        e.poke(81, int(reason == 'prize'))
        e.poke(82, 4 if reason == 'prize' else 1)
        e.poke(83, 100)
        tap(e, 8)
        if reason == 'cash':
            assert e.state()[3] == 21
            for _ in range(3):
                if e.state()[3] == 21:
                    tap(e, 8)
        else:
            assert e.state()[3] == 10
            tap(e, 8)
            assert e.state()[3] == 19
            for _ in range(4):
                tap(e, 8)


for reasons in (('cash',) * 3, ('prize',) * 3, ('wrong',) * 3,
                ('prize', 'wrong', 'cash')):
    e = Emulator()
    m['menu'](e, 2)
    for _ in range(3):
        m['accept_name'](e)
    for i, score in enumerate((100, 200, 300)):
        e.poke(9 + i, score)
    records = read(e, 'record_names', 88) + read(e, 'record_scores', 32)
    names = read(e, 'mp', 61)[28:61]
    avatars = read(e, 'avatars', 12)
    selected = []
    for stage in range(8):
        assert e.state()[3] == 15
        assert e.state()[4] == stage
        selected.append(e.state()[6])
        e.run(620)
        for turn, reason in enumerate(reasons):
            actor = (2, 0, 1)[turn]
            assert e.state()[5] == actor
            depart(e, reason)
            if turn < 2:
                assert e.state()[4] == stage
                assert mp(e)[6] & (1 << actor)
            elif stage < 7:
                assert e.state()[3] == 15
                assert e.state()[4] == stage + 1
                assert mp(e)[6] == 0
                assert e.state()[5] == 2
                assert not any(e.state()[18:70])  # Board and used letters reset.
            else:
                assert e.state()[3] == 10
                assert e.state()[4] == 7  # No ninth stage or word-array overrun.
            assert e.state()[9:12] == (100, 200, 300)
            assert read(e, 'mp', 61)[28:61] == names
            assert read(e, 'avatars', 12) == avatars
    assert len(set(selected)) == 8
    assert read(e, 'record_names', 88) + read(e, 'record_scores', 32) == records
    tap(e, 8)
    assert e.state()[3] == 0
    e.close()
    print('PASS: eight stages, departure reasons', reasons, flush=True)
