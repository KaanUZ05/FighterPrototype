# T003 — Test and report harness

**Outcome** PASS · 2026-11-25

## Inspected state and changes

- `FighterPrototype` uses UE 5.9.0 build `60738873` and Unreal MCP `1.0`. Before the build the live editor showed `/Game/ThirdPerson/Lvl_ThirdPerson`, no active PIE session and no dirty packages. The checkpoint was [T002](TASK_002_RESULT.md), Git commit `9be308b`.
- Added `Source/FighterPrototype/Tests/ThirdPersonBaselineTest.cpp` and the private `EngineSettings` dependency in `Source/FighterPrototype/FighterPrototype.Build.cs`. The test checks the configured startup and default map, the ThirdPerson map package, and the native ancestry of the configured GameMode, pawn and controller. It resolves the Blueprint GameMode class and inspects its defaults.
- Added `Scripts/Run-SmokeTests.ps1` and `reports/TASK_REPORT_TEMPLATE.md`. Updated `reports/README.md`, `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv`. No Unreal assets were edited.

## Checks

```powershell
$engine = 'C:/Program Files/Epic Games/UE_5.9/Engine'
$root = (Get-Location).Path
& "$engine/Build/BatchFiles/Build.bat" FighterPrototypeEditor Win64 Development "-Project=$root/FighterPrototype.uproject" -WaitMutex -NoHotReloadFromIDE "-Log=$root/Saved/Logs/Phase00-T003-UBT.log"
powershell -NoProfile -ExecutionPolicy Bypass -File .\Scripts\Run-SmokeTests.ps1
powershell -NoProfile -ExecutionPolicy Bypass -File .\Scripts\Run-SmokeTests.ps1 -TestFilter FighterPrototype.Smoke.NoSuchCase -TimeoutSeconds 90
```

| Check | Result | Command, observation and evidence path |
|---|---|---|
| Development Editor build | PASS | Exit `0`. UBT compiled `ThirdPersonBaselineTest.cpp` and linked `UnrealEditor-FighterPrototype.dll`. `Saved/Logs/Phase00-T003-UBT.log`. |
| Headless automation and ThirdPerson regression | PASS | Ran `UnrealEditor-Cmd.exe` with `-ExecCmds="Automation RunTests FighterPrototype.Smoke"`, `-TestExit="Automation Test Queue Empty"` and `-NullRHI`. `FighterPrototype.Smoke.ThirdPersonBaseline` returned `Success`. One passed, zero warnings, zero failures, zero not run. `Saved/Automation/FighterPrototype/20261125-005523-dd0aeb80/index.json` and `Unreal.log`. |
| Missing-test handling | PASS | A deliberate nonexistent filter matched zero tests. Unreal exported no results and the PowerShell runner returned `1`. `Saved/Automation/FighterPrototype/20261125-005552-6c8872fd/Unreal.log`. |
| Report format | PASS | This report uses the shared template and records the exact invocations, counts, evidence, and rollback point. |
| Interactive PIE and screenshot | NOT RUN | T003 validates configuration and class loading in headless automation. The last interactive baseline is documented in T002. |

## Risks, rollback and handoff

- The installed-engine Fab dependency warning seen in T001 remains non-blocking. The headless suite covers template wiring. It does not exercise physical input or game rules.
- Restore individual files from `9be308b` if rolling back. The pre-edit commit and hashes are recorded in `Saved/Phase00/T003-PreEdit/`.
- **Ready for T004**. The invocation and expected output are documented in the [reports guide](README.md).
