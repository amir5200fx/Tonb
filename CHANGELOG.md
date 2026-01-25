# Changelog
All notable changes to this project will be documented in this file.
The format follows [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and the project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Highlights
- **New cad2d topology core**: Introduced a fully re-designed, OCCT-free 2D topology layer with builders, validators, and comprehensive test coverage.
- **Validation-first architecture**: Topology invariants are now explicitly checked via a dedicated validation module, enabling early error detection and safer future geometry integration.
- **cad2d geometry binding introduced**: Added the first geometry integration layer via curve storage and geometry-aware half-edge construction, without exposing OCCT in topology.

### Added
- **cad2d topology entities** (pure topology, no geometry kernel dependency):
  - `Vertex`, `HalfEdge`, `Wire`, `Face`, and `Shape`
  - Stable `Id` system and tolerance-aware point handling
- **Builder layer (`cad2d/build`)**:
  - `VartexBuilder`, `HalfEdgeBuilder`, `WireBuilder`, `FaceBuilder`
  - Defensive construction using `Result<T>` with explicit error reporting
- **Validation layer (`cad2d/validate`)**:
  - Half-edge checks (endpoints, twin symmetry, next/prev consistency)
  - Wire checks (boundary integrity, continuity, closure, next/prev vs boundary order)
  - Face checks (outer/holes validity, edge disjointness)
  - Shape checks (registry integrity and full topology validation)
- **Result-based error handling**:
  - Explicit `Result<T>` / `Result<void>` pattern across builders and validators
  - Structured error codes and descriptive diagnostics
- **GoogleTest test suite** for cad2d topology:
  - Deterministic unit tests covering half-edges, wires, faces, and full shapes
  - Negative test intentionally breaking invariants to verify validators
  - Shared test helpers for building canonical square faces
- **Geometry binding layer (`cad2d/geom`)**:
  - `CurveStore` for owning and indexing `cad2d::Curve` objects behind stable topology ids
  - Clear separation between pure topology and geometry-backed construction
- **Geometry-aware builders**:
  - Half-edge creation from geometry curves with validated parameter ranges and orientation 
  - Twin half-edge creation bound to a single stored curve
- **Geometry tests**:
  - GoogleTest coverage for curve storage, retrieval, and geometry-aware half-edge construction
  - Tests remain backend-safe (no OCCT leakage into cad2d topology)

### Changed
- **cad2d architecture**:
  - Clear separation between topology, builders, validation, and future geometry binding
  - Topology is now independent of OCCT; geometry will be introduced in a higher layer
- **Internal API discipline**:
  - Consistent use of `std::shared_ptr` ownership and explicit `weak_ptr` links
  - Deterministic validation order for reproducible diagnostics and tests
- **cad2d build flow**:
  - half-edge construction can now be driven directly from geometry curves while preserving topology purity.

### Notes
- This release establishes a **stable foundation** for upcoming geometry binding (`cad2d/geom`) and higher-level algorithms.
- Geometry-dependent operations beyond curve binding (e.g., intersections, containment, trimming validation) are intentionally deferred and will build on the new geometry-aware topology foundation.

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
