# T001 — Project audit and build

**Outcome: PASS** · 2026-11-25

## Inspected state

- `FighterPrototype.uproject` associates with UE 5.9 and declares the `FighterPrototype` runtime module. The installed editor and the live session both reported UE 5.9.0, build `60738873`. The engine's Unreal MCP descriptor reports version `1.0`.
- Live MCP resolved `/Game/ThirdPerson/Lvl_ThirdPerson`. The prior read probe returned 72 actor descriptors. The editor startup and game defaults in `Config/DefaultEngine.ini` both point to this map. The default GameMode is `/Game/ThirdPerson/Blueprints/BP_ThirdPersonGameMode.BP_ThirdPersonGameMode_C`, backed by the template `AFighterPrototypeGameMode`.
- `Config/DefaultInput.ini` selects `EnhancedPlayerInput` and `EnhancedInputComponent`. The template controller installs mapping contexts and the character binds move, jump, and look actions. The move asset is `/Game/Input/Actions/IA_Move.IA_Move`.
- Git reported no repository at the project root or its parents. Git LFS `3.7.1` was present. The existing startup prompt and mandatory project docs were read. `README_START_HERE.md` was absent from the updated tree.

## Build and checks

```powershell
$build = 'C:/Program Files/Epic Games/UE_5.9/Engine/Build/BatchFiles/Build.bat'
$root = (Get-Location).Path
& $build FighterPrototypeEditor Win64 Development "-Project=$root/FighterPrototype.uproject" -WaitMutex -NoHotReloadFromIDE "-Log=$root/Saved/Logs/Phase00-T001-Current-UBT.log"
& $build FighterPrototypeEditor Win64 Development "-Project=$root/Saved/Phase00/T001-Clean-20261125-002747/FighterPrototype.uproject" -WaitMutex -NoHotReloadFromIDE -NoUBA "-Log=$root/Saved/Logs/Phase00-T001-Clean-UBT.log"
```

| Check | Result | Observation |
|---|---|---|
| Project-root Development Editor build | PASS | Exit `0`, `Target is up to date`, `Result: Succeeded`. |
| Clean C++ Development Editor build | PASS | Isolated copy built all 48 actions through DLL link and target metadata. `Result: Succeeded`. SHA-256 matched the current project across all 93 `.uproject`, `Source/`, and `Config/` files checked. |
| Toolchain | PASS | MSVC toolchain `14.44.35229` and Windows SDK `10.0.22621.0` were used. |
| Live PIE launch | PASS | `/Game/ThirdPerson/UEDPIE_0_Lvl_ThirdPerson` loaded with `BP_ThirdPersonGameMode_C`. No Blueprint recompile was needed. |
| Template movement smoke | PASS | Injecting forward `IA_Move` for 0.65 s moved the character's player camera from X `-400.00` to X `34.75` cm. PIE stopped and the original map remained active. |
| Automation suite and physical input devices | NOT RUN | The task verifies the existing template and the input smoke used the live editor's Enhanced Input injection. |

UBT emitted a non-blocking installed-engine `Fab` plugin dependency warning about `ToolsetRegistry`. The clean and current builds both succeeded.

## Files, evidence, and rollback

- Updated `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv`. Added this report and captured [`T001-ThirdPerson-PIE.png`](evidence/T001-ThirdPerson-PIE.png). The screenshot shows the template character in the live PIE viewport.
- Build logs are `Saved/Logs/Phase00-T001-Current-UBT.log` and `Saved/Logs/Phase00-T001-Clean-UBT.log`. `Saved/Logs/FighterPrototype.log` records the PIE GameMode, startup, and shutdown.
- The task did not edit C++, project settings, the MCP config, or any Unreal asset. The pre-report copies of the status files are in `Saved/Phase00/T001-PreReport/`.

**Ready for T002: YES.** The owner can review the screenshot and confirm the ThirdPerson baseline opens locally.
