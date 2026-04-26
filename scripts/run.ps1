#Requires -Version 5.1
<#
  Build (optional) and run the app.
  Usage:
    .\scripts\run.ps1
    .\scripts\run.ps1 -SkipBuild
    .\scripts\run.ps1 -Config Debug
#>
param(
  [ValidateSet("Debug", "Release", "RelWithDebInfo", "MinSizeRel")]
  [string]$Config = "Release",
  [string]$BuildDir = "build",
  [switch]$SkipBuild
)

$ErrorActionPreference = "Stop"
$Root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
$absBuild = Join-Path $Root $BuildDir
$exeName = "tho3ban++"

function Find-BuiltExecutable {
  param([string]$Name, [string]$BuildRoot, [string]$Cfg)
  $candidates = @(
    (Join-Path $BuildRoot "$Cfg\$Name.exe"),
    (Join-Path $BuildRoot "bin\$Cfg\$Name.exe"),
    (Join-Path $BuildRoot "bin\$Name.exe"),
    (Join-Path $BuildRoot "console\$Cfg\$Name.exe"),
    (Join-Path $BuildRoot "$Name.exe"),
    (Join-Path $BuildRoot "$Cfg\$Name"),
    (Join-Path $BuildRoot "bin\$Cfg\$Name"),
    (Join-Path $BuildRoot "$Name")
  )
  foreach ($p in $candidates) {
    if (Test-Path -LiteralPath $p) { return (Resolve-Path -LiteralPath $p).Path }
  }
  return $null
}

if (-not $SkipBuild) {
  $buildScript = Join-Path $Root "scripts\build.ps1"
  if (Test-Path -LiteralPath $buildScript) {
    & $buildScript -Config $Config -BuildDir $BuildDir
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
  }
  else {
    $configureArgs = @("-B", $absBuild, "-S", $Root)
    & cmake @configureArgs
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

    $buildArgs = @("--build", $absBuild, "--parallel")
    if ($Config) { $buildArgs += @("--config", $Config) }
    & cmake @buildArgs
    if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
  }
}

$exe = Find-BuiltExecutable -Name $exeName -BuildRoot $absBuild -Cfg $Config
if (-not $exe) {
  Write-Error "Could not find $exeName under $absBuild. Try a different -Config or build once from your IDE."
  exit 1
}

Write-Host "Running: $exe"
& $exe @args
exit $LASTEXITCODE
