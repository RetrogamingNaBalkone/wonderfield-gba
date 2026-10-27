param([Parameter(Mandatory=$true)][string]$SourceImage)
$ErrorActionPreference='Stop'
$taskRoot=Split-Path $PSScriptRoot -Parent
$taskOut=Join-Path $taskRoot 'assets/generated'
New-Item -ItemType Directory -Force $taskOut | Out-Null
Copy-Item -LiteralPath $SourceImage -Destination (Join-Path $taskOut 'blue-stone-extension-source.png')
Add-Type -AssemblyName System.Drawing
$taskImage=[Drawing.Image]::FromFile((Join-Path $taskOut 'blue-stone-extension-source.png'))
try {
 $taskPixels=New-Object byte[] (192*64)
 $taskPalette=@(@(0,0,0,0),@(0,0,170,1),@(85,85,255,9),@(170,170,170,7))
 for($taskY=0;$taskY -lt 64;$taskY++) {
  for($taskX=0;$taskX -lt 192;$taskX++) {
   $taskSampleX=[Math]::Min($taskImage.Width-1,[int][Math]::Floor(($taskX+0.5)*$taskImage.Width/192))
   $taskSampleY=[Math]::Min($taskImage.Height-1,[int][Math]::Floor(($taskY+0.5)*$taskImage.Height/64))
   $taskColor=$taskImage.GetPixel($taskSampleX,$taskSampleY)
   $taskBestDistance=[double]::PositiveInfinity;$taskBestIndex=1
   foreach($taskEntry in $taskPalette) {
    $taskDistance=[Math]::Pow($taskColor.R-$taskEntry[0],2)+[Math]::Pow($taskColor.G-$taskEntry[1],2)+[Math]::Pow($taskColor.B-$taskEntry[2],2)
    if($taskDistance -lt $taskBestDistance) {$taskBestDistance=$taskDistance;$taskBestIndex=$taskEntry[3]}
   }
   $taskPixels[$taskY*192+$taskX]=[byte]$taskBestIndex
  }
 }
 [IO.File]::WriteAllBytes((Join-Path $taskOut 'blue-stone-extension.bin'),$taskPixels)
} finally {$taskImage.Dispose()}
