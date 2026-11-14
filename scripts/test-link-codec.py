"""Property/bounds tests against the actual snapshot codec, with ASan/UBSan."""
import os
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
source = (ROOT / 'src/link.inc').read_text()
codec = source.split('/* Snapshot byte codec.', 1)[1].split('/* End snapshot byte codec. */', 1)[0]
codec = codec.split('*/', 1)[1]
qa = ROOT / 'build/qa'
qa.mkdir(parents=True, exist_ok=True)
(qa / 'link-codec-under-test.inc').write_text(codec)
for size in (16, 256, 1024, 4096):
    exe = qa / f'link-codec-{size}'
    subprocess.run([os.environ.get('CC', 'cc'), '-std=c11', '-O1', '-g',
                    '-Wall', '-Wextra', '-Werror', '-fsanitize=address,undefined',
                    f'-DCODEC_SNAPSHOT_SIZE={size}', '-I', str(qa),
                    str(ROOT / 'scripts/test-link-codec.c'), '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
    print(f'PASS snapshot size {size}', flush=True)
