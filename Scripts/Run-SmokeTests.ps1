[CmdletBinding()]
param(
    [string]$EngineRoot = 'C:\Program Files\Epic Games\UE_5.9',

    [ValidatePattern('^[A-Za-z0-9_.]+$')]
    [string]$TestFilter = 'FighterPrototype.Smoke',

    [ValidateRange(1, 3600)]
    [int]$TimeoutSeconds = 300
)

$ErrorActionPreference = 'Stop'
$projectRoot = Split-Path -Parent $PSScriptRoot
$project = Get-Item -LiteralPath (Join-Path $projectRoot 'FighterPrototype.uproject')
$editor = Get-Item -LiteralPath (Join-Path $EngineRoot 'Engine\Binaries\Win64\UnrealEditor-Cmd.exe')

$runName = '{0}-{1}' -f (Get-Date -Format 'yyyyMMdd-HHmmss'), ([guid]::NewGuid().ToString('N').Substring(0, 8))
$runDirectory = New-Item -ItemType Directory -Path (Join-Path $projectRoot "Saved\Automation\FighterPrototype\$runName") -Force
$logFile = Join-Path $runDirectory.FullName 'Unreal.log'
$reportFile = Join-Path $runDirectory.FullName 'index.json'
$arguments = @(
    ('"{0}"' -f $project.FullName)
    ('-ExecCmds="Automation RunTests {0}"' -f $TestFilter)
    '-TestExit="Automation Test Queue Empty"'
    '-Unattended', '-NullRHI', '-NoSound', '-NoSplash', '-NoP4'
    ('-ReportExportPath="{0}"' -f $runDirectory.FullName)
    ('-abslog="{0}"' -f $logFile)
)

Write-Host ('"{0}" {1}' -f $editor.FullName, ($arguments -join ' '))
$testProcess = Start-Process -FilePath $editor.FullName -ArgumentList $arguments -WorkingDirectory $projectRoot -WindowStyle Hidden -PassThru
try {
    if (!$testProcess.WaitForExit($TimeoutSeconds * 1000)) {
        $testProcess.Kill()
        $testProcess.WaitForExit()
        throw "Unreal automation timed out after $TimeoutSeconds seconds. Log: $logFile"
    }

    if ($testProcess.ExitCode -ne 0) {
        throw "Unreal automation exited with code $($testProcess.ExitCode). Log: $logFile"
    }
}
finally {
    $testProcess.Dispose()
}

if (!(Test-Path -LiteralPath $reportFile -PathType Leaf)) {
    throw "Unreal did not produce a test report for '$TestFilter'. Log: $logFile"
}

$report = Get-Content -Raw -LiteralPath $reportFile | ConvertFrom-Json
$passed = [int]$report.succeeded + [int]$report.succeededWithWarnings
Write-Host ("Passed: {0} ({1} with warnings). Failed: {2}. Not run: {3}. In process: {4}." -f `
    $passed, $report.succeededWithWarnings, $report.failed, $report.notRun, $report.inProcess)
Write-Host "Report: $reportFile"
if ($passed -lt 1 -or $report.failed -ne 0 -or $report.notRun -ne 0 -or $report.inProcess -ne 0) {
    throw "Automation did not finish with a passing set of tests. See $reportFile and $logFile."
}
