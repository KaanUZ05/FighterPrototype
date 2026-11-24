# T001 — Project Audit And Build

**Phase:** 00 — Foundation, verification and reproducibility | **Phase gate:** G0 | **Task status:** NOT_STARTED
**Prerequisite:** Current Codex MCP read-only probe (already reported by user).
**Project:** `FighterPrototype`, UE 5.9.0, Windows, C++, local MCP.

## Objective

Verify this existing UE5.9 project builds and launches before changing gameplay.

## Scope — implementation and deliverables

Inspect .uproject, Source, GameMode and input defaults; confirm 5.9.0 version; locate UBT/Windows toolchain; compile Development Editor; launch/inspect current level in PIE; audit repo without destructive init. Preserve existing MCP.

## Safety / boundaries

- Implement **ONLY T001**. Do not automatically start T002 or later tasks. Work on local project; discover actual Unreal MCP tools and UE5.9 APIs from installed editor. Do not edit `.codex/config.toml`.
- Respect exact shared stats/normal attack invariants in `AGENTS.md`, `docs/01_VISION_AND_GDD.md` and `docs/02_COMBAT_RULES.md`.
- Do not buy/download paid content or replace existing user content without approval. **Do not expand scope beyond this exact task or the next dependency.**
- Before changes make a reversible checkpoint; prefer minimal scoped source/Blueprint/Data Asset updates. No guessed success or fake screenshots.

## Required acceptance checks (objective, not just source inspection)

Real compile output and current PIE outcome recorded; version/path verified; no existing gameplay assets overwritten; note any missing MSVC/SDK as BLOCKED.

**T001 extra mandatory check:** Attempt and document the real Development Editor C++ build **even when no code changes were made**. If the project is not a C++ project or MSVC/SDK is missing, report this explicitly as a blocker; do not skip silently.

### Minimum evidence before DONE

1. List every real changed file/Blueprint/map/Data Asset and its verified Unreal path.
2. Run the actual C++ build if code changed; capture command and result. If impossible mark `NOT RUN` with reason.
3. Run a real PIE or automation check for the objective when tool/hardware permits; distinguish `PASS`/`FAIL`/`NOT RUN`.
4. Verify no regressions against the most relevant earlier gate; for Phase >=2, preserve normal/locomotion parity tests.
5. Write `reports/TASK_001_RESULT.md`; update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` based only on observed evidence.
6. **STOP** and do not progress to next task until user explicitly requests it.

## Human review (if applicable)

Confirm original ThirdPerson map still opens after baseline; review T001 report.

## Copy-paste instruction

```text
Read AGENTS.md, docs/PROJECT_STATUS.md, the game design and roadmap, and tasks/phase_00/T001_PROJECT_AUDIT_AND_BUILD.md. Run ONLY T001 in my existing Unreal Engine 5.9 FighterPrototype project. Check prerequisites and safe rollback. Execute tasks and tests, write reports/TASK_001_RESULT.md, update status, then STOP. Do not start the next task.
```
