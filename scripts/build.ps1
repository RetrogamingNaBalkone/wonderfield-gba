param(
 [string]$ZigExe="$env:LOCALAPPDATA/Programs/Zig/0.13.0/zig.exe",
 [string]$PythonExe='C:/Users/dspev/AppData/Local/Python/bin/python.exe'
)
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
Push-Location $taskRoot
$taskCache=$env:ZIG_GLOBAL_CACHE_DIR
$taskBytecode=$env:PYTHONDONTWRITEBYTECODE
try {
 $env:PYTHONDONTWRITEBYTECODE='1'
 $env:ZIG_GLOBAL_CACHE_DIR="$taskRoot/build/zig-cache"
 New-Item -ItemType Directory -Force build/gba | Out-Null
 & $PythonExe scripts/extract.py
 if($LASTEXITCODE) {throw 'Extraction failed'}
 & $PythonExe scripts/pack.py
 if($LASTEXITCODE) {throw 'Asset pack failed'}
 $taskFlags=@('cc','-target','thumb-freestanding-eabi','-mcpu=arm7tdmi','-std=c11','-O2','-g','-Wall','-Wextra','-Werror','-ffreestanding','-fno-stack-protector','-fno-unwind-tables','-fno-asynchronous-unwind-tables','-fno-pic','-I','build/generated','-I','gba','-c')
 & $ZigExe @taskFlags build/generated/main.c -o build/gba/main.o
 if($LASTEXITCODE) {throw 'Game compilation failed'}
 & $ZigExe @taskFlags build/generated/assets.c -o build/gba/assets.o
 if($LASTEXITCODE) {throw 'Assets compilation failed'}
 & $ZigExe @taskFlags gba/runtime.c -o build/gba/runtime.o
 if($LASTEXITCODE) {throw 'Runtime compilation failed'}
 & $ZigExe @taskFlags gba/speaker.c -o build/gba/speaker.o
 if($LASTEXITCODE) {throw 'Speaker compilation failed'}
 & $ZigExe cc -target arm-freestanding-eabi -mcpu=arm7tdmi -c gba/startup.S -o build/gba/startup.o
 if($LASTEXITCODE) {throw 'Startup compilation failed'}
 & $ZigExe cc -target arm-freestanding-eabi -mcpu=arm7tdmi -c gba/division.S -o build/gba/division.o
 if($LASTEXITCODE) {throw 'Division compilation failed'}
 & $ZigExe ld.lld -T gba/pole.ld --gc-sections '-Map=build/gba/pole.map' build/gba/startup.o build/gba/main.o build/gba/assets.o build/gba/runtime.o build/gba/division.o build/gba/speaker.o -o build/gba/pole.elf
 if($LASTEXITCODE) {throw 'Link failed'}
 & $PythonExe scripts/finish_rom.py
 if($LASTEXITCODE) {throw 'ROM validation failed'}
} finally {$env:ZIG_GLOBAL_CACHE_DIR=$taskCache; $env:PYTHONDONTWRITEBYTECODE=$taskBytecode; Pop-Location}
