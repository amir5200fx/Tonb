# Changelog
All notable changes to this project will be documented in this file.
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and the project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Highlights
- **Public 2D intersection result model introduced for cad2d**: Added the first public, kernel-agnostic result types for 2D curve-curve intersection queries, covering isolated points, tangent points, overlap intervals, and explicit unsupported/failure outcomes.
- **Curve intersections foundation started**: Began Milestone vNext+4 by defining the public API surface that later intersection implementations will return without forcing future redesign of the result model.

### Added
- **Public intersection result types in `cad2d/geom`**:
    - result model for isolated point intersections with parameters on both input curves
    - result model for overlap / coincident intervals with parameter spans on both input curves
    - explicit tangent-point classification where relevant
    - explicit unsupported and failure outcomes with stable diagnostics
- **Intersection result diagnostics**:
    - stable, documented representation of empty successful queries versus unsupported/failure cases
    - kernel-agnostic public API surface even when future implementations are backed internally by OCCT
- **Intersection result test coverage**:
    - regression test for line-line style crossing represented as one point with parameters on both curves
    - regression test for disjoint query represented as a successful empty intersection result
    - regression test for coincident overlapping segment-style query represented as overlap interval rather than ambiguous point output
    - regression test for tangent-point classification and explicit unsupported/failure diagnostics

### Notes
- This begins **Milestone vNext+4 — Curve Intersections Foundation**.
- Issue 8 currently covers the **public result-type and API model only**. The actual bounded span intersection implementation remains the next step.

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
