"""Inspect the actual packed ROM sprites; produce a source/nearest/outline sheet."""
import hashlib,json,struct
from pathlib import Path
from PIL import Image,ImageDraw
from emulator import symbols,ROOT
from extract import EGA
rom=(ROOT/'build/gba/pole.gba').read_bytes();sym=symbols()
meta=json.loads((ROOT/'assets/mp-sprites.json').read_text())
sheet=Image.new('RGB',(780,len(meta)*160),(90,90,90));draw=ImageDraw.Draw(sheet);report=[];poses=[]
for index,item in enumerate(meta):
 w,h,p=struct.unpack_from('<iii',rom,sym['extra_sprites']-0x08000000+index*12)
 raw=rom[p-0x08000000:p-0x08000000+w*h]
 source=(ROOT/f'assets/mp-sprite-{item["id"]:02}.bin').read_bytes()
 assert hashlib.sha256(source).hexdigest()==item['sha256']
 assert 0<w<=29 and 0<h<=42 and len(raw)==w*h
 assert set(raw)<=set(source)|{2} and 0 in raw
 if item['id'] in (21,22,57,58,59):poses.append(h)
 original=Image.frombytes('P',(item['width'],item['height']),source)
 original.putpalette(sum((list(c) for c in EGA[:16]),[]))
 sheet.paste(original.resize((round(item['width']*35/48),item['height']),Image.Resampling.NEAREST).convert('RGB'),(10,index*160+30))
 naive=original.resize((w,h),Image.Resampling.NEAREST).convert('RGB').resize((w*4,h*4),Image.Resampling.NEAREST)
 sheet.paste(naive,(250,index*160+20))
 actual=Image.frombytes('P',(w,h),raw);actual.putpalette(sum((list(c) for c in EGA[:16]),[]))
 sheet.paste(actual.convert('RGB').resize((w*4,h*4),Image.Resampling.NEAREST),(490,index*160+20))
 for x,label in [(10,f'DOS #{item["id"]}'),(250,'Nearest'),(490,f'ROM outlined {w}x{h}')]:draw.text((x,index*160+5),label,fill='white')
 report.append(dict(dos_id=item['id'],width=w,height=h,black_pixels=raw.count(0),source_sha256=item['sha256'],rom_pixel_sha256=hashlib.sha256(raw).hexdigest()))
assert len(set(poses))==1,'Human poses must have the same scale'
out=ROOT/'docs/verification';out.mkdir(parents=True,exist_ok=True);sheet.save(out/'character-outlines.png')
(out/'character-assets.json').write_text(json.dumps(dict(rom_sha256=hashlib.sha256(rom).hexdigest(),checks=report),indent=2)+'\n')
print('PASS: 13 lossless source hashes, ROM palette/bounds/black strokes; all human poses have equal height')
