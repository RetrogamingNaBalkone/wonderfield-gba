"""Cable input event tests against the production functions in link.inc."""
import os
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[1]
source = (ROOT / 'src/link.inc').read_text()
start = source.index('/* Logical input events')
end = source.index('/* Compare rule state, not the clock')
qa = ROOT / 'build/qa'
qa.mkdir(parents=True, exist_ok=True)
(qa / 'link-input-under-test.inc').write_text(source[start:end])
exe = qa / 'link-input'
subprocess.run([os.environ.get('CC', 'cc'), '-std=c11', '-O1', '-g', '-Wall', '-Wextra', '-Werror',
                '-fsanitize=address,undefined', '-I', str(qa),
                str(ROOT / 'scripts/test-link-input.c'), '-o', str(exe)], check=True)
result = subprocess.run([str(exe)], capture_output=True, text=True)
lines = result.stdout.splitlines()
for line in lines:
    if not line.startswith('PASS') or 'taps every' not in line:
        print(line)
print(f"{sum(l.startswith('PASS') for l in lines)} checks passed, {sum(l.startswith('FAIL') for l in lines)} failed")
raise SystemExit(result.returncode)
