# MASTER DEVELOPMENT ROADMAP — 59 single-task milestones (v2.0)

**The agent MUST execute one numbered task per user turn and STOP.** Read `AGENTS.md`. Every task below is a separate `.md` with scope, acceptance and individual prompt. No task automatically approves the next.

## Starting state

UE 5.9.0 MCP read-only connection to FighterPrototype verified; actual C++ build and PIE success **unverified**. Start with **T001**, not T002; previous connectivity query is reusable T001 evidence but not entire G0.

## Delivery target

Original offline Windows local 1v1 2.5D fighter, 2 original characters, one arena, equal baseline normal attacks/movement, four unique special slots, match UI and potential two non-gory finishers only after approval.

## Phase gates

| Phase | Gate | Task IDs | Phase definition of done |
|---|---|---|---|
| 00 — Foundation, verification and reproducibility | **G0** | T001–T004 | Clean compile + live editor workflow + safe checkpoints |
| 01 — Greybox two-fighter movement and controls | **G1** | T005–T012 | Symmetric greybox 2-player movement; fighting plane and same camera |
| 02 — Authoritative shared normal combat | **G2** | T013–T021 | Shared four-normal combat with exact frame parity and box debug |
| 03 — Defense, combos and complete match loop | **G3** | T022–T030 | Complete guarding/combo/health/timer/best-of-three match loop |
| 04 — Character-specific special moves and parity gate | **G4** | T031–T037 | 2 specials per fighter with base equality intact |
| 05 — Original character art and animation integration | **G5** | T038–T045 | Two original user-approved 3D characters and animation quality gate |
| 06 — Stage, cinematics, VFX, audio, menus and polish | **G6** | T046–T053 | One cinematic original arena, polished UI/VFX/audio, optional finishers |
| 07 — Regression, performance, packaging and handoff | **G7** | T054–T059 | Windows executable, tested input/performance, full handoff |

## Single-task index

### Phase 00 — Foundation, verification and reproducibility (G0)

- **T001** — [Project Audit And Build](../tasks/phase_00/T001_PROJECT_AUDIT_AND_BUILD.md). Previous: MCP read probe.
- **T002** — [Mcp Write And Checkpoint](../tasks/phase_00/T002_MCP_WRITE_AND_CHECKPOINT.md). Previous: T001.
- **T003** — [Test And Report Harness](../tasks/phase_00/T003_TEST_AND_REPORT_HARNESS.md). Previous: T002.
- **T004** — [Fight Module Shell](../tasks/phase_00/T004_FIGHT_MODULE_SHELL.md). Previous: T003.

### Phase 01 — Greybox two-fighter movement and controls (G1)

- **T005** — [Symmetric Greybox Stage](../tasks/phase_01/T005_SYMMETRIC_GREYBOX_STAGE.md). Previous: T004.
- **T006** — [Two Fighter Spawn](../tasks/phase_01/T006_TWO_FIGHTER_SPAWN.md). Previous: T005.
- **T007** — [Lock Fighting Plane And Pushbox](../tasks/phase_01/T007_LOCK_FIGHTING_PLANE_AND_PUSHBOX.md). Previous: T006.
- **T008** — [Facing And Shared Camera](../tasks/phase_01/T008_FACING_AND_SHARED_CAMERA.md). Previous: T007.
- **T009** — [Player One Enhanced Input](../tasks/phase_01/T009_PLAYER_ONE_ENHANCED_INPUT.md). Previous: T008.
- **T010** — [Player Two Input Routing](../tasks/phase_01/T010_PLAYER_TWO_INPUT_ROUTING.md). Previous: T009.
- **T011** — [Shared Locomotion Stats And Tests](../tasks/phase_01/T011_SHARED_LOCOMOTION_STATS_AND_TESTS.md). Previous: T010.
- **T012** — [G1 Greybox Playability Gate](../tasks/phase_01/T012_G1_GREYBOX_PLAYABILITY_GATE.md). Previous: T011.

### Phase 02 — Authoritative shared normal combat (G2)

- **T013** — [Shared Normal Move Data](../tasks/phase_02/T013_SHARED_NORMAL_MOVE_DATA.md). Previous: T012.
- **T014** — [Combat 60Hz Logic Clock](../tasks/phase_02/T014_COMBAT_60HZ_LOGIC_CLOCK.md). Previous: T013.
- **T015** — [Input Command Buffer](../tasks/phase_02/T015_INPUT_COMMAND_BUFFER.md). Previous: T014.
- **T016** — [Shared Combat State Machine](../tasks/phase_02/T016_SHARED_COMBAT_STATE_MACHINE.md). Previous: T015.
- **T017** — [Normal Attack Activation](../tasks/phase_02/T017_NORMAL_ATTACK_ACTIVATION.md). Previous: T016.
- **T018** — [Canonical Hit And Hurt Boxes](../tasks/phase_02/T018_CANONICAL_HIT_AND_HURT_BOXES.md). Previous: T017.
- **T019** — [Damage Stun Knockback And Hitstop](../tasks/phase_02/T019_DAMAGE_STUN_KNOCKBACK_AND_HITSTOP.md). Previous: T018.
- **T020** — [Normals Symmetry Automation](../tasks/phase_02/T020_NORMALS_SYMMETRY_AUTOMATION.md). Previous: T019.
- **T021** — [Combat Gym Debug Display G2](../tasks/phase_02/T021_COMBAT_GYM_DEBUG_DISPLAY_G2.md). Previous: T020.

### Phase 03 — Defense, combos and complete match loop (G3)

- **T022** — [Directional Standing Crouch Guard](../tasks/phase_03/T022_DIRECTIONAL_STANDING_CROUCH_GUARD.md). Previous: T021.
- **T023** — [Hitstun Blockstun Recovery Rules](../tasks/phase_03/T023_HITSTUN_BLOCKSTUN_RECOVERY_RULES.md). Previous: T022.
- **T024** — [Shared Crouch And Jump Normals](../tasks/phase_03/T024_SHARED_CROUCH_AND_JUMP_NORMALS.md). Previous: T023.
- **T025** — [Simple Universal Combo Chain](../tasks/phase_03/T025_SIMPLE_UNIVERSAL_COMBO_CHAIN.md). Previous: T024.
- **T026** — [Health Ko And Round Reset](../tasks/phase_03/T026_HEALTH_KO_AND_ROUND_RESET.md). Previous: T025.
- **T027** — [Round Timer And Best Of Three](../tasks/phase_03/T027_ROUND_TIMER_AND_BEST_OF_THREE.md). Previous: T026.
- **T028** — [Authoritative Hud](../tasks/phase_03/T028_AUTHORITATIVE_HUD.md). Previous: T027.
- **T029** — [Pause Match Result Rematch](../tasks/phase_03/T029_PAUSE_MATCH_RESULT_REMATCH.md). Previous: T028.
- **T030** — [G3 Full Match Regression](../tasks/phase_03/T030_G3_FULL_MATCH_REGRESSION.md). Previous: T029.

### Phase 04 — Character-specific special moves and parity gate (G4)

- **T031** — [Special Data And Behavior Interface](../tasks/phase_04/T031_SPECIAL_DATA_AND_BEHAVIOR_INTERFACE.md). Previous: T030.
- **T032** — [Special Input And Execution State](../tasks/phase_04/T032_SPECIAL_INPUT_AND_EXECUTION_STATE.md). Previous: T031.
- **T033** — [Projectile System](../tasks/phase_04/T033_PROJECTILE_SYSTEM.md). Previous: T032.
- **T034** — [Lunge Skill](../tasks/phase_04/T034_LUNGE_SKILL.md). Previous: T033.
- **T035** — [Area Attack And Close Burst](../tasks/phase_04/T035_AREA_ATTACK_AND_CLOSE_BURST.md). Previous: T034.
- **T036** — [Four Specials Config And Balance Seed](../tasks/phase_04/T036_FOUR_SPECIALS_CONFIG_AND_BALANCE_SEED.md). Previous: T035.
- **T037** — [G4 Specials Fairness Approval](../tasks/phase_04/T037_G4_SPECIALS_FAIRNESS_APPROVAL.md). Previous: T036.

### Phase 05 — Original character art and animation integration (G5)

- **T038** — [Art Bible And Original Roster Approval](../tasks/phase_05/T038_ART_BIBLE_AND_ORIGINAL_ROSTER_APPROVAL.md). Previous: T037.
- **T039** — [Fighter A Turnaround](../tasks/phase_05/T039_FIGHTER_A_TURNAROUND.md). Previous: T038.
- **T040** — [Fighter B Turnaround](../tasks/phase_05/T040_FIGHTER_B_TURNAROUND.md). Previous: T039.
- **T041** — [First Production 3D Mesh](../tasks/phase_05/T041_FIRST_PRODUCTION_3D_MESH.md). Previous: T040.
- **T042** — [Second Production 3D Mesh](../tasks/phase_05/T042_SECOND_PRODUCTION_3D_MESH.md). Previous: T041.
- **T043** — [Skeleton Rig And Retarget](../tasks/phase_05/T043_SKELETON_RIG_AND_RETARGET.md). Previous: T042.
- **T044** — [Shared Normal Animation Set](../tasks/phase_05/T044_SHARED_NORMAL_ANIMATION_SET.md). Previous: T043.
- **T045** — [Special Animations And G5 Visual Qa](../tasks/phase_05/T045_SPECIAL_ANIMATIONS_AND_G5_VISUAL_QA.md). Previous: T044.

### Phase 06 — Stage, cinematics, VFX, audio, menus and polish (G6)

- **T046** — [Production Arena Lighting](../tasks/phase_06/T046_PRODUCTION_ARENA_LIGHTING.md). Previous: T045.
- **T047** — [Main Menu Character Select](../tasks/phase_06/T047_MAIN_MENU_CHARACTER_SELECT.md). Previous: T046.
- **T048** — [Shared And Unique Vfx](../tasks/phase_06/T048_SHARED_AND_UNIQUE_VFX.md). Previous: T047.
- **T049** — [Original Audio And Mix](../tasks/phase_06/T049_ORIGINAL_AUDIO_AND_MIX.md). Previous: T048.
- **T050** — [Camera Hitstop Victory Presentation](../tasks/phase_06/T050_CAMERA_HITSTOP_VICTORY_PRESENTATION.md). Previous: T049.
- **T051** — [Finisher Presentation Infrastructure](../tasks/phase_06/T051_FINISHER_PRESENTATION_INFRASTRUCTURE.md). Previous: T050.
- **T052** — [Two Original Finishers](../tasks/phase_06/T052_TWO_ORIGINAL_FINISHERS.md). Previous: T051.
- **T053** — [G6 Playtest And Polish Gate](../tasks/phase_06/T053_G6_PLAYTEST_AND_POLISH_GATE.md). Previous: T052.

### Phase 07 — Regression, performance, packaging and handoff (G7)

- **T054** — [Automated Full Regression](../tasks/phase_07/T054_AUTOMATED_FULL_REGRESSION.md). Previous: T053.
- **T055** — [Physical Local Two Player Qa](../tasks/phase_07/T055_PHYSICAL_LOCAL_TWO_PLAYER_QA.md). Previous: T054.
- **T056** — [Target Pc Performance Profiling](../tasks/phase_07/T056_TARGET_PC_PERFORMANCE_PROFILING.md). Previous: T055.
- **T057** — [Final Ui Accessibility Settings](../tasks/phase_07/T057_FINAL_UI_ACCESSIBILITY_SETTINGS.md). Previous: T056.
- **T058** — [Windows Shipping Package Smoke](../tasks/phase_07/T058_WINDOWS_SHIPPING_PACKAGE_SMOKE.md). Previous: T057.
- **T059** — [Release Notes Licenses And Final Gate](../tasks/phase_07/T059_RELEASE_NOTES_LICENSES_AND_FINAL_GATE.md). Previous: T058.

## How to launch one task

1. Ensure ZIP contents were merged into the same project root as `FighterPrototype.uproject`; do not change live MCP configuration.
2. In VS Code Codex paste `prompts/START_TASK_001.md` for T001. For any other task paste the **Copy-paste instruction** at end of its file or use `prompts/RUN_ONE_TASK_TEMPLATE.md` with correct ID/path.
3. Require build/PIE evidence and `reports/TASK_###_RESULT.md` for each task. If BLOCKED/PARTIAL, fix that task, not the next one.
4. At G0 through G7 user must accept the milestone by playtest/inspection. Tasks after that gate should not start without approval.

## Scope control

Do **not** add multiplayer networking, rollback, story campaign, console platforms, commercial monetization, hundreds of cinematics or new fighters in this roadmap. Special designs and art are intentionally provisional until user approval. Finisher tasks may remain blocked/optional and must not prevent a playable MVP if declined.

## Change log

2026-11-25: Expanded starter docs from a 7-row roadmap with only three task files to a complete 59-task plan; engine state carried forward from MCP probe; no actual Unreal project code claimed to be written.

**Special dependency exception:** T052 finishers are optional; after explicit user decision to omit them, write a T052 result and mark `SKIPPED_OPTIONAL_APPROVED`, then T053 may proceed. Do not misreport cinematics as implemented.
