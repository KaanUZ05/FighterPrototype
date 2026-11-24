# T027 — Round Timer And Best Of Three

**Phase:** 03 — Defense, combos and complete match loop | **Phase gate:** G3 | **Task status:** NOT_STARTED
**Prerequisite:** T026 verified report `reports/TASK_026_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Implement 99-second logical timer, draws and first-to-two score.

## Scope — implementation and deliverables

Match controller starts count-in; timer decrements with combat/round pause rules; KO and timeout adjudication; symmetrical tied-health draw/replay; best-of-three ends at 2 wins.

## Safety / boundaries

- Implement **ONLY T027**. Do not automatically start T028 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Sequence 2-0 and 2-1 resolves correctly; tie never benefits P1 by default; round clock does not run in pause/countdown.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_027_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Play full match and inspect score.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_03/T027_ROUND_TIMER_AND_BEST_OF_THREE.md. Run ONLY T027 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_027_RESULT.md, update status, then STOP. Do not start the next task.
```
