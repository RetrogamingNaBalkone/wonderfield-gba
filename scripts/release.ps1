param(
 [string]$ZigExe="$env:LOCALAPPDATA/Programs/Zig/0.13.0/zig.exe",
 [string]$PythonExe='C:/Users/dspev/AppData/Local/Python/bin/python.exe'
)
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
Push-Location $taskRoot
$taskBytecode=$env:PYTHONDONTWRITEBYTECODE
try {
 $env:PYTHONDONTWRITEBYTECODE='1'
 & "$PSScriptRoot/build.ps1" -ZigExe $ZigExe -PythonExe $PythonExe
 & $PythonExe scripts/verify.py
 if($LASTEXITCODE) {throw 'mGBA verification failed'}
 & $PythonExe scripts/verify_scene.py
 if($LASTEXITCODE) {throw 'mGBA visual verification failed'}
 & $PythonExe scripts/verify_events.py
 if($LASTEXITCODE) {throw 'mGBA event verification failed'}
 & $PythonExe scripts/verify_flows.py
 if($LASTEXITCODE) {throw 'mGBA final, bonus and input verification failed'}
 & $PythonExe scripts/verify_stage.py
 if($LASTEXITCODE) {throw 'mGBA stage, spin and RNG audit failed'}
 & $PythonExe scripts/contact.py
 if($LASTEXITCODE) {throw 'Resource contact sheet failed'}
 New-Item -ItemType Directory -Force -Path dist,docs/media,docs/reports | Out-Null
 Copy-Item -LiteralPath build/gba/pole.gba -Destination dist/pole.gba
 Copy-Item -LiteralPath build/qa/report.json -Destination docs/reports/verification.json
 Copy-Item -LiteralPath build/qa/layout-fixed.png -Destination docs/media/gameplay.png
 Copy-Item -LiteralPath build/qa/keyboard.png -Destination docs/media/keyboard.png
 Copy-Item -LiteralPath build/qa/speaker-demo.wav -Destination docs/media/speaker-demo.wav
 Copy-Item -LiteralPath build/qa/visual-report.json -Destination docs/reports/visual-verification.json
 Copy-Item -LiteralPath build/qa/events-report.json -Destination docs/reports/events-verification.json
 Copy-Item -LiteralPath build/qa/flows-report.json -Destination docs/reports/flows-verification.json
 Copy-Item -LiteralPath build/qa/stage-report.json -Destination docs/reports/stage-verification.json
 Copy-Item -LiteralPath build/qa/assistant-left-wall.png -Destination docs/media/assistant-entry.png
 Copy-Item -LiteralPath build/qa/assistant-right-wall.png -Destination docs/media/assistant-exit.png
 Copy-Item -LiteralPath build/qa/turn-counter-2.png -Destination docs/media/turn-2.png
 Copy-Item -LiteralPath analysis/dos-spin-timing.json -Destination docs/reports/dos-spin-timing.json
 Copy-Item -LiteralPath build/qa/finale-page-1.png -Destination docs/media/finale-1.png
 Copy-Item -LiteralPath build/qa/finale-page-2.png -Destination docs/media/finale-2.png
 Copy-Item -LiteralPath build/qa/finale-page-3.png -Destination docs/media/finale-3.png
 Copy-Item -LiteralPath build/qa/prize-gift-text.png -Destination docs/media/prize-gift.png
 Copy-Item -LiteralPath build/qa/three-letters-chests.png -Destination docs/media/chests.png
 Copy-Item -LiteralPath build/qa/ai-answer-0.png -Destination docs/media/ai-answer.png
 Copy-Item -LiteralPath build/qa/ai-score-1.png -Destination docs/media/ai-score.png
 Copy-Item -LiteralPath build/qa/assistant-opens-letter.png -Destination docs/media/assistant.png
 Copy-Item -LiteralPath build/qa/assistant-opens-plus.png -Destination docs/media/assistant-plus.png
 Copy-Item -LiteralPath build/qa/assistant-waiting-ordinary.png -Destination docs/media/assistant-waiting.png
 Copy-Item -LiteralPath build/qa/prize-choice.png -Destination docs/media/prize.png
 Copy-Item -LiteralPath build/qa/prize-outline.png -Destination docs/media/prize-outline.png
 Copy-Item -LiteralPath build/qa/round-last-letter.png -Destination docs/media/round-last-letter.png
 Copy-Item -LiteralPath build/qa/round-winner.png -Destination docs/media/round-winner.png
 Copy-Item -LiteralPath build/qa/farewell.png -Destination docs/media/farewell.png
 Copy-Item -LiteralPath build/qa/studio-demo.gif -Destination docs/media/studio-demo.gif
 Copy-Item -LiteralPath build/qa/speech.png -Destination docs/media/speech.png
 Copy-Item -LiteralPath build/qa/layout-preview.png -Destination docs/media/layout-preview.png
 Copy-Item -LiteralPath build/qa/title-preview.png -Destination docs/media/title.png
 Copy-Item -LiteralPath build/qa/score-spacing.png -Destination docs/media/score-spacing.png
 Copy-Item -LiteralPath build/qa/short-i.png -Destination docs/media/short-i.png
 Copy-Item -LiteralPath assets/generated/blue-stone-extension.png -Destination docs/media/stone-texture.png
 Copy-Item -LiteralPath assets/generated/blue-stone-extension.prompt.txt -Destination docs/media/stone-texture.prompt.txt
 & $PythonExe scripts/package_release.py
 if($LASTEXITCODE) {throw 'Release packaging failed'}
 Write-Output "Release: dist/pole.gba; archive: build/release/pole-gba.zip"
} finally {$env:PYTHONDONTWRITEBYTECODE=$taskBytecode; Pop-Location}
