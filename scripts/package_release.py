"""Package the verified build without reopening a ROM held by an emulator."""
from pathlib import Path
import hashlib, json, zipfile

root=Path(__file__).resolve().parents[1]
release=root/'build/release'
release.mkdir(parents=True,exist_ok=True)
rom=(root/'build/gba/pole.gba').read_bytes()
digest=hashlib.sha256(rom).hexdigest()
names=['verification.json','visual-verification.json',
       'events-verification.json','flows-verification.json','stage-verification.json','assistant-entry.png','assistant-exit.png','turn-2.png','dos-spin-timing.json','finale-1.png','finale-2.png','finale-3.png','prize-gift.png','chests.png','gameplay.png','layout-preview.png',
       'title.png','score-spacing.png','short-i.png','keyboard.png','speech.png','assistant.png','assistant-plus.png','assistant-waiting.png',
       'ai-answer.png','ai-score.png','prize.png','prize-outline.png','round-last-letter.png','round-winner.png','farewell.png','studio-demo.gif',
       'speaker-demo.wav','stone-texture.png','stone-texture.prompt.txt']
for name in ('verification.json','visual-verification.json','events-verification.json','flows-verification.json','stage-verification.json'):
    report=json.loads((root/'docs/reports'/name).read_text(encoding='utf-8'))
    assert report['status']=='passed' and report['rom_sha256']==digest,name
temporary=release/'pole-gba.zip.tmp'
try:
    with zipfile.ZipFile(temporary,'w',zipfile.ZIP_DEFLATED) as archive:
        archive.writestr('pole.gba',rom)
        archive.write(root/'docs/play.txt','README.txt')
        archive.writestr('SHA256SUMS',f'{digest}  pole.gba\n')
        for name in names:
            directory='reports' if name.endswith('.json') else 'media'
            archive.write(root/'docs'/directory/name,name)
    with zipfile.ZipFile(temporary) as archive:
        assert archive.testzip() is None
        assert hashlib.sha256(archive.read('pole.gba')).hexdigest()==digest
    temporary.replace(release/'pole-gba.zip')
finally:
    temporary.unlink(missing_ok=True)
print(f'Archive verified: {len(names)+3} files, ROM {digest}')
