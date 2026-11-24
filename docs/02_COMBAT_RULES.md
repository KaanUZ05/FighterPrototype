# Combat rules, data schema and parity contract — v2

## Fixed rules

- Both fighters start at 1000 HP and reference **the same** shared base stats object and normal-move data object. Validate both reference identity and numerical equality where possible.
- World X horizontal, world Y plane-locked to 0, world Z vertical. No model size-based reach differences.
- Attack startup/active/recovery, stun and input buffer counted in integer 60 Hz simulation frames. Combat time controls hit activation; animation follows it and notifies only visual/audio cues.
- Fight inputs interpreted relative to facing, including hold-back block. Combat state transitions resolved in one documented canonical order; prevent double-hit and repeated KO triggers.
- Input buffering limit 6 frames initially; not a license to ignore recovery. No active action in hitstun, blockstun, KO or illegal recovery unless shared cancel data allows it.

## Seed values — NOT an existing Unreal Data Asset

Values are in `data/combat_rules.json` and `data/shared_normals.csv`. Include provenance/import path when creating Unreal Data Assets. HP 1000; forward speed 450 cm/s; backward speed 340 cm/s; jump apex target 140 cm; horizontal acceleration 2200 cm/s²; body pushbox capsule radius 38 cm, halfheight 90 cm; input buffer 6 logical frames; target 60 combat frames/sec. The DIFFERENCE between forward and backward speeds applies universally to both fighters and does not break fighter parity.

| Normal | Startup | Active | Recovery | Damage | Hitstun | Blockstun | Range |
|---|---:|---:|---:|---:|---:|---:|---:|
| LP | 5 | 2 | 10 | 30 | 12 | 7 | 75 cm |
| HP | 11 | 3 | 17 | 65 | 17 | 11 | 90 cm |
| LK | 7 | 3 | 12 | 35 | 13 | 8 | 92 cm |
| HK | 13 | 3 | 19 | 70 | 18 | 12 | 115 cm |

Initial numbers are for a playable baseline; they are not Mortal Kombat data, nor balanced final production values.

## Guard and attack levels

| Attack level | Standing guard (back) | Crouching guard (down+back) |
|---|---|---|
| High | Block | Whiff if low profile/hurtbox excludes, else block |
| Mid | Block | Block |
| Low | Hit | Block |
| Overhead | Block | Hit |

Provisional normal moves: LP high, HP mid, LK mid, HK mid. Define profile/hurtbox effects explicitly before implementing crouching high evasion; initial crouch guard may block high for simplicity if canonical hitbox remains. Report final chosen handling, test both sides. Hold-back guard is not automatically allowed during other non-cancelable actions.

## Combat-frame algorithm contract

1. Snapshot P1/P2 inputs and facing-relative directions for logical frame N.
2. Advance/expire input buffers and timers; determine input legality.
3. Update state and controlled motion for both fighters; resolve stage bounds and shared pushboxes.
4. Advance attack move instances and active windows.
5. Resolve attacks against both fighters from the same frame snapshot; apply guard/hit or trade rules symmetrically.
6. Apply damage, hitstop, stun, knockback and visual/audio event queue. KO at zero HP once.
7. Advance round state/time and publish UI state after combat resolution.

This is a logical specification. Unreal CharacterMovement is not automatically deterministic or fixed-tick; implement a tested combat-step clock and do not claim bitwise determinism across PCs. A large render frame may require bounded catch-up. Pause/alt-tab need explicit, consistent policy.

## Shared/canonical hitboxes

Single move data asset drives local-space attack boxes, normalized to facing and fighter origin. Hitbox height/dimensions are not read from animation bone bounds. No multiple damage applications per move instance unless specifically multi-hit. Testing includes boundary clamp, mirror positions, facing reversal, crouch, jump and simultaneous attack trades.

## Combo rules

First universal chain suggestion `LP -> LK -> HP` with cancel windows defined in a later shared combo data table and identical for both. Queue commands in frame order; avoid arbitrary spam/infinite cancels. Extra air/crouch normals are added as shared entries if approved.

## Specials

One `SpecialMoveDefinition` for each fighter/slot with explicit startup, active, recovery, cooldown, damage, hit type, scripted movement/projectile/hazard rules. These fields may differ between FighterA and FighterB. Baseline stats and normal move source **cannot** differ. Special seeds are proof-of-system placeholders; final art/gameplay identity needs user approval before art-intensive work.

## Testing

A/B same stat asset and normals asset, mirrored damage/range tests, 30/60/120 render FPS where feasible, hit only active frame(s), landing and dash state legality, guard low/overhead, simultaneous attacks, no damage twice, KO once, input buffer expiry, crossovers, resetting round. Flag manual-only checks separately.
