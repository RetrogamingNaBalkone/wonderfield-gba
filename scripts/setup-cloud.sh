#!/usr/bin/env bash
# Tools stay outside the checkout. No root access or devkitARM is needed.
set -euo pipefail
tools_dir="${WONDERFIELD_TOOLS_DIR:-/workspace/.tools/wonderfield}"
python3 -m venv "$tools_dir"
"$tools_dir/bin/python" -m pip install --no-cache-dir 'ziglang==0.13.0' 'libarchive-c==5.3'
"$tools_dir/bin/python" -m ziglang version
repo_dir="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
archive="${WONDERFIELD_ORIGINAL_ARCHIVE:-/workspace/.tools/wonderfield-input/Pole_Chudes.rar}"
if [[ -f "$archive" ]]; then
    "$tools_dir/bin/python" "$repo_dir/scripts/import-cloud-originals.py" "$archive"
fi
