"""Package the verified build without reopening a ROM held by an emulator."""
from pathlib import Path
import hashlib, json, zipfile

root=Path(__file__).resolve().parents[1]
release=root/'build/release'
release.mkdir(parents=True,exist_ok=True)
rom=(root/'build/gba/pole.gba').read_bytes()
digest=hashlib.sha256(rom).hexdigest()
rom_name='pole 1.1.gba'
archive_name='pole-gba-1.1.zip'
names=['records-verification.json','performance-verification.json','performance-audit-profile.json','v11-verification.json','dos-cash-timing.json','cash-dos-reference.png','title-v11.png','turn-menu-v11.png','turn-menu-solve-v11.png','solve-fixed-v11.png','wheel-native-v11.png','wheel-phases-v11.png','cash-screen-v11.png','cash-filled-v11.png','cash-natural-v11.png','cash-v11.gif','cash-v11.wav','verification.json','visual-verification.json',
       'events-verification.json','flows-verification.json','stage-verification.json','assistant-entry.png','assistant-exit.png','turn-2.png','dos-spin-timing.json','finale-1.png','finale-2.png','finale-3.png','prize-gift.png','chests.png','gameplay.png','layout-preview.png',
       'title.png','title-clean.png','score-spacing.png','short-i.png','keyboard.png','speech.png','assistant.png','assistant-plus.png','assistant-waiting.png',
       'ai-answer.png','ai-score.png','prize.png','prize-outline.png','round-last-letter.png','round-winner.png','farewell.png','studio-demo.gif',
       'speaker-demo.wav','stone-texture.png','stone-texture.prompt.txt']
for name in ('verification.json','visual-verification.json','events-verification.json','flows-verification.json','stage-verification.json','v11-verification.json','performance-verification.json','records-verification.json'):
    report=json.loads((root/'docs/reports'/name).read_text(encoding='utf-8'))
    assert report['status']=='passed' and report['rom_sha256']==digest,name
temporary=release/(archive_name+'.tmp')
try:
    with zipfile.ZipFile(temporary,'w',zipfile.ZIP_DEFLATED) as archive:
        archive.writestr(rom_name,rom)
        archive.write(root/'docs/play.txt','README.txt')
        archive.writestr('SHA256SUMS',f'{digest}  {rom_name}\n')
        for name in names:
            directory='reports' if name.endswith('.json') else 'media'
            archive.write(root/'docs'/directory/name,name)
    with zipfile.ZipFile(temporary) as archive:
        assert archive.testzip() is None
        assert hashlib.sha256(archive.read(rom_name)).hexdigest()==digest
    temporary.replace(release/archive_name)
finally:
    temporary.unlink(missing_ok=True)
print(f'Archive verified: {len(names)+3} files, ROM {digest}')
