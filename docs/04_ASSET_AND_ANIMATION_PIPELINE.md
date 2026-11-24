# Art Bible / Asset and Animation Pipeline — controlled production

## Locked art constraints

- 2 original 3D characters in a stylized-realistic cinematic dark game; **no copying Mortal Kombat character names, logos, models, outfits, music, or trademarked moves**.
- Visual silhouette, costume, facial design and attack FX may differ. Base animation **timing and gameplay boxes** match canonical normal data; artwork cannot introduce reach or movement advantage.
- One coherent material palette and proportional scale, with clean silhouettes on the final stage.
- **Do not automatically generate a huge batch of images** or purchase image-to-3D services. Gain human approval on each design before rigging.

## Pipeline

1. **Art Bible gate**: palette, silhouette/readability targets, style references (original/appropriately licensed) and original world motifs. Human selects direction.
2. **Turnaround sheet** for each fighter: full-body front, 3/4, side, back; head close-up; costume material callouts; proportion reference, rig clearance. User approves `rev_01`.
3. **Create 3D mesh** from approved concept (AI-assisted if acceptable), using Blender cleanup/retopology/UV/material work as needed. Validate topology at shoulders, elbows, hips, knees and hands.
4. **Rig** both characters using a compatible skeleton template; ensure sufficient joint naming/retarget suitability. If models have different body shape, keep canonical physics hitboxes independent.
5. **Animation**: idle, fwd/back walk, crouch, jump/land, guard, hurt, knockdown, LP/HP/LK/HK, wins, two specials. Shared normals should reuse motions or have mirrored timing, and cinematic polish can be layered later.
6. **Import into UE5.9** using tested FBX/GLB pipeline; retarget with IK Rig/Retargeter where applicable. Verify scale (cm), X-facing orientation, root motion Y constraint, foot sliding, lighting and animation blend transitions.
7. **Asset register** records source, prompt, generator/tool version, license/right-to-use, cost, approval revision, import path and provenance.
8. **QA** two light setups and three camera distances, four attacks each character, root-motion drift, stage clipping, repeated punch cycles, hands/feet contact, original design consistency.

## Quality gates

- Same canonical final costume in all views, no missing fingers/eyes/rig collapse, no severe texture stretching, no obvious knee/elbow popping, no foot sliding beyond tolerances set in art QA.
- Original production mesh/texture files stored safely. Unreal import success is necessary but not sufficient.
- Animated attacks line up with exact simulated active frames or use intentionally adjusted playback rate.
- Attack VFX do not block leg/hand visibility; hitstop retains readability.

## Art decisions reserved for human

`FINAL_WORLD_STYLE`, `FIGHTER_A_LOOK`, `FIGHTER_B_LOOK`, `FIGHTER_NAMES`, `SPECIAL_VISUAL_LANGUAGE`, `FINISHER_CONCEPTS`. Provisional code-only attacks can proceed with simple primitives before approvals.

## Asset register schema

`AssetID, Character, Revision, GeneratorOrAuthor, SourceFiles, LicenseOrTerms, PaidCost, ApprovalStatus, UnrealAssetPath, QAStatus`

Use `data/asset_register.csv`. Unknown terms must be marked UNKNOWN and resolved before inclusion in packaged demo, not silently assumed free.
