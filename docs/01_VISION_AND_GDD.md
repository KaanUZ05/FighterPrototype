# GAME DESIGN DOCUMENT (GDD) — FighterPrototype

**Version:** 1.0 / 2026-11-25 | **Status:** APPROVED BASELINE + flagged provisional creative decisions | **Document owner:** Human creative director | **Implementation:** Codex + Unreal Engine 5.9.0 C++/MCP

> The user explicitly requires that all characters share movement, basic damage and frame mechanics. Only special moves, appearance, animation styling and VFX/SFX distinguish them. Do not reinterpret the roster as heavy/slower versus agile/faster archetypes.

## 1. High concept

`FighterPrototype` is the working name of an original **2.5D, side-view, dark cinematic fighting game**, mechanically inspired by the accessibility/clarity of modern 1v1 fighters. Two visually distinct combatants confront one another on a single 3D arena while movement and collision are constrained to a 2D fighting plane. A strong local two-player versus experience comes before art polish. The project's second goal is to prove an agent-led Unreal pipeline that can be repeated for a third fighter without rewriting shared combat.

**Audience:** Players seeking readable, precise 1v1 local fighting. **Session:** short round-based match. **Target:** Windows desktop prototype / demo; no commercial promises. **Art:** original dark-fantasy / technology-mysticism hybrid as a *provisional* moodboard, stylized realism and readable silhouettes, no licensed franchise assets. Exact world, character names, color motifs and lore are **UNDECIDED**.

## 2. Core design pillars

1. **Competitive symmetry:** the same basic toolkit and underlying move definitions for every character, not merely roughly similar performance.
2. **Distinct specials:** two initial special moves per character with different tactical uses; skill differentiation must not silently alter baseline movement/normal attacks.
3. **Responsive, inspectable combat:** logical 60 Hz combat state, explicit startup/active/recovery, input buffering, clear hit/guard feedback and debug box visualization.
4. **Cinematic presentation without obscuring combat:** compelling lighting/animations and purposeful effects; combat readability takes priority over spectacle.
5. **Incremental, verifiable automation:** build and test after each task; visual assets only after greybox combat passes.

## 3. Game modes and scope

**Vertical slice includes:** local offline 1v1 (same screen, no split view), 2 characters, 1 arena, shared normals, 2 specials per character, keyboard/controller input with practical routing, health/timer/best-of-three, rematch, basic character selection, original sounds/VFX, and an optional short **non-gory** cinematic finisher per character once approved (target scope, never block gameplay gate).

**Not in first release:** online matchmaking, rollback, campaign, arcade ladder, voice acting, custom character creation, cosmetics shop, brutal gore, destructible environments, 10+ fighters, console ports, commercial publishing.

**Future/extension ideas only:** practice mode, CPU AI, advanced throw/juggle, additional specials, tutorials, online play. No implementation unless separately approved.

## 4. Match flow

1. Launch -> minimal main menu (`Versus`, `Quit`) -> character selection (can start with auto-assigned Fighter A/B and introduce a selection UI later).
2. Both fighters spawn symmetrically with mirror-normalized orientation, full health and no held inputs.
3. Pre-round countdown `3, 2, 1, FIGHT` (exact style provisional), then both controls enabled.
4. Fight with shared locomotion/normals, guards, and character-special attacks until KO or timer end.
5. Winner gains one round; if health equal at time-out, implement a documented symmetrical draw resolution (initially draw/replay round, no arbitrary player bias).
6. First fighter to **2 round wins** wins match; show winner and allow rematch/back to character selection.
7. On reset clear move instances, inputs, VFX cues, resources, cooldowns and temporary projectiles before re-enabling control.

**Starting settings (PROVISIONAL):** max HP `1000`; 99-second round clock; best-of-3 rounds; logical combat at 60 frames/sec; no explicit resource meter in MVP; configurable pause in local play.

## 5. Controls and movement

- Fighting plane: world X horizontal; world Y locked at 0; Z vertical. No stage depth roaming. Match camera frames both fighters from the side; no player-controlled camera.
- Two players independently control one fighter. Phase 1 starts P1 keyboard / P2 gamepad or controller mapping; if no second physical controller is available, use a test-harness-controlled training dummy **only for development**, never falsely claim real 2-player testing.
- Movement: forward/back relative to opponent, crouch, jump, return to neutral. Facing switches on permitted frame boundaries; combat boxes use canonical fighter-origin facing. Normal body collision prevents accidental passing-through. No unique character speed or jump stats.
- P1 placeholder bindings: `A/D` move; `W` jump; `S` crouch; `J` light punch; `K` heavy punch; `U` light kick; `I` heavy kick; `O` special 1; `P` special 2; `Esc` pause. Gamepad use d-pad/left stick plus four face buttons and two shoulders/triggers with a consistent mapping; rebinding later.
- Blocking: hold `away` from the opponent for standing guard; hold `down + away` for crouching guard (implemented after normals). Guard only if current state permits.

## 6. Fighters and parity contract

`FighterA` and `FighterB` are **technical slots**, not defined personalities or final names. Both reference the same `SharedFighterStats` and `SharedNormals` assets. Shared values include max health; ground acceleration, walk forward/back, jump and gravity; collision pushbox; normal attack timings/damage/hitboxes/knockback/hit/blockstun; input buffer; guard system; and hit/KO eligibility rules. Art rig proportions do not alter canonical combat boxes.

Different fighter art, idle style, sound, VFX and special attack animations are expected. Unique special moves may apply their *own* temporary dash, projectile, hazard or status effect only while that special executes. **Never implement a permanent heavy/slow versus agile/fast baseline.**

## 7. Base combat design

### Initial normal attacks (exact seed in `data/shared_normals.csv`)

Four grounded normals: light punch (`LP`), heavy punch (`HP`), light kick (`LK`), heavy kick (`HK`). Both characters use the same underlying definitions. The launch demo may add crouching/jumping normals **only after** these four are complete; such additions also use shared canonical data. Attack phases: `Startup -> Active -> Recovery` at 60 logical frames/sec.

### Hit resolution

- A move may hit the same opposing fighter once per attack instance unless explicitly flagged multi-hit.
- Hitbox-vs-hurtbox uses canonical gameplay collision independent of mesh; guard is checked using attack level and facing (standing blocks high/mid/overhead; crouching blocks low/mid, exact per-level table in combat spec).
- On valid hit, inflict damage and common hitstun/knockback/hitstop; on guard, apply reduced/no damage (default 0 chip for normals) and blockstun. Mutual contact may trade if both attacks become active at the same logical frame.
- KO occurs when health reaches zero and resolves only once per round; disable further damage events. Input during recovery may buffer but may activate only on legal frames/cancel windows.

### Combos

Phase 3 starts with a **small approved universal chain** (initially LP -> LK -> HP, exact cancellation windows provisional); no complex infinite chains. Combo counter is presentation derived from combat-hit events. Jumping, crouching, airborne juggle and throw interactions beyond the gate are deliberately restricted initially.

## 8. Special move identity (provisional mechanical seeds, **NOT final creative approval**)

- `FighterA / Special1`: **Lunge Strike**, a short directional attack with skill-specific displacement and a single hit. Its displacement does not change ordinary movement speed.
- `FighterA / Special2`: **Arc Pulse**, a short-range burst focused on spacing / pressure.
- `FighterB / Special1`: **Energy Bolt**, a slow visible projectile intended to control horizontal space.
- `FighterB / Special2`: **Delayed Sigil**, a short-duration placed area attack with a clear telegraph.

These are implementation-friendly placeholders to prove extensible systems, **not locked character lore, elements, costumes or effects**. Before expensive art production the user chooses the final four specials, keeping their tactical roles if useful. Specials share dispatch, input, cooldown conventions and rules, but data/behavior can differ; numeric balancing done after they work.

### Combat resources (MVP)

No meter initially. Specials may use universal cooldowns per move and explicit recovery, same cooldown policy for all skills. Final costs/timers decided after playtesting; don't hard-code into a character Blueprint.

## 9. Stage, camera and visual language

One symmetric fighting arena, visible floor and boundaries; fixed side-on framing, optional small dynamic camera zoom/pan only if framing stays readable. Temporary greybox geometry first. Final stage: one original dark environment, cinematic light, fog/particles placed behind the character silhouette. Distinct accent colors may communicate player/skill identity, but do not overuse color alone to signal important cues. No background actors should cover hitboxes or fighter feet.

## 10. Art and animation requirements

**Critical asset principle:** concept art reference -> single 3D character mesh -> rig/skeleton -> reusable animation set -> retarget / per-fighter special animation -> Unreal, NOT a new AI image for every punch frame.

Each fighter needs a locked style sheet with front/side/back views, costume material callouts, proportions and color palette; only then 3D production. Prefer compatible rigs and shared baseline moves. MVP animation list: idle, forward/back walk, crouch, jump/land, LP/HP/LK/HK, guard, hitreact, knockdown, victory, 2 specials. Add transition polish late. Preserve root position/fighting-plane discipline and inspect hands, shoulders, knees, feet. Formal asset acceptance and license provenance in `docs/04_ASSET_AND_ANIMATION_PIPELINE.md`.

AI image-to-3D or rigging output needs human inspection; never claim production quality because an import succeeded. Do not purchase/download copyrighted or paid third-party assets without authorization.

## 11. Audio, VFX, UI, accessibility

- HUD: symmetric life bars, timer, wins, subtle hit/combo cues, round callouts. No UI behavior may override authoritative match state.
- Effects: punch contact sparks, blocked attack effect distinct from hit, special-specific cues, simple hitstop/camera shake with capped duration and no uncontrolled camera rotation.
- Audio: original/licensed impact sounds, guard sounds, UI cues, stage ambience and a modest music track where licensed. Respect volume controls and clarity of combat audio.
- Options: adjustable master/effects/music levels, pause, basic keyboard/controller mapping reference, readable color contrast, avoid light-sensitive excessive flashing.

## 12. Definition of a successful vertical slice

- Windows build launches from packaged executable without editor.
- Local 1v1 complete match works: two independently controlled players, 2 fighters, 1 stage, four shared normals, 2 specials each, guard/hit reactions, round clock, health, KO, best-of-3, menu/rematch.
- Parity automation confirms shared baseline stats and normal definitions with **no per-fighter gameplay data drift**.
- Fighting feels responsive on target hardware (owner playtest), while visuals are readable and original.
- Two consistent rigged models render cleanly and their baseline attacks land on the same logical frames.
- Core integration tests, repeated PIE smoke tests and build packaging are recorded with real logs. `NOT RUN` must remain `NOT RUN`.

## 13. Quality risks / mitigation

- **Preview UE API instability:** task-scale changes, checkpoints, compile gates, stable APIs where possible.
- **AI-generated 3D flaws:** minimal clothes/hair complexity, model turnaround approval, re-rig/retopo fallback.
- **Two player input routing:** test early; explicit second controller gate, honest dummy fallback.
- **Combat 'looks right' but is unfair:** canonical boxes; hard parity tests; attack events notifies are visual only.
- **Agent over-scoping:** `AGENTS.md` one-task-at-a-time and reports after each task.
- **Overlarge game scope:** one arena, two fighters, no network, no long cinematic gore.

## 14. Approval / change management

Decisions classed `LOCKED` in `docs/08_DECISIONS_AND_OPEN_QUESTIONS.md` may not be changed by Codex. Provisional numeric seeds can be changed once through `data/` plus tests and a human-readable decision log. Creative choices (`FINAL_ART_STYLE`, `FIGHTER_DESIGNS`, `FINAL_SPECIALS`, `FINISHER_TONE`, `FINAL_GAME_NAME`) are approved by user at the appropriate task gate, not guessed by the agent. See `docs/06_ROADMAP.md`.
