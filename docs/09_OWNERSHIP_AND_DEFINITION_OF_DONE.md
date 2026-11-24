# Definition of Done, evidence and responsibilities

## Roles

- **User:** visual/art direction approvals, testing the feel of attacks and input, cost/legal approvals, deciding skills and final original characters.
- **Codex:** source architecture, C++/Blueprint integration, local Unreal MCP tooling, safe editor modifications, test automation, build, documentation, evidence reports.
- **Third-party model/3D tools:** optional asset generation only with user-approved rights/cost, never automatically trusted.

## Finish criteria per subtask

Implement smallest functional behavior, compile with local engine (when code touched), run automation/PIE (when runnable), no blocking regression, write report and mark tested statuses. Single source of truth maintained; avoid leaving blueprint assets in broken/transient state.

## Quality levels

- **Level 0:** spec only, no implementation.
- **Level 1:** files created, compile not yet proved.
- **Level 2:** compiled + minimal observed PIE behavior.
- **Level 3:** repeatable automation + human gameplay check for interactive features.
- **Level 4:** representative visual QA + packaged EXE + documentation.

A task may be `PARTIAL` at Level 1 if 2 was required; do not advance dependent tasks unless blockers resolved.
