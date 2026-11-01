// Independent decoder: raw RGBA captured from mGBA, no PNG processing.
const fs = require('fs');
const jsQR = require('./vendor/jsqr/jsQR.js');
const pixels = Uint8ClampedArray.from(fs.readFileSync(process.argv[2]));
const result = jsQR(pixels, 240, 160, { inversionAttempts: 'dontInvert' });
if (!result) throw new Error('No QR code found in the mGBA frame');
process.stdout.write(JSON.stringify({ data: result.data, version: result.version }));
