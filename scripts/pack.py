"""Produce ROM data and CP866 C source without third-party dependencies."""
from pathlib import Path
import json,struct,re,math
from extract import ROOT,OUT,SRC,EGA
from pixel_art import outlined_resize,wheel_symbol,title_logo_resize
GEN=ROOT/'build/generated'; GEN.mkdir(parents=True,exist_ok=True)
def cstr(b):return '"'+''.join('\\%03o'%x for x in b)+'"'
def arr(name,b):return f'const unsigned char {name}[] __attribute__((aligned(4)))={{'+','.join(map(str,b))+'};\n'

def build_stage(half):
 stage=bytearray([7]*240*160)
 for y in range(5):stage[y*240:(y+1)*240]=bytes([3]*240)
 for y in range(5,56):stage[y*240:(y+1)*240]=bytes([1]*240)
 def put(item,x,y,transparent):
  w,h,b=item
  for yy in range(h):
   for xx in range(w):
    v=b[yy*w+xx]
    if v!=transparent and 0<=x+xx<240 and 0<=y+yy<160:stage[(y+yy)*240+x+xx]=v
 for row in range(3):
  for col in range(12):put(half[31+(col+row*5)%3],col*20,6+row*15,1)
 # User-requested extension: the lower course is drawn in the original palette.
 stone=(OUT/'generated/blue-stone-extension.bin').read_bytes()
 assert len(stone)==192*64 and set(stone)<={0,1,7,9}
 for y in range(43,56):
  for x in range(240):stage[y*240+x]=stone[(51+y-43)*192+x%192]
 put(half[40],0,12,7);put(half[41],225,12,7);put(half[34],23,0,7);put(half[34],210,0,7)
 return bytes(stage)
def main():
 code=['#include "assets.h"\n']; metadata=json.loads((OUT/'sprites.json').read_text()); sprites=[]; normalized=[]; half=[]; half_refs=[]
 for s in metadata:
  w,h=s['width'],s['height']; raw=(OUT/f"sprite-{s['id']:02}.bin").read_bytes();b=raw
  # EGA 640x350 is displayed at 4:3: source pixel aspect = 35/48.
  # Normalize once, then use identical horizontal/vertical scale in-game.
  nw=max(1,round(w*35/48)); b=bytes(b[y*w+min(w-1,x*w//nw)] for y in range(h) for x in range(nw))
  code.append(arr(f'sprite_data_{s["id"]}',b)); sprites.append(f'{{{nw},{h},sprite_data_{s["id"]}}}')
  normalized.append((nw,h,b))
  sw,sh=max(1,round(w*35/96)),max(1,round(h/2))
  small=bytes(raw[min(h-1,y*h//sh)*w+min(w-1,x*w//sw)] for y in range(sh) for x in range(sw))
  if s['id'] in (21,22,23,24,25,26,48,49,50,51):small=outlined_resize(raw,w,h,sw,sh,2)
  elif s['id'] in (27,42,45):small=outlined_resize(raw,w,h,sw,sh,3)
  elif s['id'] in (43,44):small=outlined_resize(raw,w,h,sw,sh,5)
  code.append(arr(f'small_data_{s["id"]}',small));half.append((sw,sh,small));half_refs.append(f'{{{sw},{sh},small_data_{s["id"]}}}')
 code.append('const Sprite sprites[57]={'+','.join(sprites)+'};\n')
 code.append('const Sprite sprites_half[57]={'+','.join(half_refs)+'};\n')
 # The large title gets its own carefully reduced masks; DOS resources and
 # the smaller logos on the certificate/cash screens retain their original ink.
 title_refs=[]
 for id in (46,47):
  w,h=metadata[id]['width'],metadata[id]['height'];raw=(OUT/f'sprite-{id:02}.bin').read_bytes()
  tw,th=round(w*35/48)*150//256,h*150//256
  code.append(arr(f'title_logo_data_{id}',title_logo_resize(raw,w,h,tw,th,id)))
  title_refs.append(f'{{{tw},{th},title_logo_data_{id}}}')
 code.append('const Sprite title_logos[2]={'+','.join(title_refs)+'};\n')
 # Large payouts skip directly to one prepared DOS-style finished picture.
 # Draw these stamps at build time; the ARM7 only copies a bitmap on A.
 finished=bytearray([7]*38400)
 def cash_blit(item,x,y,transparent,bottom=160):
  w,h,pixels=item
  for yy in range(min(h,bottom-y)):
   row=(y+yy)*240+x
   for xx in range(w):
    color=pixels[yy*w+xx]
    if color!=transparent:finished[row+xx]=color
 for id,x,y,transparent in ((46,4,4,7),(47,73,4,7),(27,185,75,-1),(45,196,76,-1),(43,204,94,-1)):
  cash_blit(half[id],x,y,transparent)
 seed=1
 for _ in range(100000):
  seed=(seed*134775813+1)&0xffffffff
  seed=(seed*134775813+1)&0xffffffff;x=((seed>>16)%400)*35//96
  seed=(seed*134775813+1)&0xffffffff;y=((seed>>16)%295)//2
  cash_blit(half[56],x,y,2,152)
 code.append(arr('cash_finished_bitmap',finished))
 stage=build_stage(half)
 # Bake wheel composites from original sprites; scaling is not repeated per frame.
 labels=[4,5,12,6,14,7,13,6,12,8,11,5,10,7,9,8]
 wheel=[];wheel_labels=[];symbol_cache={}
 for id in set(labels):
  ow,oh=metadata[id]['width'],metadata[id]['height'];raw=(OUT/f'sprite-{id:02}.bin').read_bytes();h=12;w=round(ow*35/48*h/oh)
  symbol_cache[id]=(w,h,wheel_symbol(raw,ow,oh,w,h,id))
 for frame in range(32):
  # Keep the blue wall visible through transparent areas above the wheel.
  pixels=bytearray(b''.join(stage[(43+y)*240+32:(43+y)*240+160] for y in range(112)))
  def blit(item,x,y,transparent):
   w,h,b=item
   for yy in range(h):
    for xx in range(w):
     color=b[yy*w+xx]
     if color!=transparent and 0<=x+xx<128 and 0<=y+yy<112:pixels[(y+yy)*128+x+xx]=color
  # Original 32-step cycle: the four DOS wheel frames at 11.25-degree steps.
  # The common disk (without protruding handles) is 197x148 source pixels.
  # 100x103 gives a round 88x89 px disk; source canvas dimensions alone mislead.
  id=(frame+3)%4;source=(OUT/f'sprite-{id:02}.bin').read_bytes();ow,oh=metadata[id]['width'],metadata[id]['height'];w,h=100,103
  b=bytes(source[y*oh//h*ow+x*ow//w] for y in range(h) for x in range(w))
  blit((w,h,b),64-w//2,56-h//2,3)
  base=bytes(pixels);occupied=set()
  for i,id in enumerate(labels):
   angle=((i+frame/2)%16)*math.pi/8;w,h,b=symbol_cache[id]
   desired_x,desired_y=round(64+38*math.cos(angle)-w/2),round(58+38*math.sin(angle)-h/2)
   expected=15 if i%2==0 else 0
   ink=[(xx,yy) for yy in range(h) for xx in range(w) if b[yy*w+xx]!=7]
   choices=[]
   for dy in range(-8,9):
    for dx in range(-8,9):
     x,y=desired_x+dx,desired_y+dy
     points=[(y+yy)*128+x+xx for xx,yy in ink]
     if not all(0<=x+xx<128 and 0<=y+yy<112 for xx,yy in ink):continue
     bad=sum(base[p]!=expected for p in points);overlap=sum(p in occupied for p in points)
     choices.append((bad+overlap*100,dx*dx+dy*dy,bad,overlap,x,y,points))
   _,_,bad,overlap,x,y,points=min(choices,key=lambda v:v[:2]);occupied.update(points)
   wheel_labels.append(dict(frame=frame,sector=i,resource=id,x=x,y=y,width=w,height=h,expected_background=expected,noncontrasting_pixels=bad,overlapping_pixels=overlap))
   blit((w,h,b),x,y,7)
  blit(half[16],63,33,7)
  wheel.extend(pixels)
 code.append(arr('wheel_bitmaps',wheel))
 assert all(p['noncontrasting_pixels']==0 and p['overlapping_pixels']==0 for p in wheel_labels),'Sector signs leave their contrasting wedge'
 (GEN/'wheel-labels.json').write_text(json.dumps(wheel_labels,indent=2))
 code.append(arr('stage_background',stage))
 for h in (6,8,14):code.append(arr(f'font{h}',(OUT/f'font-{h}.bin').read_bytes()))
 words=json.loads((OUT/'words.json').read_text(encoding='utf-8'))
 code.append('const Word words[495]={'+','.join('{'+cstr(bytes.fromhex(s['word_hex']))+','+cstr(bytes.fromhex(s['topic_hex']))+'}' for s in words)+'};\n')
 exe=(SRC/'POLE.EXE').read_bytes(); header=struct.unpack_from('<H',exe,8)[0]*16; ds=header+0xc790
 for name,off,n in [('wheel_sectors',0x50,16),('sector_values',0x70,12)]:
  vals=struct.unpack_from('<'+'h'*n,exe,ds+off); code.append(f'const short {name}[{n}]={{'+','.join(map(str,vals))+'};\n')
 names=[]; ids=[]
 for i in range(6):
  p=ds+2+i*13;ids.append(struct.unpack_from('<H',exe,p)[0]);n=exe[p+2];names.append(cstr(exe[p+3:p+3+n]))
 code.append('const char *const opponent_names[6]={'+','.join(names)+'};\n')
 code.append('const unsigned char opponent_sprites[6]={'+','.join(map(str,ids))+'};\n')
 palette=[(r>>3)|((g>>3)<<5)|((b>>3)<<10) for r,g,b in EGA[:16]]
 code.append('const unsigned short palette[16]={'+','.join(map(str,palette))+'};\n')
 pic=(SRC/'POLE.PIC').read_bytes();assert len(pic)==8*13
 initial_names=[];initial_scores=[]
 for i in range(8):
  p=i*13;n=pic[p];assert n<=10
  initial_names.append(cstr(pic[p+1:p+1+n]));initial_scores.append(struct.unpack_from('<H',pic,p+11)[0])
 code.append('const char *const initial_names[8]={'+','.join(initial_names)+'};\n')
 code.append('const unsigned short initial_scores[8]={'+','.join(map(str,initial_scores))+'};\n')
 gifts=[]
 for i in range(10):
  p=ds+0x19a+i*25;n=exe[p];assert n<=24;gifts.append(cstr(exe[p+1:p+1+n]))
 code.append('const char *const gift_names[10]={'+','.join(gifts)+'};\n')
 # Every host phrase remains the original Pascal literal, including spelling.
 offsets=[0xd8c,0xd93,0xd9a,0xda1,0xda9,0xdbb,0xdc2,0xdca,0xdda,0xdea,0xdfe,0xe12,0xe26,0xe33,0xe47,0xe54,0xe65,0xe77,0xe7f,0xe90,0xe9f,0xea6,0xeb5,0xec8,0xe9f,0xf20,0xf3f,0xf45,0xf53,0xf5b,0xf6b,0xf7b,0xffa,0x1004,0x1011,0x101d,0x1029,0xfba,0xfc7,0xfe8,0xff1,0x1a30,0x1a38,0x1fc6,0x41be,0x41c2,0x41c7,0x41cf]
 literals=[]
 offsets += [0x41d7,0x41fd,0x4224,0x4240,0x4261,0x4285,0x46aa,0x46ca,0x46d2,0x46fc,0x4718,0x4739,0x475d,0x4099,0x40d8,0x478c,0x479e]
 for off in dict.fromkeys(offsets+[0xeda,0xee6,0xef1,0xefa,0xf07,0xf10,0xf8a,0xf9a,0xfa9,0xf30,0x5384,0x5391,0x539e,0x53ab,0x568e,0x569c,0x56a8,0x39fd,0x4ebd,0x4ecf,0x4ee3,0x4ef5,0x4f08,0x4f18,0x4f2a,0x4f38,0x4f47,0x4f5a]):
  p=header+off;n=exe[p];b=exe[p+1:p+1+n]
  if 0<n<=120 and all(x>=32 for x in b):literals.append((off,b))
 for off,b in literals:code.append(f'const char msg_{off:x}[]={cstr(b)};\n')
 (GEN/'assets.c').write_text(''.join(code),encoding='ascii')
 hdr='#pragma once\ntypedef struct {int w,h;const unsigned char *data;} Sprite;\ntypedef struct {const char *word,*topic;} Word;\nextern const Sprite sprites[57];\nextern const Word words[495];\nextern const unsigned char font6[],font8[],font14[],opponent_sprites[6];\nextern const char *const opponent_names[6];\nextern const short wheel_sectors[16],sector_values[12];\nextern const unsigned short palette[16];\n'
 hdr+='extern const Sprite sprites_half[57];\nextern const unsigned char wheel_bitmaps[],stage_background[];\nextern const char *const gift_names[10];\nextern const char *const initial_names[8];\nextern const unsigned short initial_scores[8];\n'
 hdr+='extern const unsigned char cash_finished_bitmap[];\n'
 hdr+='extern const Sprite title_logos[2];\n'
 hdr+=''.join(f'extern const char msg_{off:x}[];\n' for off,b in literals)
 (GEN/'assets.h').write_text(hdr)
 for name in ('main.c','presentation.inc','scene.inc'):
  source=(ROOT/'src'/name).read_text(encoding='utf-8')
  source=re.sub(r'"(?:[^"\\]|\\.)*"',lambda m:cstr(m.group()[1:-1].encode('cp866')) if any(ord(c)>127 for c in m.group()) else m.group(),source)
  (GEN/name).write_text(source,encoding='ascii')
if __name__=='__main__':main()
