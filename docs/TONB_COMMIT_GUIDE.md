# Tonb Commit Decision Chart (Linux Workflow)

This document summarises commit message conventions for the Tonb project, following Conventional Commits, tailored for your rebuild and development workflow on Linux.

---

## 1. Commit Types

| Type     | When to use                                                                 |
|----------|-----------------------------------------------------------------------------|
| feat     | Add a new API, class, option, or CLI flag                                   |
| fix      | Correct wrong behaviour (bug fix)                                           |
| refactor | Change code structure without changing behaviour                            |
| style    | Formatting only (wrap lines, whitespace, clang-format)                     |
| perf     | Improve performance without changing the API                               |
| test     | Add or modify tests                                                         |
| build    | Change build system / dependencies / CMake / toolchains                    |
| ci       | Change CI/CD configuration                                                  |
| docs     | Documentation only (README, Doxygen, Sphinx, etc.)                          |
| chore    | Release bumps, dependency updates, or other project maintenance tasks      |
| revert   | Undo a previous commit                                                      |

---

## 2. Picking a Scope

Scope should be the top-level module or main area changed:
- `system`, `base`, `geometry`, `cad`, `io`, `io/vtk`, `occt`, `cmake`, `docs`, `tests`, `deps`

---

## 3. Examples

**feat**
```
feat(geometry): add Curve2d wrapper with OCCT and null backends

- OCCT impl: D0/D1, degree, trim via Geom2d_TrimmedCurve
- Null impl throws on eval, compiles without OCCT
```

**fix**
```
fix(io/vtk): guard against empty point set in quad writer

- Return false early with log message instead of segfault
```

**style**
```
style(cad): wrap long line in surface.cpp for readability
```

**build**
```
build(cmake): add surface.{hxx,occt.cxx,null.cxx} to TonbGeometry target
```

---

## 4. Breaking Changes

If the change breaks compatibility:
```
feat(geometry): rename Pnt3d::distance to DistTo

BREAKING CHANGE: Pnt3d::distance removed; use DistTo instead.
```

---

## 5. Quick Decision Flow

1. Adds user-visible capability? → **feat**
2. Fixes wrong behaviour? → **fix**
3. No behaviour change, just structure? → **refactor**
4. Only formatting? → **style**
5. Faster, same result? → **perf**
6. Only CMake/deps/tooling? → **build** / **ci**
7. Only docs? → **docs**
8. Only tests? → **test**
9. Version bump / chores? → **chore**
10. Undo commit? → **revert**

---

## 6. Tips

- Keep subject ≤ 72 chars, imperative mood (“add”, “fix”, “update”)
- One commit type per commit; split unrelated changes
- Don’t mix formatting and logic — separate `style` commits
- Avoid file paths in subject; details go in the body
