# T007 — Fighting plane and pushboxes

**Outcome** PASS · 2026-11-25

Checkpoint `a8a9e06`. Added `FighterMovementComponent.h/.cpp` and updated the native fighter and GameMode. Added bound tags to the two existing walls in `/Game/Fight/Maps/Lvl_FightGreybox` and mirrored the tags in `Scripts/Editor/CreateFightGreybox.py`. The movement component keeps the engine Y-plane constraint, clamps swept movement against the wall faces and uses the fighter's shared capsule radius. Capsules block other fighters and cannot step onto them during a walk.

| Check | Result | Evidence |
|---|---|---|
| Development Editor | PASS | UE 5.9.0 build 60738873. `Build.bat FighterPrototypeEditor Win64 Development -Project=<project> -WaitMutex -NoHotReloadFromIDE`, seven actions. `Saved/Logs/Phase01-T007-UBT.log`. |
| Pushbox and spawn regression | PASS | Two fighters still spawned at X=−220/+220. Simultaneous inward walks reached a minimum center gap of 76.10 cm with 38 cm radii. |
| Plane and stage limits | PASS | Depth-only input and launch produced zero Y drift. High launches above the 400 cm walls clamped at X=−722/+722 with zero Y drift. |
| Authored root motion animation | NOT RUN | Movement from animation uses the same constrained component. No root-motion animation asset was available in this slice. |

[PIE readback](evidence/T007-Greybox-PIE.json). The original maps were outside the edit. Rollback checkpoint `a8a9e06`. Ready for T008.
