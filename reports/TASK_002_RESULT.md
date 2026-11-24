# T002 — MCP write and checkpoint

**Outcome: PASS** · 2026-11-25

## Inspected state

`FighterPrototype` was open in UE 5.9.0 build `60738873` with Unreal MCP `1.0`. The ThirdPerson editor level was clean and PIE was stopped. [T001](TASK_001_RESULT.md) established the Development Editor and PIE baseline. Live `list_toolsets` returned 112 toolsets. The [MCP actor diff](evidence/T002-MCP-actor-diff.json) records the names and the responses used for verification.

## Checks

| Check | Result | Observed evidence |
|---|---|---|
| Local Git and Git LFS baseline | PASS | Initialized `main` with owner authorization and configured `origin` for `KaanUZ05/FighterPrototype`. Baseline commit `ec6e05b2289a8b0fa8b0fa537aae9114d90cb3de` contains 934 files and 753 LFS assets. Verified a staged `.umap` pointer and ran `git lfs fsck HEAD` successfully. |
| Ignore and credentials audit | PASS | `git check-ignore` confirmed `.codex/config.toml`, caches, build output, logs, and generated solutions are excluded. Local Git authorship uses the GitHub no-reply address. |
| MCP write, read and save | PASS | Opened `/Game/M_T002_McpScratch_20261125`. Placed `/Script/Engine.PointLight` with label `T002_MCP_ProbeLight` at `(120, -80, 240)` cm. Read back the actor and transform. The editor confirmed the level save, and the saved map was copied to the local checkpoint. |
| Undo and save | PASS | Confirmed the latest transaction was `Place Object` (`2F79A621-453E-BE3A-4A57-BE89A0CFCAC8`). `TRANSACTION UNDO` logged `Undo Place Object`. The same MCP actor query returned `[]`, and the actor-free scratch map was saved. |
| Scratch cleanup and original level | PASS | Returned to `/Game/ThirdPerson/Lvl_ThirdPerson`. MCP `Delete` unloaded the scratch asset but left its `.umap` on disk. After archiving that single file under `Saved`, MCP `Exists` returned `false`. All 72 original actor names, labels and classes matched the pre-edit query. The prior viewport transform and empty selection were restored. |
| Original project files | PASS | File paths and SHA-256 matched for all 845 files in `Content/`, `Config/` and `Source/`. The `.uproject` and `.codex/config.toml` hashes also matched their pre-task readings. No map or content package was dirty after the check. |
| ThirdPerson PIE regression | PASS | The original level launched as `/Game/ThirdPerson/UEDPIE_0_Lvl_ThirdPerson` with `BP_ThirdPersonGameMode_C` and a player camera sourced from `BP_ThirdPersonCharacter_C_0`. PIE stopped cleanly. |
| C++ rebuild and automation suite | NOT RUN | T002 made no code or build configuration changes. T001 verified the editor build and T002 reran live PIE. |

## Changes and rollback

- Updated `.gitignore` to exclude `.codex/` and generated `*.slnx` files. Added this report and the actor diff. Updated `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv`. Git metadata and the LFS hook are local, and the temporary Unreal map and actor have been removed from project Content.
- Restore or compare individual files against baseline commit `ec6e05b`. Local copies of the original project files and the two saved scratch states are in `Saved/Phase00/T002-PreEdit/`. The editor log is `Saved/Logs/FighterPrototype.log`.
- Switching levels cleared one pre-existing `Edit Client Selection` undo entry. The project already contained trailing whitespace in generated template source, which was preserved in the baseline. The scoped whitespace check for new edits passed.

**Ready for T003: YES.** The actor diff is available for owner review.
