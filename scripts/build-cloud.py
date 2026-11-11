"""Linux equivalent of build.ps1; extract resources only in an ignored staging tree."""
from pathlib import Path
import hashlib
import json
import os
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def main():
    tools = Path(os.environ.get('WONDERFIELD_TOOLS_DIR', '/workspace/.tools/wonderfield'))
    zig = [os.environ['ZIG_EXE']] if 'ZIG_EXE' in os.environ else [str(tools / 'bin/python'), '-m', 'ziglang']
    version = subprocess.check_output(zig + ['version'], text=True).strip()
    if version != '0.13.0':
        raise SystemExit(f'Zig 0.13.0 required, found {version}')
    originals = ROOT / 'originals/Wonderfield'
    manifest = json.loads((ROOT / 'analysis/originals.json').read_text())
    problems = []
    for name, entry in manifest.items():
        path = originals / name
        if not path.is_file():
            problems.append(f'missing: {path}')
        elif path.stat().st_size != entry['bytes'] or hashlib.sha256(path.read_bytes()).hexdigest() != entry['sha256']:
            problems.append(f'size/SHA-256 mismatch: {path}')
    if problems:
        raise SystemExit('\n'.join(problems))

    stage = ROOT / 'build/cloud-source'
    stage.mkdir(parents=True, exist_ok=True)
    for name in ('scripts', 'src', 'gba', 'assets', 'analysis'):
        shutil.copytree(ROOT / name, stage / name, dirs_exist_ok=True,
                        ignore=shutil.ignore_patterns('__pycache__'))
    staged_originals = stage / 'originals/Wonderfield'
    staged_originals.mkdir(parents=True, exist_ok=True)
    for name in manifest:
        shutil.copy2(originals / name, staged_originals / name)
    env = os.environ.copy()
    env['PYTHONDONTWRITEBYTECODE'] = '1'
    env['ZIG_GLOBAL_CACHE_DIR'] = str(ROOT / 'build/zig-cache')

    def run(args):
        subprocess.run(args, cwd=stage, env=env, check=True)

    (stage / 'build/gba').mkdir(parents=True, exist_ok=True)
    run([sys.executable, 'scripts/extract.py'])
    run([sys.executable, 'scripts/pack.py'])
    flags = ['cc', '-target', 'thumb-freestanding-eabi', '-mcpu=arm7tdmi',
             '-std=c11', '-O2', '-g', '-Wall', '-Wextra', '-Werror',
             '-ffreestanding', '-fno-stack-protector', '-fno-unwind-tables',
             '-fno-asynchronous-unwind-tables', '-fno-pic',
             '-I', 'build/generated', '-I', 'gba', '-c']
    for source, name in [('build/generated/main.c', 'main'),
                         ('build/generated/assets.c', 'assets'),
                         ('gba/runtime.c', 'runtime'), ('gba/speaker.c', 'speaker')]:
        run(zig + flags + [source, '-o', f'build/gba/{name}.o'])
    for name in ('startup', 'division'):
        run(zig + ['cc', '-target', 'arm-freestanding-eabi', '-mcpu=arm7tdmi',
                   '-c', f'gba/{name}.S', '-o', f'build/gba/{name}.o'])
    run(zig + ['ld.lld', '-T', 'gba/pole.ld', '--gc-sections',
               '-Map=build/gba/pole.map'] +
        [f'build/gba/{name}.o' for name in
         ('startup', 'main', 'assets', 'runtime', 'division', 'speaker')] +
        ['-o', 'build/gba/pole.elf'])
    run([sys.executable, 'scripts/finish_rom.py'])
    for name in ('generated', 'gba'):
        shutil.copytree(stage / 'build' / name, ROOT / 'build' / name, dirs_exist_ok=True)
    # The original report refers to build/gba/pole.gba relative to the staging root.
    # That relative path is also the final output location.
    (ROOT / 'dist').mkdir(exist_ok=True)
    shutil.copy2(ROOT / 'build/gba/pole.gba', ROOT / 'dist/pole 2.0beta1.gba')
    print('ROM: dist/pole 2.0beta1.gba')


if __name__ == '__main__':
    main()
