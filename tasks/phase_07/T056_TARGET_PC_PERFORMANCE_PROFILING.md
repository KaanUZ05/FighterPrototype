# T056 — Target Pc Performance Profiling

**Phase:** 07 — Regression, performance, packaging and handoff | **Phase gate:** G7 | **Task status:** NOT_STARTED
**Prerequisite:** T055 verified report `reports/TASK_055_RESULT.md`.
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Measure real game performance and fix major regressions.

## Scope — implementation and deliverables

Record target PC GPU/CPU/settings, profile editor standalone or packaged scene, frame time on stage, VFX costs; prioritize obvious perf fixes.

## Safety / boundaries

- Implement **ONLY T056**. Do not automatically start T057 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Human sign-off or asset approval required before proceeding. STOP if this is not granted.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Measured not guessed frame-time and FPS; no critical spikes in repeated rounds; target 60fps where hardware permits.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_056_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Play at native screen resolution and report stutter.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_07/T056_TARGET_PC_PERFORMANCE_PROFILING.md. Run ONLY T056 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_056_RESULT.md, update status, then STOP. Do not start the next task.
```
