"""Profile settled PPU frames and actual draw calls in deterministic mGBA states.

Fixtures change only emulated RAM. On old ROMs, scene.last_redraw changes
(and main iterations in Gallery) provide the original scheduling counter.
"""
import ctypes as c
import hashlib
import json
import struct
import zlib
from emulator import Emulator,ROOT


def profile(rom_path=None,elf_path=None,destination=None):
    em=Emulator(rom_path,elf_path)
    loaded_rom=c.string_at(em.info.data,em.info.size)
    digest=hashlib.sha256(loaded_rom).hexdigest()

    def read(name,offset=0):
        return struct.unpack('<I',c.string_at(em.ram+em.sym[name]-0x02000000+offset,4))[0]

    def write(name,value,offset=0):
        c.memmove(em.ram+em.sym[name]-0x02000000+offset,struct.pack('<I',value&0xffffffff),4)

    def fixture(mode):
        for i in range(20):em.poke(18+i,0)
        for i in range(32):em.poke(38+i,0)
        for i,value in {3:mode,4:0,5:2,6:0,7:12,9:0,10:0,11:0,12:0,13:1,70:0,71:0,72:0,76:0,79:0,80:0,81:1,82:0,83:0,84:0}.items():em.poke(i,value)
        c.memmove(em.ramgame+352,bytes(21),21)
        write('message1',0);write('scene',0,168);write('scene',1,180);write('scene',0,184)
        write('dirty',1)

    def sample(name):
        em.run(240)
        initial=em.state()[1]
        previous=read('scene',8)
        scheduled=0
        hashes=set()
        title_hashes=set()
        irqs=read('speaker_diag');samples=read('speaker_diag',4)
        draws=read('rendered_frames') if 'rendered_frames' in em.sym else None
        silent=read('speaker_silent_buffers') if 'speaker_silent_buffers' in em.sym else 0
        for _ in range(300):
            em.run(1)
            current=read('scene',8)
            scheduled+=current!=previous;previous=current
            hashes.add(zlib.crc32(em.raw))
            if name=='title-settled':
                # The version caption was intentionally made smaller;
                # compare all remaining title pixels against the old ROM.
                masked=bytearray(em.raw);size=4 if em.format==1 else 2
                for y in range(120,134):masked[(y*240+206)*size:(y*240+234)*size]=bytes(28*size)
                title_hashes.add(zlib.crc32(masked))
        main_updates=em.state()[1]-initial
        redraws=read('rendered_frames')-draws if draws is not None else main_updates if em.state()[3]==13 else scheduled
        result=dict(name=name,mode=em.state()[3],vblanks=300,main_updates=main_updates,
                    scheduled_redraws=scheduled,rendered_frames=redraws,
                    draw_counter='rendered_frames' if draws is not None else 'legacy scheduling',
                    unique_ppu_frames=len(hashes),ppu_crc32=sorted(hashes),
                    title_without_version_crc32=sorted(title_hashes),
                    audio_irqs=read('speaker_diag')-irqs,
                    audio_samples=read('speaker_diag',4)-samples,
                    fast_silent_buffers=read('speaker_silent_buffers')-silent if 'speaker_silent_buffers' in em.sym else 0)
        print(json.dumps(result),flush=True);em.audio=[]
        return result

    try:
        em.run(300);results=[sample('title-settled')]
        fixture(1);write('scene',0,4);results.append(sample('human-turn-settled'))
        em.tap(10);results.append(sample('human-turn-muted'))
        em.tap(6);em.tap(8);results.append(sample('solve-keyboard-idle'))
        for mode,name in ((14,'name-keyboard-idle'),(19,'gift-page-idle'),(13,'gallery-idle')):
            fixture(mode);results.append(sample(name))
        # Use real transitions: old ROMs can cache dirty in a register, so
        # a RAM-only mode/dirty fixture cannot force these static screens.
        em.tap(0);em.tap(2);results.append(sample('help-idle'))
        em.tap(0);em.tap(10);results.append(sample('records-idle'))
        fixture(17);write('scene',read('video_ticks'),12);results.append(sample('credits-settled'))
        fixture(7);em.poke(81,0);em.poke(82,1);em.poke(83,1000000);em.tap(8);em.tap(8)
        em.until(lambda state:read('cash')==read('cash',4));results.append(sample('cash-completed'))
        report=dict(rom_sha256=digest,rom_bytes=len(loaded_rom),hash_source='retro_load_game input buffer',
                    fps=em.fps,warmup_vblanks=240,sample_vblanks=300,results=results)
        target=destination or ROOT/'build/qa/audit-idle-profile.json'
        target.parent.mkdir(parents=True,exist_ok=True);target.write_text(json.dumps(report,indent=2),encoding='utf-8')
        return report
    finally:em.close()


if __name__=='__main__':profile()
