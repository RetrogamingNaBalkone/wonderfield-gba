"""Palette/coverage reduction for outlined DOS sprites, not RGB interpolation.

Transparent green never votes as an opaque colour. Thin black source strokes
are projected with area coverage and given priority on the target silhouette.
Only colours already present in the original image can appear in the result.
"""
import math

def title_logo_resize(raw,w,h,nw,nh,resource):
    """Repair only identified hairline cuts, then reduce the original ink mask.

    The narrow loop in the capital and the counters/letter separations stay
    untouched. These small source regions contain copying seams in the lower
    joins and the cap of the last letter, not intentional letter counters.
    """
    seams={46:((189,138,195,143),),
           47:((233,85,240,94),(149,137,155,142),
               (187,137,193,142),(227,137,233,142))}
    repaired=bytearray(raw)
    for x0,y0,x1,y1 in seams[resource]:
        for y in range(y0,y1+1):
            x=x0
            while x<=x1:
                if raw[y*w+x]!=7:
                    x+=1
                    continue
                start=x
                while x<w and raw[y*w+x]==7:x+=1
                if x<=x1+1 and x-start<=3 and raw[y*w+start-1]==1 and raw[y*w+x]==1:
                    repaired[y*w+start:y*w+x]=bytes([1])*(x-start)
    # One area-based reduction avoids the two nearest-neighbour passes that
    # turn source hairlines into isolated background pixels on the GBA.
    return symbol_resize(repaired,w,h,nw,nh,7)

def wheel_symbol(raw,w,h,nw,nh,resource):
    """Hinted numeral masks; other DOS symbols keep their existing reduction."""
    import json
    from pathlib import Path
    spec=json.loads((Path(__file__).resolve().parents[1]/'assets/wheel-digits.json').read_text())
    label=spec['labels'].get(str(resource))
    if label is None:return symbol_resize(raw,w,h,nw,nh,7,outline=resource==13)
    assert nh==12 and nw==label['width']
    rows=['']*nh
    for digit in label['text']:
        glyph=spec['glyphs'][digit]
        assert len(glyph)==nh and len(set(map(len,glyph)))==1
        for y,row in enumerate(glyph):rows[y]+=('.'*label['gap'] if rows[y] else '')+row
    assert len(rows[0])<=nw and label['ink'] in raw
    left=(nw-len(rows[0]))//2
    return bytes(label['ink'] if c=='#' else 7 for row in rows for c in '.'*left+row+'.'*(nw-left-len(row)))

def symbol_resize(raw,w,h,nw,nh,transparent=7,outline=False):
    """Area-voted palette masks, optionally retaining a source black perimeter."""
    result=bytearray([transparent]*(nw*nh));area=w*h/(nw*nh)
    for y in range(nh):
        top,bottom=y*h/nh,(y+1)*h/nh
        for x in range(nw):
            left,right=x*w/nw,(x+1)*w/nw;hist=[0.0]*16
            for sy in range(math.floor(top),math.ceil(bottom)):
                wy=min(bottom,sy+1)-max(top,sy)
                for sx in range(math.floor(left),math.ceil(right)):
                    wx=min(right,sx+1)-max(left,sx)
                    hist[raw[min(h-1,sy)*w+min(w-1,sx)]]+=wx*wy
            if area-hist[transparent]>=area*.45:
                result[y*nw+x]=max((c for c in range(16) if c!=transparent),key=lambda c:hist[c])
    if outline:
        # Preserve an existing black perimeter without expanding the silhouette
        # or closing the gap between the legs of the original Prize letter.
        neighbours=((1,0),(-1,0),(0,1),(0,-1))
        for y in range(h):
            for x in range(w):
                if raw[y*w+x]!=transparent and any(not(0<=x+dx<w and 0<=y+dy<h) or raw[(y+dy)*w+x+dx]==transparent for dx,dy in neighbours):
                    assert raw[y*w+x]==0,'Source symbol has no complete black outline'
        mask=bytes(result)
        for y in range(nh):
            for x in range(nw):
                if mask[y*nw+x]!=transparent and any(not(0<=x+dx<nw and 0<=y+dy<nh) or mask[(y+dy)*nw+x+dx]==transparent for dx,dy in neighbours):
                    result[y*nw+x]=0
    assert set(result)<=set(raw)|{transparent}
    return bytes(result)

def outlined_resize(raw,w,h,nw,nh,transparent=2):
    samples=[];mask=[]
    area=w*h/(nw*nh)
    for y in range(nh):
        top,bottom=y*h/nh,(y+1)*h/nh
        for x in range(nw):
            left,right=x*w/nw,(x+1)*w/nw;hist=[0.0]*16
            for sy in range(math.floor(top),math.ceil(bottom)):
                wy=min(bottom,sy+1)-max(top,sy)
                for sx in range(math.floor(left),math.ceil(right)):
                    wx=min(right,sx+1)-max(left,sx)
                    hist[raw[min(h-1,sy)*w+min(w-1,sx)]]+=wx*wy
            ink=area-hist[transparent]
            samples.append(hist)
            mask.append(ink>=area*.30 or hist[0]>=area*.16)
    result=bytearray([transparent]*(nw*nh))
    for y in range(nh):
        for x in range(nw):
            p=y*nw+x
            if not mask[p]:continue
            hist=samples[p];ink=area-hist[transparent]
            edge=any(not(0<=x+dx<nw and 0<=y+dy<nh) or not mask[(y+dy)*nw+x+dx]
                     for dx,dy in ((-1,0),(1,0),(0,-1),(0,1)))
            if hist[0]>=area*.10 and edge:
                result[p]=0
            elif hist[0]>=ink*.26:
                result[p]=0
            else:
                result[p]=max((c for c in range(16) if c!=transparent),key=lambda c:hist[c])
    assert set(result)<=set(raw)|{transparent}
    return bytes(result)

if __name__=='__main__':
    from extract import OUT,EGA,png
    import json
    meta=json.loads((OUT/'sprites.json').read_text())
    canvas=bytearray([7]*(360*600))
    for row,id in enumerate((21,22,48,49,50,51)):
        s=meta[id];w,h=s['width'],s['height'];raw=(OUT/f'sprite-{id:02}.bin').read_bytes()
        nw,nh=round(w*35/96),round(h/2)
        nearest=bytes(raw[y*h//nh*w+x*w//nw] for y in range(nh) for x in range(nw))
        new=outlined_resize(raw,w,h,nw,nh)
        for col,data in enumerate((nearest,new)):
            for y in range(nh):
                for x in range(nw):
                    color=data[y*nw+x]
                    if color==2:continue
                    for dy in range(2):
                        for dx in range(2):canvas[(row*100+y*2+dy)*360+col*180+35+x*2+dx]=color
    png(OUT/'outline-comparison.png',360,600,canvas,EGA)
