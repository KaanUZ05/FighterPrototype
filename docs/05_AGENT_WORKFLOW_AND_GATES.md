# One-task-per-request Codex protocol

**Do not run the whole roadmap in one prompt.** This project succeeds by passing a verifiable sequence of small gates.

## Task lifecycle

1. User supplies task `T###` and says execute only it.
2. Codex reads `AGENTS.md`, GDD, current project status, and the exact task file; inspects current state and engine.
3. Codex names the files/assets to modify and confirms dependency tasks by real reports.
4. Codex takes a reversible save/checkpoint, implements, builds, runs tests/PIE where relevant.
5. Codex writes `reports/TASK_###_RESULT.md` with `PASS`, `FAIL`, `NOT RUN` per test and evidence (paths to logs/screenshots if actually generated), updates `docs/PROJECT_STATUS.md` and `tasks/TASK_STATUS.csv` without fabricated facts.
6. Codex **stops**. User reviews. A new message is required for every following task.

## Formatting required in every result

```text
Task ID / outcome: PASS, FAIL, BLOCKED or PARTIAL
State inspected (engine version, map, project, plugin, prior task evidence):
Changed files and assets:
Compile command and result:
Tests run + results:
PIE/visual observations:
Evidence files:
Tests NOT RUN and why:
Potential regressions/risks:
Rollback instruction:
Ready for next task? YES/NO; recommended task ID:
```

## Human milestone gates

- G0: user acknowledges repo/build baseline.
- G1: user confirms both players can operate/mannequins face each other.
- G2: user plays two minutes, assesses response and symmetry; parity tests pass.
- G3: user completes a best-of-three locally with guard, combo and HUD.
- G4: user approves special design roles/balance (can change skills before art).
- G5: user visually approves 2 final character turnarounds and rig/animation QA.
- G6: user approves combat readability, stage VFX/audio and final finisher scope.
- G7: user runs packaged Windows build and signs off final known limitations.

## Conflict and change control

Do not change locked rules due to convenience. If 5.9 API limitations make planned approach impossible, report cause and propose smallest equivalent change first. Never create an unrelated 'temporary' character system that makes parity impossible later. Any new paid service or web upload requires direct authorization.
