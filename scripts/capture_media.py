"""Lossless GIF capture for actual emulator frames (stdlib only)."""
import struct

def gif(path,frames,fmt,delay=8):
 """Lossless GIF, fixed-width LZW with frequent clear codes (stdlib only)."""
 values=[];lookup={};indexed=[]
 size=4 if fmt==1 else 2
 for frame in frames:
  out=bytearray()
  for v, in struct.iter_unpack('<I' if size==4 else '<H',frame):
   if v not in lookup:lookup[v]=len(values);values.append(v)
   out.append(lookup[v])
  indexed.append(out)
 assert len(values)<=16,'Emulated capture leaves the original palette'
 bits=max(2,(len(values)-1).bit_length());table=1<<bits;palette=bytearray()
 for v in values:
  if fmt==1:palette.extend(((v>>16)&255,(v>>8)&255,v&255))
  else:
   g=6 if fmt==2 else 5;palette.extend((((v>>(5+g))&31)*255//31,((v>>5)&((1<<g)-1))*255//((1<<g)-1),(v&31)*255//31))
 palette.extend(bytes(table*3-len(palette)))
 data=bytearray(b'GIF89a'+struct.pack('<HHBBB',240,160,0x80|0x70|(bits-1),0,0))+palette
 data+=b'!\xff\x0bNETSCAPE2.0\x03\x01\x00\x00\x00'
 clear=1<<bits;end=clear+1;width=bits+1
 for frame in indexed:
  data+=b'!\xf9\x04'+struct.pack('<BHB',4,delay,0)+b'\0'
  data+=b','+struct.pack('<HHHHB',0,0,240,160,0)+bytes([bits])
  packed=bytearray();acc=0;n=0
  # No dictionary expansion reaches the next code width before a clear.
  codes=[]
  for p in range(0,len(frame),8):codes.append(clear);codes.extend(frame[p:p+8])
  codes.append(end)
  for value in codes:
   acc|=value<<n;n+=width
   while n>=8:packed.append(acc&255);acc>>=8;n-=8
  if n:packed.append(acc&255)
  for p in range(0,len(packed),255):part=packed[p:p+255];data.append(len(part));data+=part
  data+=b'\0'
 data+=b';';path.write_bytes(data)
