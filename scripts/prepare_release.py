"""Prepare the verified ROM and its checksum for publication."""
from pathlib import Path
import hashlib
import json

root = Path(__file__).resolve().parents[1]
release = root / 'build/release'
release.mkdir(parents=True, exist_ok=True)
rom = (root / 'build/gba/pole.gba').read_bytes()
digest = hashlib.sha256(rom).hexdigest()

reports = (
    'verification.json', 'visual-verification.json', 'events-verification.json',
    'flows-verification.json', 'ai-chests-verification.json', 'stage-verification.json',
    'v11-verification.json', 'performance-verification.json', 'records-verification.json',
    'controls-verification.json', 'authors-verification.json', 'rng-verification.json',
    'rng-audit.json', 'rng-cold.json', 'rng-live-mash.json',
)
for name in reports:
    report = json.loads((root / 'docs/reports' / name).read_text(encoding='utf-8'))
    assert report['status'] == 'passed' and report['rom_sha256'] == digest, name

rom_name = 'pole.2.0beta2.gba'
(release / rom_name).write_bytes(rom)
(release / 'SHA256SUMS').write_text(f'{digest}  {rom_name}\n', encoding='ascii')
print(f'Release files: {rom_name}, SHA256SUMS')
