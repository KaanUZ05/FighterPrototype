# T034 — Lunge Skill

**Phase:** 04 — Character-specific special moves and parity gate | **Phase gate:** G4 | **Task status:** NOT_STARTED
**Prerequisite:** T033 verified report `reports/TASK_033_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Implement first skill-specific movement strike without altering normal locomotion.

## Scope — implementation and deliverables

A slot1 lunge with timed start/recovery and bounded X displacement; collision/cancel handling; after skill revert to identical shared movement.

## Safety / boundaries

- Implement **ONLY T034**. Do not automatically start T035 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Lunge respects Y plane and walls/pushboxes; no permanent speed buff; frame data tested; collision cannot teleport behind wall.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_034_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Perform lunge near both arena edges.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_04/T034_LUNGE_SKILL.md. Run ONLY T034 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_034_RESULT.md, update status, then STOP. Do not start the next task.
```
