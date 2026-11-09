"""Import only checksum-verified original files from a supplied RAR/ZIP archive."""
from pathlib import Path
import hashlib
import json
import sys

import libarchive

ROOT = Path(__file__).resolve().parents[1]


def main():
    if len(sys.argv) != 2:
        raise SystemExit('Usage: import-cloud-originals.py /path/to/Pole_Chudes.rar')
    manifest = json.loads((ROOT / 'analysis/originals.json').read_text())
    found = {}
    with libarchive.file_reader(sys.argv[1]) as entries:
        for entry in entries:
            name = Path(entry.pathname.replace('\\', '/')).name
            if name not in manifest:
                continue
            if name in found:
                raise SystemExit(f'Duplicate archive entry: {name}')
            data = bytearray()
            for block in entry.get_blocks():
                data.extend(block)
                if len(data) > manifest[name]['bytes']:
                    raise SystemExit(f'Unexpected size: {name}')
            expected = manifest[name]
            if len(data) != expected['bytes'] or hashlib.sha256(data).hexdigest() != expected['sha256']:
                raise SystemExit(f'Size/SHA-256 mismatch: {name}')
            found[name] = bytes(data)
    missing = set(manifest) - set(found)
    if missing:
        raise SystemExit(f'Missing archive entries: {sorted(missing)}')
    output = ROOT / 'originals/Wonderfield'
    # Check existing files before writing anything; never replace differing user data.
    for name, data in found.items():
        path = output / name
        if path.exists() and path.read_bytes() != data:
            raise SystemExit(f'Refusing to overwrite existing file: {path}')
    output.mkdir(parents=True, exist_ok=True)
    for name, data in found.items():
        path = output / name
        if not path.exists():
            path.write_bytes(data)
        print(f'{name}: size and SHA-256 OK')


if __name__ == '__main__':
    main()
