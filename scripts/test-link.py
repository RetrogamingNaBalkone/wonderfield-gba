"""Build/run the SIO harness using matching mGBA source/build ABI definitions.

MGBA_BUILD points to a CMake Unix Makefiles build of the mGBA shared library.
"""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
from emulator import ROOT, symbols

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--consoles', type=int, choices=(2, 3))
parser.add_argument('--scenario', type=int, choices=range(6))
args = parser.parse_args()
build = Path(os.environ['MGBA_BUILD']).resolve()
flags = []
for line in (build / 'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
    if line.startswith(('C_DEFINES =', 'C_INCLUDES =')):
        flags += shlex.split(line.split('=', 1)[1])
executable = ROOT / 'build/qa/test-link'
executable.parent.mkdir(exist_ok=True, parents=True)
subprocess.run(['cc', *flags, str(ROOT / 'scripts/test-link.c'), '-L' + str(build),
                '-Wl,-rpath,' + str(build), '-lmgba', '-o', str(executable)], check=True)
s = symbols()
s['prefs'] = s.get('prefs', s.get('prefs.0'))
for count in ([args.consoles] if args.consoles else (2, 3)):
    for scenario in ([args.scenario] if args.scenario is not None else range(6)):
        print(f'RUN: {count} consoles, name scenario {scenario}', flush=True)
        subprocess.run([str(executable), str(ROOT / 'build/gba/pole.gba'), str(count)]
                       + [hex(s[k]) for k in ('game', 'mp', 'prefs', 'avatars')]
                       + [str(scenario)]
                       + [hex(s[k]) for k in ('link_name_edit', 'link_name_answer',
                                             'link_name_pos', 'link_name_cursor')]
                       + [hex(s['match']),hex(s.get('prefs.4',s['prefs']+16)),hex(s.get('prefs.5',s['prefs']+20))], check=True)
