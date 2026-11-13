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
parser.add_argument('--animations',action='store_true',help='assert local animation advances without pose events')
parser.add_argument('--benchmark',action='store_true',help='measure updates and wire transfers in a fixed simulated interval')
parser.add_argument('--native', action='store_true', help='use the stock mGBA lockstep driver, without fault injection')
parser.add_argument('--rom', type=Path, default=ROOT / 'build/gba/pole.gba')
parser.add_argument('--elf', type=Path, default=ROOT / 'build/gba/pole.elf')
parser.add_argument('--join-order', choices=('together','host-first','client-first'), default='together')
parser.add_argument('--join-delay', type=int, default=2400, help='frames before remaining consoles confirm avatars')
parser.add_argument('--irq-delay', type=int, default=0,
                    help='delay every 37th slave serial IRQ by this many CPU cycles')
parser.add_argument('--time-scale', type=int, choices=range(1, 11), default=1,
                    help='allow for acknowledged transport and initial full snapshots')
args = parser.parse_args()
if args.native and (args.irq_delay or int(os.environ.get('LINK_IRQ_DELAY','0'))):
    parser.error('--native uses unmodified mGBA SIO and cannot inject IRQ delays')
os.environ['LINK_JOIN_ORDER'] = str(('together','host-first','client-first').index(args.join_order))
os.environ['LINK_JOIN_DELAY'] = str(args.join_delay)
os.environ.setdefault('LINK_IRQ_DELAY', str(args.irq_delay))
os.environ.setdefault('LINK_TIME_SCALE', str(args.time_scale))
build = Path(os.environ['MGBA_BUILD']).resolve()
flags = []
for line in (build / 'CMakeFiles/mgba.dir/flags.make').read_text().splitlines():
    if line.startswith(('C_DEFINES =', 'C_INCLUDES =')):
        flags += shlex.split(line.split('=', 1)[1])
    if line.startswith('C_FLAGS ='):
        flags += [f for f in shlex.split(line.split('=', 1)[1]) if f.startswith('-D')]
if args.native:flags += ['-DLINK_NATIVE']
executable = ROOT / ('build/qa/test-link-native' if args.native else 'build/qa/test-link')
executable.parent.mkdir(exist_ok=True, parents=True)
subprocess.run(['cc', *flags, str(ROOT / 'scripts/test-link.c'), '-L' + str(build),
                '-Wl,-rpath,' + str(build), '-lmgba', '-o', str(executable)], check=True)
s = symbols(args.elf)
s['prefs'] = s.get('prefs', s.get('prefs.0'))
if args.animations:
    os.environ['LINK_ANIMATIONS']='1'
    for key in ('scene','cash','link_events','video_ticks','message1','message2','message_tokens'):os.environ['LINK_'+key.removeprefix('link_').upper()+'_ADDR']=hex(s[key])
if args.benchmark:
    os.environ['LINK_BENCHMARK']='1';os.environ['LINK_STAGE_ADDR']=hex(s['link_stage'])
for key in ('link_create','link_avatar_edit','link_name_edit'):
 if key in s:os.environ[key.upper()+'_ADDR']=hex(s[key])
 else:os.environ.pop(key.upper()+'_ADDR',None)
for count in ([args.consoles] if args.consoles else (2, 3)):
    for scenario in ([args.scenario] if args.scenario is not None else range(6)):
        print(f'RUN: {count} consoles, name scenario {scenario}', flush=True)
        subprocess.run([str(executable), str(args.rom), str(count)]
                       + [hex(s[k]) for k in ('game', 'mp', 'prefs', 'avatars')]
                       + [str(scenario)]
                       + [hex(s[k]) for k in ('link_name_edit', 'link_name_answer',
                                             'link_name_pos', 'link_name_cursor')]
                       + [hex(s['match']),hex(s.get('prefs.4',s['prefs']+16)),hex(s.get('prefs.5',s['prefs']+20))], check=True)
