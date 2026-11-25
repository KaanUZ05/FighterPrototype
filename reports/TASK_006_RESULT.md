# T006 — Two fighter spawn

**Outcome** PASS · 2026-11-25

Checkpoint `e71d06a`. Updated `FightGameMode.h/.cpp` and `FighterCharacter.h/.cpp`, and added native `SharedFighterStats.h` under `Source/FighterPrototype/Fight`. No level or config changes. Both fighters use the same `/Script/FighterPrototype.Default__SharedFighterStats` object and Engine primitive meshes over identical collision capsules.

| Check | Result | Evidence |
|---|---|---|
| Development Editor | PASS | UE 5.9.0 build 60738873, `Build.bat FighterPrototypeEditor Win64 Development -Project=<project> -WaitMutex -NoHotReloadFromIDE`. Initial C4458 shadowing was corrected. `Saved/Logs/Phase01-T006-UBT.log` records the successful build. |
| Identities, ownership and facing | PASS | Two distinct pawns at X=−220/+220 and Y=0. P1 possessed FighterA, FighterB was available as an unpossessed dummy, and both faced inward. |
| Restart | PASS | Three live `RestartPlayer` calls left the same possessed pawn and exactly two fighters. |
| Second physical player | NOT RUN | The greybox creates one local player by default. A second slot is assigned if a second local controller is present. Physical routing is T010. |

See [PIE readback](evidence/T006-Greybox-PIE.json) and [both capsules](evidence/T006-Greybox-PIE.png). The camera was switched to the inspection view only during the check. Rollback checkpoint `e71d06a`. Ready for T007.
