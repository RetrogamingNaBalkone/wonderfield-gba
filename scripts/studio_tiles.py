"""Tile and object banks for the Mode 0 studio. Input pixels are DOS palette indices."""
import struct


def tiles(pixels, width, height, key):
    # XOR puts the transparent colour at hardware index zero. Each palette
    # bank undoes the same permutation, so opaque black survives compositing.
    out = bytearray()
    for y in range(0, height, 8):
        for x in range(0, width, 8):
            for row in range(y, y + 8):
                for col in range(x, x + 8, 2):
                    a, b = pixels[row * width + col:row * width + col + 2]
                    out.append(((a ^ key) | ((b ^ key) << 4)))
    return out


def emit_studio(arr, stage, wheel, half, extra, full):
    code = []
    maps = [[0] * 1024 for _ in range(4)]
    ground = bytearray(32)
    lookup = {}
    for y in range(20):
        for x in range(30):
            cell = y * 32 + x
            maps[0][cell] = 13 << 12 | (1 + y * 30 + x)
            if y >= 7:
                maps[2][cell] = 13 << 12 | (97 + (y - 7) * 30 + x)
            if y < 6:
                tile = 64 + y * 30 + x
            else:
                source = b''.join(stage[(y*8+i)*240+x*8:][:8] for i in range(8))
                if source not in lookup:
                    lookup[source] = len(ground) // 32
                    ground.extend(tiles(source, 8, 8, 13))
                tile = lookup[source]
            maps[3][cell] = 13 << 12 | tile
    assert len(ground) <= 64 * 32 and 13 not in stage
    code.append(arr('studio_ground', ground))
    board = bytearray(stage[:48*240])
    for y in range(2,44):
        for x in range(30,211):
            grid = y<=34 and ((x-30)%9==0 or y in (2,10,26,34))
            board[y*240+x] = 0 if grid else 8 if y==43 else 7
    code.append(arr('studio_board_base', tiles(board,240,48,13)))
    # Fixed badges and banknotes are stamped at arbitrary pixel offsets.
    for name,idx,transparent in [('badge',28,7),('note',56,2)]:
        w,h,data=half[idx]
        pairs=[]
        for y in range(h):
            for x in range(0,w,8):
                mask=value=0
                for bit in range(min(8,w-x)):
                    color=data[y*w+x+bit]
                    if color!=transparent:
                        mask |= 15 << (4*bit)
                        value |= (color^13) << (4*bit)
                pairs.extend([mask,value])
        code.append(f'const unsigned int studio_{name}[]={{'+','.join(map(str,pairs))+'};\n')
    w,h,data=full[39]
    edges=[[],[]]
    for y in range(h):
        xs=[x for x in range(98) if data[y*w+x*w//98]!=2]
        edges[0].append(min(xs,default=98))
        edges[1].append(max(xs,default=-1))
    for name,edge in zip(('left','right'),edges):
        code.append(f'const int speech_{name}[]={{'+','.join(map(str,edge))+'};\n')

    masks = [sum(15 << (col*4) for col in range(8) if bits & (128 >> col))
             for bits in range(256)]
    code.append('const unsigned int studio_font_mask[256]={'+','.join(map(str,masks))+'};\n')
    for y in range(14):
        for x in range(16):
            maps[1][y*32+x] = 13 << 12 | (256 + y*16 + x)
    code.append(arr('studio_maps', b''.join(struct.pack('<1024H', *m) for m in maps)))

    frames, shifted = bytearray(), bytearray()
    for phase in range(32):
        pixels = bytearray(wheel[phase*14336:(phase+1)*14336])
        assert 13 not in pixels
        frames.extend(tiles(pixels, 128, 112, 13))
        for y in range(13):
            for x in range(128):
                if pixels[y*128+x] == stage[(43+y)*240+32+x]:
                    pixels[y*128+x] = stage[(44+y)*240+28+x]
        shifted.extend(tiles(pixels, 128, 16, 13))
    code += [arr('studio_wheel', frames), arr('studio_wheel_shifted', shifted)]

    atlas = bytearray()
    for name, source, selection in [
        ('half', half, {**dict.fromkeys([21,22,23,24,25,26,48,49,50,51,53,54,55],2),
                        **dict.fromkeys([27,42,43,44,45],None)}),
        ('extra', extra, dict.fromkeys(range(len(extra)), 2)),
        ('full', full, dict.fromkeys([36,37,38], 7)),
    ]:
        entries = []
        for idx, key in selection.items():
            w, h, data = source[idx]
            if key is None:
                key = next(i for i in range(16) if i not in data)
            first = len(atlas) // 32
            # 16x16 objects give the 55x76 host a bounded scanline cost
            # and leave room for all portraits and all animation cels in OBJ VRAM.
            for y in range(0, h, 16):
                for x in range(0, w, 16):
                    piece = bytes(data[yy*w+xx] if xx<w and yy<h else key
                                  for yy in range(y,y+16) for xx in range(x,x+16))
                    atlas.extend(tiles(piece, 16, 16, key))
            entries.append(f'[{idx}]={{{first},{(w+15)//16},{(h+15)//16},{key}}}')
        code.append(f'const StudioObject obj_{name}[{len(source)}]={{'+','.join(entries)+'};\n')
    # The mute indicator stays fixed while the credits BG scrolls.
    icon = bytearray([13] * 256)
    def rect(x, y, w, h, color):
        for yy in range(y, y+h):
            icon[yy*16+x:yy*16+x+w] = bytes([color])*w
    rect(1,1,14,12,8)
    rect(2,5,3,4,15)
    for i in range(4):
        rect(5+i,5-i,1,4+i*2,15)
    for i in range(10):
        rect(12-i,2+i,3,1,8)
        rect(13-i,2+i,1,1,15)
    atlas.extend(tiles(icon,16,16,13))
    assert len(atlas) <= 32768
    code.append(arr('studio_atlas', atlas))
    return ''.join(code), len(ground), len(atlas)


def cash_backdrop(arr, pixels):
    # On entry the canvas has no notes. Only 206 distinct tiles are needed
    # while the foreground speech and footer are being installed.
    data=tiles(pixels,240,160,13)
    entries,bank,screen={},bytearray(),[0]*1024
    for i in range(600):
        tile=bytes(data[i*32:(i+1)*32])
        if tile not in entries:
            entries[tile]=len(bank)//32+1
            bank.extend(tile)
        screen[i//30*32+i%30]=(13<<12)|entries[tile]
    return arr('cash_ground',bank)+arr('cash_map',struct.pack('<1024H',*screen)),len(bank)


def keyboard_tiles(arr, font):
    """The same unselected key caps on a transparent or opaque black page."""
    code = []
    for name, backdrop in [('stage',13),('solve',0)]:
        pixels = bytearray([backdrop] * (240*72))
        for y in range(84,150):
            for x in range(3,237):
                pixels[(y-80)*240+x] = 0 if x in (3,236) or y in (84,149) else 1
        for i in range(32):
            left, top = 8+(i%8)*28, 6+(i//8)*16
            for y in range(15):
                for x in range(26):
                    color = 0 if x in (0,25) or y in (0,14) else 11
                    if 9<=x<17 and y>=1 and font[(128+i)*14+y-1] & (128>>(x-9)):
                        color = 0
                    pixels[(top+y)*240+left+x] = color
        code.append(arr('keyboard_'+name, tiles(pixels,240,72,13)))
    return ''.join(code)


def credits_tiles(lines, font14, font8):
    pixels = bytearray([1] * (240*160))
    def centered(y, text, h, font):
        left = (240-len(text)*8)//2
        for i,ch in enumerate(text):
            for row in range(h):
                bits = font[ch*h+row]
                for bit in range(8):
                    x = left+i*8+bit
                    if 0<=x<240 and bits & (128>>bit):
                        pixels[(y+row)*240+x] = 14
    for i,line in enumerate(lines):
        centered(4+i*14,line,14,font14)
    centered(151,'A: Следующий раунд'.encode('cp866'),8,font8)
    return tiles(pixels,240,160,13)
