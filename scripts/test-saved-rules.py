"""Exercise the rules menus with SRAM carried across emulator sessions."""
import ctypes as c
import runpy
import struct

from emulator import Emulator, ROOT

menu = runpy.run_path(str(ROOT / 'scripts/test-multiplayer.py'))
options, select_option, tap = (menu[name] for name in ('options', 'select_option', 'tap'))

RULES_OFFSET = 0x90
SAVE_END = RULES_OFFSET + 4


def sram(e):
    return e.core.retro_get_memory_data(0)


def rules(e):
    dictionary, plus, characters, _, rule, rounds = struct.unpack(
        '<6i', menu['read'](e, 'prefs', 24)
    )
    return dictionary, plus, characters, rule, rounds


def change(e, option, button=8):
    select_option(e, option)
    tap(e, button)


def resume(save):
    e = Emulator()
    c.memmove(sram(e), bytes(save), len(save))
    return e


e = resume(b'\xff' * SAVE_END)
options(e)
legacy_save = c.string_at(sram(e), RULES_OFFSET)
assert rules(e) == (0, 0, 0, 0, 3)
change(e, 0)
change(e, 2)
change(e, 3)  # Start the single-player game.
assert e.state()[3] == 15
assert c.string_at(sram(e), RULES_OFFSET) == legacy_save
single_save = c.string_at(sram(e), SAVE_END)
e.close()

e = resume(single_save)
options(e, humans=3)
legacy_save = c.string_at(sram(e), RULES_OFFSET)
assert rules(e) == (1, 1, 1, 0, 3)
change(e, 0)
change(e, 3, 6)  # Left selects wins.
change(e, 4)
change(e, 4)
change(e, 5)  # Confirm and proceed to player entry.
assert e.state()[3] == 27
assert c.string_at(sram(e), RULES_OFFSET) == legacy_save
both_saved = c.string_at(sram(e), SAVE_END)
e.close()

e = resume(both_saved)
options(e)
assert rules(e) == (1, 0, 1, 0, 3)
change(e, 0)
tap(e, 0)  # Back abandons edits.
assert e.state()[3] == 26
tap(e, 8)
assert rules(e) == (1, 0, 1, 0, 3)
e.close()

e = resume(both_saved)
options(e, humans=2, link=True, open_lobby=False)
assert rules(e) == (0, 1, 1, 2, 5)
change(e, 1)
change(e, 5)  # Confirm as cable host and open the lobby.
assert e.state()[3] == 30
cable_save = c.string_at(sram(e), SAVE_END)
e.close()

e = resume(cable_save)
options(e, humans=2)
assert rules(e) == (0, 0, 1, 2, 5)
e.close()

corrupt = bytearray(cable_save)
corrupt[RULES_OFFSET + 2] ^= 1
e = resume(corrupt)
options(e, humans=3)
assert rules(e) == (1, 1, 1, 0, 3)
e.close()

e = resume(corrupt)
options(e)
assert rules(e) == (1, 0, 1, 0, 3)
e.close()

print('Saved rules restored for solo, local multiplayer, and cable hosts')
