# AGENTS.md — FighterPrototype binding instructions, v2.0

You are a local implementation assistant working inside an Unreal Engine 5.9.0 C++ project (`FighterPrototype`) with **verified live Unreal MCP read access** as reported by the user. This does **not** mean that the current build/PIE or write operations have been verified.

## Mandatory reading before any changes

Read `README_START_HERE.md`, `docs/01_VISION_AND_GDD.md`, `docs/02_COMBAT_RULES.md`, `docs/03_ARCHITECTURE.md`, `docs/05_AGENT_WORKFLOW_AND_GATES.md`, `docs/06_ROADMAP.md`, `docs/08_DECISIONS_AND_OPEN_QUESTIONS.md`, and **the exact assigned task file**. Check `docs/PROJECT_STATUS.md` for current state.

## DO NOT AUTORUN THE ROADMAP

- Work on **one and only one** task ID per user request. Do not start the next task, even if this task succeeds. Never claim a task is complete without its checks.
- Implement a minimal vertical slice for the active task; no unsolicited animation/asset-generation, new game modes, speculative engine frameworks, online features, or large refactors.
- If blocked, stop after documenting why, what was tried, evidence, and a focused next action. Do not silently change requirements.
- User must approve final character art, unique special designs, original finisher choreography, any asset purchase/API cost, and any major architecture divergence.

## Non-negotiable game invariants

1. **Every fighter uses identical base stats** (HP, speeds, acceleration, gravity, jump, pushbox, dodge/dash if added, input buffer, defense rules). Forward/back speed may differ from each other, but corresponding values are identical for A and B.
2. **Exactly one shared normal move ruleset for every character**: damage, startup, active, recovery, reach, hitbox/hurtbox interaction, cancel rules, stun, knockback. No hidden differences due to size/mesh/animation. Unique visuals are allowed; actual gameplay collision is canonical.
3. **Only special move behavior/data and audiovisual identity differ between fighters.** Special moves may contain temporary motion as an explicit skill effect, but not change default walk/jump/normal stats outside skill state.
4. 2.5D plane: horizontal X; locked depth Y=0; vertical Z. Automatic facing; shared side-on camera. Stage ends symmetric.
5. Intended combat logical step 60 Hz. Render and animation timing cannot be the authority for hit frames. Do not promise cross-device determinism without tests.
6. Local Windows 1v1, one arena, two original characters, offline only. Online, rollback, story and commercial publishing are out of scope. No copyrighted Mortal Kombat characters, models, music, logos or signature assets.
7. Preserve the existing `.codex/config.toml`, Unreal MCP settings, and functioning editor state. UE5.9 is a preview; inspect local engine and tools instead of assuming APIs.

## Engineering rules

- C++: reusable authoritative gameplay; Data Assets: tunables and per-fighter special definitions; Blueprint/Animation Blueprint: animation/presentation/assignment; Python/MCP: editor automation.
- Discrete combat events and gameplay values may be frame-indexed; separate those from Unreal render tick. Do not hand-edit binary `.uasset` files or assume a mesh/animation exists without importing it.
- One source of truth per value; avoid copied defaults across A/B and duplicate table definitions. Maintain any source JSON/CSV to engine import traceability.
- Never delete or overwrite user assets, plugins, settings, files, or save data without explicit approval; prepare a reversible checkpoint and audit impact. No paid API calls, asset purchases, or undisclosed uploads.
- Prefer UE 5.9 supported systems and verify local signatures; discover Unreal MCP tool schema dynamically; call editor-changing MCP tools sequentially. Do not expose MCP outside loopback.
- Keep Content tree and code organized and consistently named. Source-control binary assets with appropriate Git LFS where available. Never commit `Binaries`, `Intermediate`, `Saved`, `DerivedDataCache`, tokens/keys, or build outputs.

## Required workflow for EVERY TASK

1. Read current project state, active task, previous report and dependencies; disclose blockers.
2. Brief plan: files and assets that will change + how they will be tested.
3. Save checkpoint; implement **only** task scope.
4. Build using real Windows Unreal toolchain when applicable; perform available unit/automation and PIE checks. Mark unperformed tests **NOT RUN**, not PASS. Screenshot/record in-game observable result if possible.
5. Write `reports/TASK_###_RESULT.md` containing observed version, changes, commands, pass/fail/not-run checks, evidence paths, risks, rollback guidance, and next task ID. Update `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` only with verified facts.
6. **STOP**. Wait for explicit next task ID. Do not run subsequent tasks automatically.

## If documentation conflicts

Priority: (1) this `AGENTS.md` for workflow and invariants, (2) `docs/08_DECISIONS_AND_OPEN_QUESTIONS.md` approved decisions, (3) `docs/01_VISION_AND_GDD.md`, (4) `docs/02_COMBAT_RULES.md`, (5) active task, (6) other docs. Report contradictions instead of inventing compromises.

## Optional task completion

T052 cinematic finishers may be marked `SKIPPED_OPTIONAL_APPROVED` only after explicit user approval and a factual T052 report. A dependent T053 may then proceed. This is not a PASS for finished cinematics.
