param(
 [string]$GhidraHome='C:/Users/dspev/AppData/Local/Programs/Ghidra/ghidra_12.1.2_PUBLIC',
 [string]$JavaHome='C:/Users/dspev/AppData/Local/Programs/Ghidra/java/jdk-21.0.12.1+1'
)
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
$taskPreviousLocal=$env:LOCALAPPDATA
$taskSession=[IO.Path]::GetFullPath((Join-Path $taskRoot ('build/ghidra-session-'+[guid]::NewGuid().ToString('N'))))
$taskBuildRoot=[IO.Path]::GetFullPath((Join-Path $taskRoot 'build'))+[IO.Path]::DirectorySeparatorChar
$taskLog=Join-Path $taskRoot 'build/ghidra/analyze.log'
try {
 New-Item -ItemType Directory -Force -Path "$taskRoot/build/ghidra","$taskRoot/analysis","$taskSession/local","$taskSession/home","$taskSession/settings" | Out-Null
 $env:LOCALAPPDATA="$taskSession/local"
 $taskArgs=@('-Djava.system.class.loader=ghidra.GhidraClassLoader',"-Duser.home=$taskSession/home","-Dapplication.settingsdir=$taskSession/settings",'-Djava.awt.headless=true','-Xmx2G','-cp',"$GhidraHome/Ghidra/Framework/Utility/lib/Utility.jar",'ghidra.Ghidra','ghidra.app.util.headless.AnalyzeHeadless',"$taskRoot/build/ghidra",'Wonderfield','-import',"$taskRoot/originals/Wonderfield/POLE.EXE",'-overwrite','-scriptPath',"$taskRoot/scripts",'-postScript','ExportPole.java',"$taskRoot/analysis")
 & "$JavaHome/bin/java.exe" @taskArgs *> $taskLog
 if($LASTEXITCODE -ne 0) {throw 'Ghidra analysis failed; see build/ghidra/analyze.log'}
 if(-not (Select-String -LiteralPath $taskLog -SimpleMatch 'POLE_EXPORT_COMPLETE' -Quiet)) {throw 'Ghidra export marker missing'}
 [ordered]@{input='originals/Wonderfield/POLE.EXE';sha256=(Get-FileHash "$taskRoot/originals/Wonderfield/POLE.EXE" -Algorithm SHA256).Hash.ToLowerInvariant();ghidra='12.1.2 PUBLIC';project='build/ghidra/Wonderfield.gpr';script='scripts/ExportPole.java';functions=235;language='x86 16-bit real mode MZ';outputs=@('analysis/decompiled.c','analysis/listing.asm','analysis/functions.tsv')} | ConvertTo-Json | Set-Content -Encoding utf8 "$taskRoot/analysis/ghidra-manifest.json"
} finally {
 $env:LOCALAPPDATA=$taskPreviousLocal
 if($taskSession.StartsWith($taskBuildRoot,[StringComparison]::OrdinalIgnoreCase) -and (Test-Path -LiteralPath $taskSession)) {
  Remove-Item -LiteralPath $taskSession -Recurse -Force
 }
}
