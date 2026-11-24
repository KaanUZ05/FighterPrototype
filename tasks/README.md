# Tasks: 59 isolated task files, 8 phases

Each task is a **standalone Codex request**, not a continuous autopilot run. Order from T001 to T059 without skipping unverified dependencies. The authoritative list is `docs/06_ROADMAP.md`; machine-readable registry/status is `tasks/TASK_STATUS.csv`.

`tasks/phase_00/` ... `tasks/phase_07/`: detailed one-task prompts. Task files specify delivery, actual pass/fail criteria, and when human signoff is required.

**Old starter pack task files `tasks/001_CONNECTIVITY_AND_BASELINE.md`, `tasks/002_GREYBOX_MOVEMENT.md`, `tasks/003_SHARED_NORMAL_COMBAT.md` are deprecated.** Do not use them if they remain in the project folder; all new tasks are prefixed T001-T059 under phases.

**Human control:** user explicitly authorizes EACH next task. Successful MCP connection does not mean C++ build verified.
