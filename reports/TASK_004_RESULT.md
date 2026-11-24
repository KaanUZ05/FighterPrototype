# T004 — Fight module shell

**Outcome** PASS · 2026-11-25

## Inspected state and changes

- `FighterPrototype` uses UE 5.9.0 build `60738873` and Unreal MCP `1.0`. [T003](TASK_003_RESULT.md) passed at checkpoint `d6b8e04`. ThirdPerson was the clean, active editor level before the build.
- Added `Source/FighterPrototype/Fight/FightGameMode.h`, `FightGameMode.cpp` and `FighterCharacter.h` to the existing module. `/Script/FighterPrototype.FightGameMode` uses `/Script/FighterPrototype.FighterCharacter` as its default pawn. The fighter is a native `ACharacter` scaffold.
- Added `Content/Fight/Maps/M_FightShell.umap` at `/Game/Fight/Maps/M_FightShell`. Created it from the engine's Basic level template and set its World Settings GameMode Override through the live editor. Existing project-level map and GameMode defaults were retained.
- Added the PIE screenshot under `reports/evidence/`. Updated `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv`.

## Checks

```powershell
$engine = 'C:/Program Files/Epic Games/UE_5.9/Engine'
$root = (Get-Location).Path
& "$engine/Build/BatchFiles/Build.bat" FighterPrototypeEditor Win64 Development "-Project=$root/FighterPrototype.uproject" -WaitMutex -NoHotReloadFromIDE "-Log=$root/Saved/Logs/Phase00-T004-UBT.log"
powershell -NoProfile -ExecutionPolicy Bypass -File .\Scripts\Run-SmokeTests.ps1
```

| Check | Result | Command, observation and evidence path |
|---|---|---|
| Development Editor build | PASS | UHT processed the new native classes, UBT compiled `FightGameMode.cpp` and linked `UnrealEditor-FighterPrototype.dll`. Five actions, exit `0`. `Saved/Logs/Phase00-T004-UBT.log`. |
| Headless baseline regression | PASS | `FighterPrototype.Smoke.ThirdPersonBaseline` succeeded. One passed, zero warnings or failures. `Saved/Automation/FighterPrototype/20261125-005738-b69959de/index.json`. |
| Saved map and native classes load | PASS | Reloaded `/Game/Fight/Maps/M_FightShell` from disk and read back `/Script/FighterPrototype.FightGameMode` as the world override. The native `FighterCharacter` class resolved. |
| FightShell PIE and possession | PASS | `/Game/Fight/Maps/UEDPIE_0_M_FightShell.M_FightShell` selected `FightGameMode`, and player 0 possessed `FighterCharacter`. The live viewport showed the Basic floor and sky. [`T004-FightShell-PIE.png`](evidence/T004-FightShell-PIE.png) and `Saved/Logs/FighterPrototype.log`. |
| ThirdPerson PIE regression | PASS | Original level booted with `BP_ThirdPersonGameMode_C` and `BP_ThirdPersonCharacter_C`. PIE stopped and the editor returned to ThirdPerson with its original viewport transform. |
| Original files | PASS | SHA-256 matched for all 760 pre-edit files checked across `Content/`, `Config/`, the `.uproject` and the local MCP configuration. |
| Physical input, combat and packaged build | NOT RUN | The scope is a map and native class shell. |

## Risks, rollback and handoff

- The shell shows the inherited player viewpoint and has no visible fighter mesh or gameplay bindings yet. The GameMode and possessed pawn were verified directly in the PIE world. The installed-engine Fab dependency warning remains non-blocking.
- Open `Content/Fight/Maps/M_FightShell` and press Play to review the opt-in level. The existing ThirdPerson map remains the startup map.
- Rollback checkpoint `d6b8e04`. The pre-edit object hashes and commit are in `Saved/Phase00/T004-PreEdit/`.
- **Ready for G0 owner review**. T005 is the next task after the owner accepts G0.
