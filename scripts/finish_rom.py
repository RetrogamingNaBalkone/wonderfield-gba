from pathlib import Path
import struct,hashlib,json
root=Path(__file__).resolve().parents[1]; p=root/'build/gba/pole.gba'
elf=(root/'build/gba/pole.elf').read_bytes()
assert elf[:7]==b'\x7fELF\x01\x01\x01'
assert struct.unpack_from('<H',elf,18)[0]==40
phoff=struct.unpack_from('<I',elf,28)[0];phsize,phnum=struct.unpack_from('<HH',elf,42)
segments=[]
for i in range(phnum):
 kind,off,va,pa,size,memsize,flags,align=struct.unpack_from('<8I',elf,phoff+i*phsize)
 if kind==1 and size and 0x08000000<=pa<0x0a000000:segments.append((pa-0x08000000,elf[off:off+size]))
assert segments
b=bytearray(b'\xff'*max(off+len(data) for off,data in segments))
for off,data in segments:b[off:off+len(data)]=data
logo=bytes.fromhex('24ffae51699aa2213d84820a84e409ad11248b98c0817f21a352be199309ce2010464a4af82731ec58c7e83382e3cebf85f4df94ce4b09c194568ac01372a7fc9f844d73a3ca9a615897a327fc039876231dc7610304ae56bf38840040a70efdff52fe036f9530f197fbc08560d68025a963be03014e38e2f9a234ffbb3e0344780090cb88113a9465c07c6387f03cafd625e48b380aac7221d4f807')
assert len(logo)==156 and b[3]==0xea
b[4:160]=logo;b[160:192]=bytes(32);b[160:172]=b'POLE CHUDES ';b[172:176]=b'PC01';b[176:178]=b'00';b[178]=0x96;b[189]=(-sum(b[160:189])-0x19)&255
assert (sum(b[160:190])+0x19)&255==0
b.extend(b'\xff'*((1<<(len(b)-1).bit_length())-len(b)));p.write_bytes(b)
report=dict(rom=str(p.relative_to(root)),bytes=len(b),sha256=hashlib.sha256(b).hexdigest(),checksum=b[189])
(root/'build/gba/build-report.json').write_text(json.dumps(report,indent=2))
print(json.dumps(report))
