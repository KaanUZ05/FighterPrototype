# Decisions, provisional seeds, and creative approval gates

## LOCKED by user / validated project status

- 2.5D Mortal Kombat-*style* original fighting game in Unreal Engine 5.9; VS Code + Codex + working Unreal MCP connection.
- **Baseline equal across characters**: movement, speed/accel/jump, body boxes, normal attack power/frame data/reach/behavior; only special moves and visuals may vary.
- First version 2 original fighters, one stage, Windows local versus, data-driven reusable system, AI-led development with user review.
- Live editor reported `FighterPrototype`, UE `5.9.0` build `60738873`, active `/Game/ThirdPerson/Lvl_ThirdPerson`; MCP read-only query reported 72 actors. **No build/PIE success evidence yet.**

## PROVISIONAL defaults chosen to unblock coding

- HP 1000; forward/back 450/340 cm/s universally; target jump apex 140 cm; 60 Hz combat; 99-second round; best-of-three; four normal attacks; no meter; two specials each.
- Keyboard P1, gamepad P2 (or dummy until physical gamepad is available), same-screen one camera.
- Dark cinematic *stylized realism* with readable silhouettes; original fantasy/tech aesthetic. Temporary greybox fighters will be identical mannequins or simple capsules.
- Four sample specials: A lunge/short burst; B projectile/telegraphed area attack; **these are mechanical placeholders, not final chosen identities**.
- One final short original cinematic finisher per fighter is stretch scope; only after combat passes. No explicit gore requirement.

## ASK FOR USER APPROVAL AT THE PHASE GATE (not during initial tasks)

| Decision | Earliest task/gate | Safe temporary default |
|---|---|---|
| Exact fighter names, world story, costume themes | T038 art bible / G5 | FighterA and FighterB placeholders |
| Final four unique specials and visual language | T037 special gate, before special-themed art | Simple Lunge/Arc/Bolt/Sigil debug shapes |
| Final concept sheets and 3D appearances | T039/T040 | capsules/UE mannequin |
| Arena mood, palette and key props | T046 | readable greybox stage |
| Original finisher tone/choreography | T052 | omit finisher until approved |
| Any paid asset/model API and content license | before any payment/upload | use available UE basics only |
| New platforms, online, story, commercial release | after G7 | no |

## How to revise

User approves an explicit edit in writing. Codex records it here, updates GDD + seed data/tests if affected, and states which task checks need rerunning. Do not quietly encode assumptions as irreversible design choices.
