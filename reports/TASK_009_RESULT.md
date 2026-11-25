# T009 — Player One Enhanced Input

**Outcome** PASS · 2026-11-25

Checkpoint `3054663`. Added `FightPlayerController.h/.cpp` and wired the class through FightGameMode. Updated `FighterCharacter.h/.cpp` and `SharedFighterStats.h` with shared locomotion values and the crouch visual. The greybox uses A/D for screen-left/right. The actor's facing determines whether a direction uses the 450 cm/s forward or 340 cm/s backward speed. W jumps and S crouches while held.

The editor saved these project assets through `Scripts/Editor/CreateFightKeyboardInput.py`.

- `/Game/Fight/Input/IMC_FightKeyboard`
- `/Game/Fight/Input/IA_FightMoveHorizontal`
- `/Game/Fight/Input/IA_FightJump`
- `/Game/Fight/Input/IA_FightCrouch`

| Check | Result | Evidence |
|---|---|---|
| Development Editor | PASS | UE 5.9.0 build 60738873, `Build.bat FighterPrototypeEditor Win64 Development -Project=<project> -WaitMutex -NoHotReloadFromIDE`. `Saved/Logs/Phase01-T009-UBT.log`. |
| Key mappings in greybox PIE | PASS | MCP queued A/D/W/S key input through Unreal's player input. A moved left, D moved right, and swapping sides changed which action was forward while preserving the speeds. |
| Jump, crouch and plane | PASS | W raised the pawn by 104.84 cm at the sampled point and the pawn landed at its previous height. S changed capsule half-height from 90 to 52 cm and release restored it. The sampled Y drift was 0 cm. |
| P1 isolation and camera | PASS | A temporary second local player possessed FighterB. FighterB's position stayed fixed through the P1 key sequence and both controllers kept the shared view. |
| ThirdPerson baseline | PASS | `powershell -NoProfile -ExecutionPolicy Bypass -File Scripts/Run-SmokeTests.ps1` ran one test with zero failures. `Saved/Automation/FighterPrototype/20261125-232738-50579bf6/index.json`. The ThirdPerson and FightShell maps, project defaults and MCP config matched their original hashes. |
| Physical keyboard and P2 gamepad | NOT RUN | Key events were injected through the live editor and the second local player was created for the check. Device routing is T010. |

[PIE readback](evidence/T009-Greybox-PIE.json) and [viewport screenshot](evidence/T009-Greybox-PIE.png). The 52 cm crouched capsule half-height is a greybox tuning value. The editor is on `Lvl_FightGreybox` with PIE stopped. Rollback checkpoint `3054663`. Ready for T010 when requested.
