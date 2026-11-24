# Technical architecture — Unreal Engine 5.9 C++ / MCP

**Only design targets, not claims these types already exist.** Read project `Source/` and current Blueprints before adding anything. Use engine headers to resolve actual 5.9 API. Prefer small components over huge `AFighterCharacter` monolith. Build each task.

## Layers / responsibility

| Layer | Candidate UE type | Owns |
|---|---|---|
| Rules clock | `UCombatSimulationSubsystem` or `AFightGameState` fixed-step driver | integer combat frame counter, command snapshots, authoritative combat update |
| Fighter physical | `AFighterCharacter` based on `ACharacter` | plane confinement, body collision, facing, animation state bridge; shared movement stats reference |
| Per-fighter combat | `UCombatComponent` | move requests, buffered commands, move instance, states, hit/guard transitions |
| Data | `UFighterDefinition`, `USharedFighterStats`, `USharedNormals`, `USpecialMoveDefinition` as Data Assets/structs | canonical values, visual assets, per-fighter specials |
| Match | `AFightGameMode`/`AFightGameState` | two spawns, round result, timer, win score, reset, first-to-two match ending |
| Input | `AFightPlayerController`, Enhanced Input contexts | P1/P2 separate local players, facing-relative commands, authoritative input submission |
| Camera | `AFightCameraActor` (or dedicated camera component) | side-on same-screen framing and stage-bound constraints |
| Presentation | Animation Blueprint + UMG + Niagara + SFX | visual/audio outputs derived from rule events, never authoritative damage |
| Tests | automation tests + functional test level | parity, round rules, deterministic scripted inputs, packaging smoke |

## Critical integration constraints

1. ThirdPerson template is only a starting level. Keep original `/Game/ThirdPerson/Lvl_ThirdPerson` intact until dedicated test stage works. Set maps/Gamemode carefully; do not destructively replace user content.
2. Scene convention: X moves horizontally, Y locked at zero, Z is vertical. Unreal camera looks along Y with only X/Z tracking. Plane constraint/locking must be verified against root motion, knockback and teleport-like skills.
3. Source of truth for 4 normal attacks is one common Data Asset, shared by both definitions. A fighter variant cannot fork normal data. Visual animation references may differ but attacks are gameplay-identical.
4. Hitboxes may use transient box math/overlap in a controlled trace/test; never couple damage decisions to frame-timing of animation events. Use canonical collision geometry and test boundaries.
5. Fighter abilities should be data + small clear behavior implementations (e.g. lunge/projectile/area attack), not an enormous speculative effects framework.
6. Input: Enhanced Input Action + Mapping Context for each local player. On a single PC, keyboard/gamepad routing can require explicit project settings; verify with an actual second controller or label NOT RUN. Do not spawn a second local player until the input flow is audited; ensure no split-screen by design.
7. For fixed combat frames, isolate logical combat simulation from frame-rate-variable engine/visual Tick. CharacterMovement/physics should be sampled/mediated with documented integration. Repeatable tests on the current machine do not automatically prove network determinism.
8. A task may introduce an Unreal feature only after its predecessor; never implement polished character art in Phase 0–3.

## Proposed directory layout (created incrementally)

```text
Source/FighterPrototype/        # C++ gameplay classes/modules as verified against existing project
Content/Fight/Maps/             # TestStage / ProductionStage
Content/Fight/Core/             # shared stats, normals, combat data
Content/Fight/Characters/A/     # character A mesh, data, animation, special FX
Content/Fight/Characters/B/     # character B mesh, data, animation, special FX
Content/Fight/Input/            # input assets, contexts
Content/Fight/UI/               # HUD and menus
Content/Fight/Effects/          # shared sound and Niagara
Content/Fight/Tests/            # in-editor debug/functional test assets
Scripts/                        # controlled Unreal Python/import helpers where supported
reports/                        # real evidence, logs, task reports
```

## Build / tooling

- Use Unreal Build Tool on locally installed engine; discover installed engine location, solution/projects and Windows MSVC version. Do not invent a compile command without locating executable paths.
- Code changes via VS Code; C++ class/module names and build.cs changes must match existing module.
- Unreal editor asset operations use **verified** MCP tools or editor Python/Blueprint tools; do not guess tool names. Operations against one editor serialized.
- Git & Git LFS if available; respect project-local configuration and existing repo, no destructive git init/clean/reset without approval.
- Unit tests for pure gameplay math; Functional Testing / PIE for state, and external packaged EXE smoke at release. Record actual executable paths/evidence.

## Example logical flow

`Enhanced Input -> PlayerInputBuffer -> Command Snapshot -> FixedCombatStep -> CharacterState/MoveInstance -> Hit/Hurt/Guard -> Health/RoundState -> Event Queue -> Animation/VFX/SFX/HUD`

Detailed handling decisions for KO/guard/trades in `docs/02_COMBAT_RULES.md`.
