"""Compare decoded DOS LIB pixels and EXE tables, without modifying port assets."""
from pathlib import Path
import argparse,hashlib,json,struct

def digest(b):return hashlib.sha256(b).hexdigest()
def sprites(path):
 b=path.read_bytes();p=128;out=[]
 for i,n in enumerate(b[1:b[0]+1]):
  chunk=b[p:p+n*128];w,h,extra=struct.unpack_from('<HHH',chunk);q=6;pixels=[]
  for y in range(h):
   length=struct.unpack_from('<H',chunk,q)[0];end=q+2+length;q+=2;row=[]
   while q<end-1:
    control=chunk[q];q+=1
    if control>=128:row.extend([chunk[q]]*(control-128));q+=1
    else:row.extend(chunk[q:q+control]);q+=control
   assert q==end-1 and len(row)==w,(path,i,y)
   pixels.extend(row);q=end
  out.append(dict(id=i,width=w,height=h,pixels=bytes(pixels),sha256=digest(bytes(pixels)),encoded_sha256=digest(chunk),offset=p));p+=n*128
 assert p==len(b)
 return out

def tables(path,ds_offset,count,gifts_offset):
 b=path.read_bytes();ds=struct.unpack_from('<H',b,8)[0]*16+ds_offset
 chars=[];gifts=[]
 for i in range(count):
  p=ds+2+i*13;sprite,n=struct.unpack_from('<HB',b,p);assert n<=10
  chars.append(dict(name=b[p+3:p+3+n].decode('cp866'),sprite=sprite))
 for i in range(10):
  p=ds+gifts_offset+i*25;n=b[p];assert n<=24;gifts.append(b[p+1:p+1+n].decode('cp866'))
 return dict(characters=chars,gifts=gifts)
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('old',type=Path);p.add_argument('new',type=Path);p.add_argument('out',type=Path);a=p.parse_args();a.out.mkdir(parents=True,exist_ok=True)
 old,new=sprites(a.old/'POLE.LIB'),sprites(a.new/'POLE2.LIB')
 ot=tables(a.old/'POLE.EXE',0xc790,6,0x19a);nt=tables(a.new/'POLE2.EXE',0xce50,8,0x1bc)
 matches=[]
 for n in new:
  matches.append(dict(new_id=n['id'],old_ids=[o['id'] for o in old if (o['width'],o['height'],o['sha256'])==(n['width'],n['height'],n['sha256'])]))
 report=dict(old=ot,new=nt,old_sprite_count=len(old),new_sprite_count=len(new),pixel_matches=matches,unchanged_legacy_library=(a.old/'POLE.LIB').read_bytes()==(a.new/'POLE.LIB').read_bytes(),unchanged_font=(a.old/'POLE.FNT').read_bytes()==(a.new/'POLE.FNT').read_bytes(),gifts_identical=ot['gifts']==nt['gifts'])
 (a.out/'resources-diff.json').write_text(json.dumps(report,ensure_ascii=False,indent=2)+'\n')
 from PIL import Image,ImageDraw
 palette=[(0,0,0),(0,0,170),(0,170,0),(0,170,170),(170,85,0),(255,170,170),(255,170,85),(170,170,170),(85,85,85),(85,85,255),(85,255,85),(85,255,255),(255,85,85),(255,85,255),(255,255,85),(255,255,255)]
 for title,items in [('old',old),('new',new)]:
  sheet=Image.new('RGB',(6*230,((len(items)+5)//6)*180),(70,70,70));d=ImageDraw.Draw(sheet)
  for s in items:
   pic=Image.frombytes('P',(s['width'],s['height']),s['pixels']);pic.putpalette(sum((list(c) for c in palette),[]));pic.thumbnail((220,155),Image.Resampling.NEAREST)
   x=(s['id']%6)*230;y=(s['id']//6)*180;sheet.paste(pic.convert('RGB'),(x,y+20));d.text((x+4,y+2),f'{s["id"]}: {s["width"]}x{s["height"]}',fill='white')
  sheet.save(a.out/(title+'-sprites.png'))
 print(json.dumps({k:v for k,v in report.items() if k!='pixel_matches'},ensure_ascii=False));print('changed/new IDs',[m['new_id'] for m in matches if not m['old_ids']])
