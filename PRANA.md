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

Use the public [ZhenhaoH/robotic](https://github.com/ZhenhaoH/robotic) packaging
fork on `zhhuang/feat/robot-policy-public`. Its committed `rai` submodule URL and
gitlink select the extension from this fork. Initialize submodules at their
recorded commits; no local submodule override or patch application is needed.
After changing RAI, advance that gitlink and then the consuming project's pinned
source commits together. Native build products and Python environments stay
outside Git.

The initial extension has passed static patch checks only. Native compilation,
binding tests and Engine execution have not run. GitHub Actions is disabled to
prevent imported workflows from running before runtime validation is authorized.
