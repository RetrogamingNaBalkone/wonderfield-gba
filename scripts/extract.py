"""Lossless resource extraction from POLE; formats recovered using Ghidra."""
from pathlib import Path
import struct, json, hashlib, zlib, binascii, re
ROOT=Path(__file__).resolve().parents[1]
SRC=ROOT/'originals/Wonderfield'
OUT=ROOT/'assets'; OUT.mkdir(exist_ok=True)
def text(b):
    return b.decode('cp866')
def png(path,w,h,pixels,palette):
    def chunk(t,d): return struct.pack('>I',len(d))+t+d+struct.pack('>I',binascii.crc32(t+d)&0xffffffff)
    raw=b''.join(b'\0'+bytes(pixels[y*w:(y+1)*w]) for y in range(h))
    Path(path).write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',w,h,8,3,0,0,0))+chunk(b'PLTE',bytes(sum((list(c) for c in palette),[])))+chunk(b'IDAT',zlib.compress(raw))+chunk(b'IEND',b''))
EGA=[(0,0,0),(0,0,170),(0,170,0),(0,170,170),(170,85,0),(255,170,170),(255,170,85),(170,170,170),(85,85,85),(85,85,255),(85,255,85),(85,255,255),(255,85,85),(255,85,255),(255,255,85),(255,255,255),(255,0,255)]
def sprites():
    lib=(SRC/'POLE.LIB').read_bytes(); p=128; result=[]
    for i,n in enumerate(lib[1:1+lib[0]]):
        b=lib[p:p+n*128]; w,h,unknown=struct.unpack_from('<HHH',b)
        q=6; rows=[]
        for y in range(h):
            length=struct.unpack_from('<H',b,q)[0]; end=q+2+length; q+=2; row=[]
            while q<end-1:
                control=b[q]; q+=1
                if control>=128: row.extend([b[q]]*(control-128)); q+=1
                else: row.extend(b[q:q+control]); q+=control
            # The decoder consumes one lookahead byte after the last run.
            assert q==end-1,(i,y,q,end)
            q=end
            assert len(row)==w,(i,y,len(row),w)
            rows.extend(row)
        assert max(rows)<=15,(i,max(rows))
        png(OUT/f'sprite-{i:02}.png',w,h,rows,EGA)
        (OUT/f'sprite-{i:02}.bin').write_bytes(bytes(rows))
        result.append(dict(id=i,offset=p,allocated=len(b),width=w,height=h,header=unknown,consumed=q))
        p+=n*128
    assert p==len(lib),(p,len(lib))
    (OUT/'sprites.json').write_text(json.dumps(result,indent=2))
    return result
def fonts():
    b=(SRC/'POLE.FNT').read_bytes(); p=0
    for height in (6,8,14):
        data=b[p:p+256*height]; (OUT/f'font-{height}.bin').write_bytes(data)
        pixels=[0]*(128*height*16)
        for c in range(256):
            for y in range(height):
                for x in range(8): pixels[((c//16)*height+y)*128+(c%16)*8+x]=15 if data[c*height+y]&(128>>x) else 0
        png(OUT/f'font-{height}.png',128,height*16,pixels,EGA)
        p+=256*height
def inspect():
    exe=(SRC/'POLE.EXE').read_bytes(); header=struct.unpack_from('<H',exe,8)[0]*16
    # Pascal literal strings referenced by recovered code; retain binary bytes.
    src=(ROOT/'analysis/decompiled.c').read_text()
    strings=[]
    for off in sorted(set(int(x,16) for x in re.findall(r'0x([0-9a-f]{3,4})',src.split('/* 174b:')[0]))):
        seg=0x1000; pos=header+off
        if pos<len(exe):
            n=exe[pos]; b=exe[pos+1:pos+1+n]
            if 2<=n<=120 and all(c>=32 for c in b) and all(' '<=c<='~' or 'А'<=c<='я' or c in 'Ёё' for c in text(b)): strings.append(dict(address=f'{seg:04x}:{off:04x}',text=text(b),hex=b.hex()))
    (ROOT/'analysis/strings.json').write_text(json.dumps(strings,ensure_ascii=False,indent=2),encoding='utf-8')
    hashes={p.name:dict(bytes=p.stat().st_size,sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in SRC.iterdir()}
    manifest=ROOT/'analysis/originals.json'
    if manifest.exists():assert json.loads(manifest.read_text())==hashes,'Original files changed; inspect originals.json'
    else:manifest.write_text(json.dumps(hashes,indent=2))
def words():
    b=(SRC/'POLE.OVL').read_bytes(); count=int(b[1:1+b[0]])
    assert len(b)==21+count*42
    records=[]
    for i in range(count):
        fields=[]; raw=[]
        for pos in (21+i*42,42+i*42):
            n=b[pos]; assert 0<n<=20
            v=bytes((x-32)&255 for x in b[pos+1:pos+1+n]); fields.append(text(v));raw.append(v.hex())
        assert all('А'<=c<='Я' or c in ' -' for c in fields[0]),(i,fields)
        records.append(dict(id=i,offset=21+i*42,word=fields[0],topic=fields[1],word_hex=raw[0],topic_hex=raw[1]))
    (OUT/'words.json').write_text(json.dumps(records,ensure_ascii=False,indent=2),encoding='utf-8')
    print(f'Extracted {count} original word/topic pairs')
if __name__=='__main__':
    inspect(); fonts(); sprites(); words()
