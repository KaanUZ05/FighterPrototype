# Task reports

Each task result uses `reports/TASK_###_RESULT.md`. Copy the [report template](TASK_REPORT_TEMPLATE.md) and fill it with observed results. Update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` after the checks finish.

## Run the UE 5.9 smoke tests

From the project root in PowerShell, close the editor before building the Development Editor target. Supply `-EngineRoot` to the script if UE 5.9 is installed elsewhere.

```powershell
$engine = 'C:\Program Files\Epic Games\UE_5.9'
$project = (Resolve-Path -LiteralPath .\FighterPrototype.uproject).Path
& "$engine\Engine\Build\BatchFiles\Build.bat" FighterPrototypeEditor Win64 Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE
# Run after the build succeeds.
powershell -NoProfile -ExecutionPolicy Bypass -File .\Scripts\Run-SmokeTests.ps1 -EngineRoot $engine
```

The runner prints the Unreal command and writes `Unreal.log` and `index.json` to a new directory under `Saved/Automation/FighterPrototype/`. It fails on an engine error, a timeout, a missing report, or a report without a completed passing test set. Use `-TestFilter FighterPrototype.Smoke.ThirdPersonBaseline` to run just the baseline check. The headless test covers the map and class wiring. Record interactive PIE separately.

## Keep evidence reviewable

Keep full build and engine logs in ignored `Saved/` directories. Reference their paths in the report and quote the relevant result lines. Put short, shareable screenshots and excerpts under `reports/evidence/`, prefixed with the task ID. Check each published artifact for local credentials and unrelated personal data.
