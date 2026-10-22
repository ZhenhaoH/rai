# RAI LGP Python extension

This public fork preserves the history of
[MarcToussaint/rai](https://github.com/MarcToussaint/rai), based on
`28576e01e0896fc880833632b2e00251022c5d0a`. The upstream MIT license and copyright
remain in `LICENSE`.

The downstream adds Python action-constraint callbacks and bounded LGP search,
status and cancellation for Prana RobotPolicy (`ROBOT_POLICY_LGP_API == 1`).
Native FOL/AStar, LGP and KOMO remain responsible for planning. Agent/Engine
adapters live in Workspace, outside this repository.

The extension lives on `zhhuang/feat/robot-policy-public`; the upstream `master`
branch is retained. Merge upstream updates deliberately and review the native
API before advancing the selected commit. Use `origin` for ZhenhaoH/rai and a
read-only `upstream` remote for MarcToussaint/rai. There is no automatic sync.

Use the upstream [robotic](https://github.com/MarcToussaint/robotic) packaging
repository at `61647f20466786ebd7eca8c67b91e0939185d104`. Before building, explicitly
point its `rai` submodule at this fork and check out a fixed extension commit.
Record both commits in the consuming project's source manifest; the packaging
repository's original gitlink still records the upstream RAI commit. No robotic
fork is required. Native build products and Python environments stay outside Git.

The initial extension has passed static patch checks only. Native compilation,
binding tests and Engine execution have not run. GitHub Actions is disabled to
prevent imported workflows from running before runtime validation is authorized.
