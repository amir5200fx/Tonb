# Changelog
All notable changes to this project will be documented in this file.
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and the project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Highlights
- **Root-level foundation layer introduced for Tonb**: Added a new reusable `foundation/` module tree, ported and adapted from GeoForge, to provide shared infrastructure for future shells and tooling.
- **Shell-oriented infrastructure established**: Added reusable command-line, workspace, logging, export, failure, configuration, and utility foundations intended to support upcoming root-level shells such as `shell/cad2d`.
- **GeoForge foundations adapted to Tonb conventions**: Integrated the imported foundation code into Tonb-native include paths, namespaces, module macros, and build wiring.
- **Root-level cad2d shell module introduced**: Added the first dedicated `shell/cad2d` module outside `libs/`, establishing the build, public-header, and target foundation for the future AutoCAD-like `cad2d` shell.
- **cad2d shell module scaffolded for future expansion**: Added the initial `ShellApp` façade, Tonb-native shell export macros, placeholder shell runtime headers, and basic smoke-test coverage so later session, tokenisation, UI, and command infrastructure can be developed on a real module boundary.
- **cad2d shell session model introduced**: Added the first real `ShellSession` orchestration root for `shell/cad2d`, with named curve-store and shape domains, active-context tracking, shape-to-curve-store binding, primary selection, runtime flags, and deterministic status/reset support.
- **Session foundation prepared for CAD-like growth**: The new shell session model is intentionally structured to support future selection-set, alias-handle, journaling, and undo/redo style workflows without embedding CAD algorithms into the shell state layer.
- **cad2d command registry and dispatch foundation introduced**: Added the first real hierarchical command infrastructure for `shell/cad2d`, with deterministic path lookup, alias support, structured command dispatch, and explicit invalid-command failures.
- **Command infrastructure aligned with future shell growth**: The new registry/context/args model is designed to support later command families, help integration, tokenisation, and AutoCAD-like command workflows without collapsing everything into ad hoc handlers.

### Added
- **Root-level Tonb foundation module**:
    - new `foundation/` tree added at the repository root as a reusable infrastructure layer outside `libs/` and `shell/`
    - new `TonbFoundation` target with `Tonb::Foundation` alias
    - integrated root CMake wiring for building and installing the foundation module
- **CLI foundation infrastructure**:
    - command path representation
    - command registry support
    - command specification/help metadata support
    - help rendering utilities
    - parse utilities for command-line style token handling
    - text-table support for structured terminal output
- **Workspace foundation infrastructure**:
    - workspace model and standard workspace-area handling
    - default workspace path support
    - workspace lifecycle utilities
    - workspace persistence helpers
- **Logging foundation infrastructure**:
    - structured logger support
    - log context support
    - Tonb foundation log macros
    - console, text-file, NDJSON, and buffered sink support
- **Failure and export foundation infrastructure**:
    - failure-code, severity, diagnostics, and exception support
    - export bundle models and bundle-writing support
    - export naming, path, and profile utilities
    - integrity-oriented export support carried over from the GeoForge foundation set
- **Configuration and utility foundation infrastructure**:
    - configuration helpers adapted into the Tonb foundation layer
    - shared utility support required by the imported foundation modules
- **Tonb-native foundation module header**:
    - `tonb/foundation/module.hxx` added for export/import control and shared module visibility handling
- **Foundation module documentation**:
    - README documenting the role of the new foundation layer as the reusable basis for future Tonb shells and tooling
- **Root-level cad2d shell module**:
    - new `shell/` root module tree with dedicated `shell/cad2d` module outside `libs/`
    - new `TonbCAD2dShell` target with `Tonb::CAD2dShell` alias
    - root and module-level CMake wiring for building and installing the new shell module
- **Tonb-native cad2d shell public headers**:
    - `tonb/cad2d/shell/module.hxx` for shell-module export/import control
    - initial public `ShellApp` façade in `tonb/cad2d/shell/shell_app.hxx`
    - initial placeholder headers for future shell subsystems:
        - `shell_session.hxx`
        - `shell_tokenise.hxx`
        - `shell_ui.hxx`
- **Initial cad2d shell implementation and smoke testing**:
    - minimal `ShellApp` implementation for the new shell module
    - basic smoke-test coverage verifying shell target linkage and public header availability
- **cad2d shell session model**:
    - first real `ShellSession` state root for the new shell module
    - first-class session ownership for named curve stores and named topology shapes
    - active curve-store tracking and active shape tracking
    - explicit shape-to-curve-store binding support to keep shell workflows practical while preserving the clean topo/geom split in `cad2d`
    - minimal primary-selection model as the first step toward future CAD-like selection workflows
    - shell runtime flags stored as part of session state
    - deterministic session `reset()` and `status()` support
- **cad2d shell session test coverage**:
    - regression tests for deterministic session creation and reset behavior
    - regression tests for active shape and active curve-store assignment
    - regression tests for storing and reporting shape-to-curve-store bindings
- **cad2d command registry and dispatch infrastructure**:
    - hierarchical command path model for shell command registration and lookup
    - structured command argument model for dispatch-time token handling
    - command execution context carrying session access and dispatch-facing state
    - command node and registry types for clean command-family registration
    - deterministic longest-prefix or equivalent path matching for nested commands
    - alias support for command-path dispatch
    - explicit unknown-command failure behavior
    - deterministic rejection of conflicting alias or command registrations
- **cad2d command infrastructure test coverage**:
    - regression tests for simple command dispatch
    - regression tests for nested command dispatch
    - regression tests for clean unknown-command failure
    - regression tests for alias dispatch behavior
    - regression tests ensuring ambiguous or conflicting command registration is prevented deterministically

### Changed
- **Foundation namespace and include adaptation**:
    - ported GeoForge foundation headers and sources into Tonb-native `tonb/foundation/...` include paths
    - adapted imported code to Tonb-style namespaces and module structure
- **Tonb build integration**:
    - aligned the imported foundation layer with Tonb build, target, and install conventions
    - extended the root build to include the new `shell/cad2d` module
    - extended the shell module build to compile and test the first real session subsystem
    - extended the shell module build further to compile and test the first real command infrastructure subsystem
- **Bundle integrity implementation cleanup**:
    - removed an unnecessary OpenSSL include during the Tonb port of the foundation bundle-integrity implementation

### Notes
- This foundation work is intended to support upcoming root-level shell development, beginning with `shell/cad2d`.
- The imported GeoForge foundations were integrated as a Tonb-native root-level infrastructure layer rather than being embedded directly into a product-specific shell.
- The current integration keeps the module structure broad and reusable so it can later be split further if needed.
- This completes **Issue 1 — Root-level cad2d Shell Module** from the cad2d shell roadmap.
- This also completes **Issue 2 — Shell Session Model** from the cad2d shell roadmap.
- This also completes **Issue 3 — Command Registry and Dispatch Infrastructure** from the cad2d shell roadmap.
- The current `shell/cad2d` state now includes a real session foundation and command dispatch foundation, but help rendering, tokenisation, and higher-level command families remain future issues built on top of this boundary.

---

## [0.21.0] - 2026-05-08

### Highlights
- **Public 2D intersection result model introduced for cad2d**: Added the first public, kernel-agnostic result types for 2D curve-curve intersection queries, covering isolated points, tangent points, overlap intervals, and explicit unsupported or failure outcomes.
- **Initial bounded span intersection API introduced**: Added the first real bounded curve-span intersection API in `cad2d/geom`, with deterministic segment-segment support and initial representative support for segment-arc and arc-arc cases.
- **Half-edge span intersection utility introduced**: Added the first `cad2d/algo` bridge utility that resolves half-edge curve bindings from `CurveStore` and forwards bounded-span queries through the geometry intersection layer.
- **Curve intersections foundation advanced**: Milestone vNext+4 now includes the public result model, the first bounded-span solver layer, and the first topology-level half-edge intersection integration utility, without changing the public intersection report format.

### Added
- **Public intersection result types in `cad2d/geom`**:
    - result model for isolated point intersections with parameters on both input curves
    - result model for overlap or coincident intervals with parameter spans on both input curves
    - explicit tangent-point classification where relevant
    - explicit unsupported and failure outcomes with stable diagnostics
- **Intersection result diagnostics**:
    - stable, documented representation of empty successful queries versus unsupported or failure cases
    - kernel-agnostic public API surface even when later implementations are backed internally by OCCT
- **Intersection result test coverage**:
    - regression test for line-line style crossing represented as one point with parameters on both curves
    - regression test for disjoint query represented as a successful empty intersection result
    - regression test for coincident overlapping segment-style query represented as overlap interval rather than ambiguous point output
    - regression test for tangent-point classification and explicit unsupported or failure diagnostics
- **Bounded span intersection API in `cad2d/geom`**:
    - public `intersect_bounded_spans(...)` entry point for bounded 2D curve-span queries
    - deterministic manual segment-segment intersection path
    - initial circular support for representative segment-arc and arc-arc cases
    - explicit `Result` failures for unsupported span combinations
- **Initial bounded-span intersection test coverage**:
    - orthogonal segment-segment intersection test
    - non-overlapping collinear segment test returning no point intersection
    - representative segment-arc intersection test
    - representative arc-arc intersection test
- **Half-edge span intersection utility in `cad2d/algo`**:
    - public half-edge-aware intersection entry point that accepts two topology half-edges and a `geom::CurveStore`
    - topology-to-geometry bridge that resolves half-edge curve bindings and delegates bounded-span queries to `geom::intersect_bounded_spans(...)`
    - half-edge-aware point and overlap result items carrying half-edge ids and per-span parameters on both inputs
    - explicit failure reporting for null half-edges, missing curve bindings, and invalid curve ids
- **Half-edge intersection test coverage**:
    - crossing half-edges test returning the expected point intersection in half-edge/span terms
    - invalid curve-id test failing cleanly through `Result`
    - disjoint-span test verifying that identical underlying geometry with separated half-edge parameter spans returns no intersections

### Changed
- **Intersection result usability**:
    - added stable short public aliases such as `IntersectionResult`, `IntersectionPoint`, and `IntersectionOverlap` on top of the documented `CurveIntersection*` model
- **Curve intersection implementation alignment**:
    - aligned bounded-span solver code and tests with the actual public variant-based intersection result model
    - removed assumptions about separate `points` and `overlaps` containers in favour of the documented `items` result representation

### Notes
- This continues **Milestone vNext+4 — Curve Intersections Foundation**.
- Issue 8 covers the **public result-type and API model**.
- Issue 9 adds the **initial bounded-span intersection solver**, with segment-first support and representative arc cases.
- Issue 10 adds the **topology-level half-edge span intersection bridge** in `cad2d/algo`, linking `topo::HalfEdge` and `geom::CurveStore` to the existing bounded-span geometry solver.

---

## [0.20.0] - 2026-05-07

### Highlights
- **Geometry consistency validation completed for cad2d**: Finished the full vNext geometry-validation milestone, including vertex–curve agreement checks, curve-domain and degeneracy validation, optional shape-level geometry validation, and standardised diagnostic behaviour.
- **Validation diagnostics strengthened**: Geometry validation now uses stable error-code mappings and consistent message prefixes, with targeted tests locking down representative diagnostic cases.
- **Project-wide feature-config propagation introduced**: Added a generated configuration-header path so build-time feature macros such as `TONB_WITH_OCCT` can be propagated consistently through the codebase and tests.
- **Wire geometric length utility introduced**: Added a geometry-aware wire-length algorithm in `cad2d/algo`, backed by a public robust arc-length integration API in `numerics`.
- **Polygonal face area and orientation utilities introduced**: Added the first face-level geometric utilities in `cad2d/algo`, including signed area, loop orientation classification, and standard face-orientation helpers for segment-only polygonal faces.

### Added
- **Geometry-aware half-edge validation**:
    - validation of stored `curve_id`, `u0`, and `u1` against the referenced curve in `geom::CurveStore`
    - endpoint agreement checks between evaluated curve points and half-edge start/end vertices
    - curve-domain checks with tolerance-aware parameter validation
    - degenerate-span detection for invalid zero-length parameter ranges
    - orientation/parameter-order consistency checks for forward and reversed half-edges
- **Shape-level optional geometry validation**:
    - geometry checks can now be enabled from `validate::check_shape(...)` without changing topology-only behaviour
    - missing or invalid curve bindings are now caught at shape-validation level when geometry validation is enabled
- **Geometry validation diagnostic tests**:
    - message-prefix and error-code assertions for representative geometry-validation failures
    - validator-side out-of-domain tests using direct half-edge construction for corrupted/imported states
    - strengthened regression coverage for endpoint mismatch, missing curve, domain violation, degeneracy, and orientation handling
- **Generated Tonb config header path**:
    - build-generated project configuration header for propagating feature macros such as `TONB_WITH_OCCT`
    - unified feature-flag usage between library code and tests without local source-level macro definitions
- **Public numerics arc-length integration API**:
    - adaptive arc-length integration for planar parametric curves exposed as a public numerics facility
    - deterministic, tolerance-driven refinement with explicit work limits and convergence metadata
    - intended for reuse by higher-level CAD and geometry algorithms
- **Wire length utility in `cad2d/algo`**:
    - geometric wire-length computation by summing per-half-edge arc lengths from `curve_id`, `u0`, and `u1`
    - explicit failure reporting for missing curves, invalid parameters, non-finite spans, and unsupported unbounded domains
- **Wire-length test coverage**:
    - regression test verifying that a square built from segment edges returns a total length of approximately 4 within tolerance
- **Polygonal face area and orientation utilities in `cad2d/algo`**:
    - signed polygonal area computation for wires and faces using segment-only geometric spans
    - loop orientation classification based on signed-area sign
    - face-level orientation checks using the documented convention of outer CCW and holes CW
    - face-orientation normalisation helpers based on reversing wires through existing twin half-edges
    - explicit rejection of non-linear spans for the current polygon-only milestone scope
- **Face-area test coverage**:
    - regression test verifying that a unit square face returns signed area ≈ 1
    - regression test verifying that a hole subtracts correctly from the outer face area

### Changed
- **cad2d validation flow**:
    - geometry validation is now treated as a first-class extension of the validation layer rather than only a builder-side safeguard
    - manually created, imported, or corrupted half-edge states can now be rejected by validators even if builders would have prevented them at construction time
- **Geometry validation diagnostics**:
    - standardised message prefix for geometry-validation failures
    - stable mapping of representative geometry failures onto existing `ErrorCode` categories
- **Test configuration discipline**:
    - tests now rely on configured build-time feature propagation instead of ad hoc local macro definitions for OCCT-enabled coverage
- **Numerical integration layering**:
    - robust arc-length integration is now exposed from `numerics` as a public reusable API rather than being embedded privately inside `cad2d`
- **cad2d algorithm layering**:
    - wire-length computation is implemented as an algorithm-layer consumer of topology, geometry storage, and public numerics utilities
    - polygonal face-area computation is implemented as an algorithm-layer consumer of topology, geometry storage, and existing orientation conventions

### Notes
- This completes **Milestone vNext — Geometry Consistency Validation (Option B)**.
- This also completes **Milestone vNext+2 — Wire Geometry Utilities**, introducing the first wire-level geometric utility.
- This also completes **Milestone vNext+3 — Face Geometry Basics**, introducing signed-area and orientation utilities for segment-only polygonal faces.
- The next planned milestone is **vNext+4 — Curve Intersections Foundation**.

## [0.19.0] - 2025-08-21
### Highlights
- **Build system migration:** Switched from Visual Studio solutions to **CMake** as the primary build system.
- **Legacy fallback:** The previous VS-based codebase is kept under **`Legacy/`** and remains runnable as before.

### Added
- **New logger** (structured, context-aware) with sinks:
    - `ConsoleSink` (human-friendly), `JsonFileSink` (NDJSON), and `BufferedTextSink` (flush/rewind behaviour similar to the old logger).
    - `withContext`, levels, structured fields, basic rate limiting, and task integration.
- **Versioning header**: generated `tonb/system/version.hpp` exposing:
    - `version_semver()` → numeric SemVer (X.Y.Z)
    - `version_full()` → `git describe` string (e.g., `v0.19.0-…`)
- **Serialization niceties**:
    - Optional **type tags** (`type_tag`) after the wire header to self-describe files.
    - **Registry** + `read_tagged_file_any<Base>` dynamic dispatch.
    - `peek_file_type()` to read just header + tag without payload.
- **Demos**:
    - `logger_demo` showcasing sinks, contexts, scope timing, flush/rewind, and task logging.
    - Common runtime output dir for all demos; RPATH set so demos run from build/install trees without `LD_LIBRARY_PATH`.

### Changed
- **Library naming on Linux**:
    - `.so` **VERSION** now uses the numeric SemVer core (e.g., `0.19.0`).
    - `.so` **SOVERSION** follows the SemVer **major** (still `0` while pre-1.0).
- **CMake install layout**:
    - Libraries under `lib/`, headers under `include/tonb/…`, and a `tonb` CMake package under `lib/cmake/tonb/`.
- **Windows developer UX**:
    - Post-build step (optional) copies **runtime DLLs** next to each demo EXE.
    - Demos can share one `demos/bin/<Config>/` folder to avoid per-target duplication.

### Fixed
- **Linux linking**:
    - “undefined reference to vtable …” resolved by adding out-of-line virtual destructors and compiling vtable **anchor** TU(s).
    - Visibility/exports adjusted so shared builds link cleanly across toolchains.

### Deprecated
- The **old logger API** is considered legacy. Prefer the new structured logger.
    - The previous implementation is still available under `Legacy/` for continuity.

### Notes for packagers / integrators
- Use CMake package config:
  ```cmake
  find_package(tonb CONFIG REQUIRED)
  target_link_libraries(your_target PRIVATE tonb::system)
  ```
