import extract as e,json
a=json.loads((e.OUT/'sprites.json').read_text())
w=960;h=1000;pix=[7]*(w*h);f=(e.OUT/'font-8.bin').read_bytes()
for s in a:
 x=(s['id']%8)*120;y=(s['id']//8)*125
 b=(e.OUT/f"sprite-{s['id']:02}.bin").read_bytes(); scale=min(1,114/s['width'],105/s['height'])
 for yy in range(int(s['height']*scale)):
  for xx in range(int(s['width']*scale)):pix[(y+yy+14)*w+x+xx]=b[int(yy/scale)*s['width']+int(xx/scale)]
 for j,c in enumerate(str(s['id'])):
  for yy in range(8):
   for xx in range(8):
    if f[ord(c)*8+yy]&(128>>xx):pix[(y+yy)*w+x+j*8+xx]=0
e.png(e.OUT/'contact.png',w,h,pix,e.EGA)
