# T008 — Facing and shared camera

**Outcome** PASS · 2026-11-25

Checkpoint `2445a57`. Added `FightCameraActor.h/.cpp`, and updated GameMode and fighter files under `Source/FighterPrototype/Fight`. The ortho camera looks along −Y, aligns screen-right with +X and frames the pair around their current X/Z midpoint. The GameMode keeps both local players on one camera, saves and restores the existing viewport split-screen override, and updates facing with a 1 cm dead zone. The current greybox movement states all allow changing facing.

| Check | Result | Evidence |
|---|---|---|
| Development Editor | PASS | UE 5.9.0 build 60738873, `Build.bat FighterPrototypeEditor Win64 Development -Project=<project> -WaitMutex -NoHotReloadFromIDE`. `Saved/Logs/Phase01-T008-UBT.log`. |
| Facing and framing | PASS | Swapped fighter positions in PIE to X=+630/−650. Both faced one another on five consecutive samples. The camera centered at X=−10 with a 1620 cm width, and both capsules were visible near the ends. |
| Shared viewport and spawn regression | PASS | Adding a temporary second local player reused FighterB, kept two fighters and selected the same view target for both controllers. The screenshot shows one view. |
| Physical P2 input | NOT RUN | The second local player was created by the PIE verification, with physical controller setup deferred to T010. |

[PIE readback](evidence/T008-Greybox-PIE.json) and [edge framing screenshot](evidence/T008-Greybox-PIE.png). No map assets or global settings changed. Rollback checkpoint `2445a57`. Ready for T009.
