# T033 — Projectile System

**Phase:** 04 — Character-specific special moves and parity gate | **Phase gate:** G4 | **Task status:** NOT_STARTED
**Prerequisite:** T032 verified report `reports/TASK_032_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Implement first slow 2.5D projectile skill, engine-agnostic enough to reuse.

## Scope — implementation and deliverables

Create gameplay projectile actor/data that travels X on locked Y, one-hit collision or guard, stage lifetime and cleanup; B slot1 prototype.

## Safety / boundaries

- Implement **ONLY T033**. Do not automatically start T034 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Projectile launches with correct facing, cannot hit owner/multihit, vanishes after collision/stage/round, handles guard.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_033_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Try firing from both sides; watch expiry.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_04/T033_PROJECTILE_SYSTEM.md. Run ONLY T033 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_033_RESULT.md, update status, then STOP. Do not start the next task.
```
