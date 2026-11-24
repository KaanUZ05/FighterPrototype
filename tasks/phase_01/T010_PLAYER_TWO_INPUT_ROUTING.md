# T010 — Player Two Input Routing

**Phase:** 01 — Greybox two-fighter movement and controls | **Phase gate:** G1 | **Task status:** NOT_STARTED
**Prerequisite:** T009 verified report `reports/TASK_009_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Implement P2 independent gamepad controls and dummy fallback for development.

## Scope — implementation and deliverables

Create local player 1 and route gamepad to P2 using UE 5.9 settings / subsystem; disable split screen; add development-only programmable dummy when physical gamepad absent.

## Safety / boundaries

- Implement **ONLY T010**. Do not automatically start T011 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

P1 inputs do not control P2; P2 gamepad works if hardware available; otherwise report physical test NOT RUN and demo deterministic dummy control; no split screen.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_010_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Connect gamepad/controller and verify simultaneous control if available.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_01/T010_PLAYER_TWO_INPUT_ROUTING.md. Run ONLY T010 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_010_RESULT.md, update status, then STOP. Do not start the next task.
```
