# Test plan — executable proof not mere claims

## Universal reporting

Each test is `PASS`, `FAIL`, or `NOT RUN`. Differentiate C++ compile, editor asset import, PIE behavior, gamepad physical test, automation tests, package exe test and art acceptance. Logs/screenshots must be actual files and linked by path in report. Visual checking by an AI model does not replace user playtesting.

## Environment G0

- MCP read queries (previously user-confirmed), reversible write check if permitted, project/module audit.
- Real Windows Development Editor C++ compilation using installed UE toolchain; load map; PIE in current engine; save/restore baseline.
- `.gitignore` safety and saved local checkpoint; no secret files, project kept working.

## Movement G1

- Two fighter objects spawn at symmetric positions, oriented toward each other, movement X only, Y constant; stage boundaries symmetric.
- Equal movement and jump measures for A/B using same data; same acceleration, forward/back rules; both react only to own input.
- Crouch/jump state cleanup, body collision/spacing, facing reversal when necessary; ensure no split screen.
- Keyboard P1 + physical P2 device when available; otherwise mark manual P2 check `NOT RUN` and test dummy path separately.

## Combat G2

- Both fighter definitions share references for HP/physics and normal-move assets; edit of shared normal affects both.
- For all normals: identical startup/active/recovery and damage; symmetric mirrored hit positions; no attack hits more than once per move instance.
- State transitions when hit interrupts attack; world-space damage direction flips with facing; bounds and crossovers; same-frame trade case.
- Rendering at distinct FPS targets (if machine permits) does not change authoritative integer combat frames.

## Match G3

- Standing/crouching guard high/mid/low/overhead matrix; no guard during prohibited states.
- Input buffers expire and cannot attack during recovery/stun; documented chain obeys exact cancel window.
- KO triggers once, time-out draws resolved symmetrically, round resets health/states and effects, first to two round wins completes match, rematch resets.
- HUD shows authoritative health, timer and round wins; pause/resume follows freeze clock policy.

## Specials G4

- Exactly two unique specials per fighter; temporary movement/attack boxes from skill cannot alter shared default stats.
- Projectile hits once / expires / respects guard, lunge doesn't leave stage/plane, area hazard only active during its scheduled frames.
- No leaked actors/particles/cooldowns across round restart; A/B baseline parity tests still pass after all special work.

## Art G5/G6

- Approved mesh matches front/side/back sheet and original design. Skeleton and animation retarget produce clean joints, no Y drift, no obvious foot sliding or costume clipping.
- Visual attack cues correspond to simulation-active windows, not the other way around. Readable contrast in final arena at common viewing scale.
- Health/timer readable at target resolution; VFX and shake have accessible intensity; asset provenance recorded.

## Shipping G7

- Fresh package builds for Windows, launches without editor, loads correct menu/stage, accepts real 2-player controls, plays multiple matches without stuck states.
- Target test on user's own PC for smooth 60 FPS in gameplay (benchmark must report actual GPU/CPU/settings). No assumed guarantee.
- Document all licenses, credits, known bugs and remaining non-goals. Save reports and screenshot evidence.
