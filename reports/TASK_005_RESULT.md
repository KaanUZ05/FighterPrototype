# T005 — Symmetric greybox stage

**Outcome** PASS · 2026-11-25

The T004 checkpoint was `72afffc`. Created `/Game/Fight/Maps/Lvl_FightGreybox` from Unreal's Basic template with Engine meshes and a map-local FightGameMode override. The replayable creation script is `Scripts/Editor/CreateFightGreybox.py`. UE 5.9.0 build `60738873` and the local Unreal MCP endpoint responded.

| Check | Result | Evidence |
|---|---|---|
| Floor and walls | PASS | Floor measures 1600 × 600 × 50 cm, with its top at Z=0. Walls measure 40 × 600 × 400 cm. Inner faces are X=−760 and +760. |
| Spawn markers and inspection view | PASS | Tagged starts at X=−220 and +220, Y=0, Z=100. The shallow orthographic inspection view shows both ends. |
| Saved map PIE | PASS | Loaded the saved map, verified collision bounds and both starts in the PIE world, and observed the existing FightGameMode and FighterCharacter. PIE stopped cleanly. |
| C++ rebuild | NOT RUN | No native code changed. |

Evidence is the [PIE readback](evidence/T005-Greybox-PIE.json) and [arena screenshot](evidence/T005-Greybox-PIE.png). The original ThirdPerson and shell maps were outside the edit. Rollback checkpoint is `72afffc`. Ready for T006.
