# T005 — Symmetric Greybox Stage

**Phase:** 01 — Greybox two-fighter movement and controls | **Phase gate:** G1 | **Task status:** NOT_STARTED
**Prerequisite:** T004 verified report `reports/TASK_004_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Create one clean symmetric training arena for gameplay logic.

## Scope — implementation and deliverables

Create /Game/Fight/Maps/Lvl_FightGreybox with floor, symmetric X bounds, safe spawn markers and side-view staging; no imported art.

## Safety / boundaries

- Implement **ONLY T005**. Do not automatically start T006 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Fighters-to-be have centered floor and both stage walls; stage loads, PIE safe; dimensions documented.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_005_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Check arena visibly symmetric.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_01/T005_SYMMETRIC_GREYBOX_STAGE.md. Run ONLY T005 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_005_RESULT.md, update status, then STOP. Do not start the next task.
```
