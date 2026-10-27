[CmdletBinding(SupportsShouldProcess)]
param()

$ErrorActionPreference='Stop'
$taskRoot=[IO.Path]::GetFullPath((Split-Path $PSScriptRoot -Parent))
$taskRemovedBytes=0L

function Remove-ProjectArtifact([string]$RelativePath) {
 $taskTarget=[IO.Path]::GetFullPath((Join-Path $taskRoot $RelativePath))
 if(-not $taskTarget.StartsWith($taskRoot+[IO.Path]::DirectorySeparatorChar,[StringComparison]::OrdinalIgnoreCase)) {
  throw "Cleanup target is outside the project: $taskTarget"
 }
 if(-not (Test-Path -LiteralPath $taskTarget)) {return}
 $taskItem=Get-Item -LiteralPath $taskTarget -Force
 if($taskItem.Attributes -band [IO.FileAttributes]::ReparsePoint) {throw "Refusing to clean a link: $taskTarget"}
 $taskContents=@($taskItem)
 if($taskItem.PSIsContainer) {$taskContents+=@(Get-ChildItem -LiteralPath $taskTarget -Recurse -Force)}
 if($taskContents | Where-Object { $_.Attributes -band [IO.FileAttributes]::ReparsePoint }) {
  throw "Refusing to clean a directory containing links: $taskTarget"
 }
 $taskBytes=($taskContents | Where-Object {-not $_.PSIsContainer} | Measure-Object Length -Sum).Sum
 if($PSCmdlet.ShouldProcess($taskTarget,'Remove generated files')) {
  Remove-Item -LiteralPath $taskTarget -Recurse -Force
  $script:taskRemovedBytes+=$taskBytes
 }
}

# Keep release files, original resources, analysis exports and DOS reference captures.
foreach($taskRelative in @(
 'build/gba','build/generated','build/qa','build/v1','build/release',
 'build/zig-cache','zig-cache','.zig-cache','zig-out',
 'build/ghidra','build/ghidra-home','build/ghidra-local','build/ghidra-settings',
 'build/reference/game','build/reference/dosbox.conf','build/reference/pid.txt',
 'build/reference/stdout.log','build/reference/stderr.log',
 'build/reference/plane0.png',
 'build/reference/spin-timing/5000','build/reference/spin-timing/20000',
 'scripts/__pycache__','analysis/ghidra.log','dist/pole-gba.zip.tmp'
)) {Remove-ProjectArtifact $taskRelative}
# Remove isolated sessions left behind by a forcibly interrupted process.
foreach($taskParent in @('build','build/reference')) {
 $taskParentPath=Join-Path $taskRoot $taskParent
 if(Test-Path -LiteralPath $taskParentPath) {
  if((Get-Item -LiteralPath $taskParentPath -Force).Attributes -band [IO.FileAttributes]::ReparsePoint) {
   throw "Refusing to clean through a link: $taskParentPath"
  }
  Get-ChildItem -LiteralPath $taskParentPath -Directory -Force | Where-Object {
   $_.Name -match '^(ghidra-session-[0-9a-f]{32}|dosbox-[a-z0-9_]+)$'
  } | ForEach-Object {Remove-ProjectArtifact (Join-Path $taskParent $_.Name)}
 }
}
Write-Output ('Removed {0:N2} MiB of generated files.' -f ($taskRemovedBytes/1MB))
