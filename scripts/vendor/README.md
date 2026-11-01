# Vendored QR tools

- `nayuki/qrcodegen.py`: Project Nayuki QR Code generator, tag `v1.8.0`, MIT.
  Source: https://github.com/nayuki/QR-Code-generator/tree/v1.8.0/python
  Used by `pack.py` with the Python standard library; no network during builds.
- `jsqr/jsQR.js`: published `jsqr@1.4.0` distribution, Apache-2.0.
  Source: https://www.npmjs.com/package/jsqr/v/1.4.0
  Used only by Node.js in independent verification of actual mGBA RGBA frames.

Licenses are stored beside each library. `SHA256.json` records downloaded bytes.
Neither library runs on the GBA; the ROM stores only the packed QR module mask.
