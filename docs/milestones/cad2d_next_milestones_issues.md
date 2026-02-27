# Milestone: vNext --- Geometry Consistency Validation (Option B)

## Issue 1 --- Geometry-aware HalfEdge Validation: Vertex--Curve Agreement

**Priority:** Critical\
**Domain:** cad2d/validate + cad2d/geom\
**Type:** Feature / Correctness

### Description

Add a geometry-aware validator that checks whether a `HalfEdge`'s
`(curve_id, u0, u1)` is consistent with its `start/end` vertex
positions.

Validation must: - fetch curve from `geom::CurveStore` by `curve_id` -
evaluate curve at `u0` and `u1` - compare evaluated points to
`Vertex::position()` - fail if distance exceeds tolerance

Must remain OCCT-free at the cad2d layer (only use `cad2d::Curve`
wrapper APIs).

### Proposed API

-   `validate::check_halfedge_geometry(const std::shared_ptr<topo::HalfEdge>& e, const geom::CurveStore& store, const topo::Tolerance& tol) -> topo::Result<void>`
    or equivalent, but must be callable from
    `validate::check_shape(...)` later.

### Acceptance Criteria

-   If `curve_id==0` or missing in store → validation fails with clear
    message.
-   If `|C(u0) - Vstart| > tol` or `|C(u1) - Vend| > tol` → fails with
    clear message.
-   Passes for correct models built via geometry-aware builder.
-   Error messages include: half-edge id, curve id, u0/u1, and measured
    distances.

### Tests

-   ✅ passes for a valid edge created with `create_from_curve`
-   ❌ fails when end vertex is moved away
-   ❌ fails when curve_id is missing in the store

------------------------------------------------------------------------

## Issue 2 --- Geometry-aware HalfEdge Validation: Curve Domain and Degeneracy

**Priority:** Critical\
**Domain:** cad2d/validate\
**Type:** Feature / Correctness

### Description

Add validation checks for: - `u0/u1` inside curve domain (with small
epsilon) - non-degenerate span (`|u1-u0| > eps`) - orientation
consistency (forward expects `u0 < u1`, reversed expects `u0 > u1`)

These checks must be performed in the validator (not only in builders),
so imported or manually edited models are still validated.

### Acceptance Criteria

-   Domain check uses curve's domain from wrapper and allows small
    epsilon overshoot.
-   Degenerate span triggers a dedicated error code (`degenerate` or
    equivalent).
-   Orientation mismatch triggers `invalid_input` (or equivalent).
-   Messages include curve domain and offending params.

### Tests

-   ❌ out-of-domain u0/u1 fails
-   ❌ u0==u1 fails as degenerate
-   ❌ wrong ordering for orientation fails

------------------------------------------------------------------------

## Issue 3 --- Integrate Geometry Validation into ShapeChecks (Optional Flag)

**Priority:** High\
**Domain:** cad2d/validate\
**Type:** Feature / Integration

### Description

Extend `validate::check_shape(...)` to optionally run geometry-aware
validation, without changing existing pure-topology behaviour.

Add a new option, e.g.: - `ShapeCheckOptions::check_geometry = false` by
default

When enabled, shape validation should: - validate each half-edge against
`CurveStore` - treat missing curves as failures

### Acceptance Criteria

-   Existing topology-only test suite passes unchanged with default
    options.
-   When `check_geometry=true`, geometry errors are caught at shape
    level.
-   Deterministic traversal order is preserved.

### Tests

-   ✅ shape built with geometry curves passes with
    `check_geometry=true`
-   ❌ shape with missing curve_id fails only when `check_geometry=true`

------------------------------------------------------------------------

## Issue 4 --- Add Geometry Validation Error Codes and Message Convention

**Priority:** Medium\
**Domain:** cad2d/topo/result + validate\
**Type:** Maintenance / Quality

### Description

Standardise error codes and message formatting for geometry validation
failures.

Add/confirm error codes for: - geometry_missing_curve -
geometry_endpoint_mismatch - geometry_domain_violation -
geometry_degenerate_span - geometry_orientation_mismatch

If you do not want to expand enum now, map these to existing codes but
enforce a consistent message prefix.

### Acceptance Criteria

-   Geometry validator failures have consistent prefix and include
    ids/parameters.
-   Tests assert error code category (where stable) and message
    substring.

### Tests

-   Minimal: one test that asserts code mapping for endpoint mismatch
    and domain violation.

------------------------------------------------------------------------

# Milestone: vNext+1 --- Edge Abstraction (Topology Usability)

## Issue 5 --- Introduce `topo::Edge` as Twin HalfEdge Owner

**Priority:** High\
**Domain:** cad2d/topo + build\
**Type:** Feature / Refactor (controlled)

### Description

Introduce a new topology entity `Edge` that owns two half-edges and
enforces twin symmetry as a first-class invariant.

Edge responsibilities: - create/own both directed half-edges - guarantee
`ab->twin == ba` and `ba->twin == ab` - ensure both share the same
`curve_id` and consistent parameter span

HalfEdge continues to exist (wire traversal), but "edge identity"
becomes explicit.

### Acceptance Criteria

-   New `Edge` entity exists with full documentation.
-   Builders can create an `Edge` from a curve.
-   Validators treat edge invariants as stronger than incidental
    half-edge invariants.

### Tests

-   ✅ edge creation yields valid twin pair
-   ❌ breaking twin fails edge validation

------------------------------------------------------------------------

# Milestone: vNext+2 --- Wire Geometry Utilities

## Issue 6 --- Wire Geometric Length Utility

**Priority:** Medium\
**Domain:** cad2d/algo (or cad2d/geom)\
**Type:** Feature

### Description

Compute wire length by summing edge lengths using curve evaluation and
(u0,u1) spans.

-   Use numerical integration policy (simple adaptive sampling is fine
    initially)
-   Must be deterministic and tolerance-driven

### Acceptance Criteria

-   Works for segment wires (exact or near-exact).
-   Provides stable result for bounded curves.
-   Clear behaviour on unbounded curves (error or skip with Result).

### Tests

-   Square of segments returns length ≈ 4 within tolerance.

------------------------------------------------------------------------

# Milestone: vNext+3 --- Face Geometry Basics

## Issue 7 --- Face Signed Area and Orientation Utilities

**Priority:** Medium\
**Domain:** cad2d/algo\
**Type:** Feature

### Description

Compute signed area for a face (outer minus holes) and enforce
orientation conventions: - outer CCW, holes CW (or vice versa, but
document it)

### Acceptance Criteria

-   Provides signed area for polygonal (segment-only) faces.
-   Returns deterministic output.
-   Orientation helper can detect and optionally normalise.

### Tests

-   Square face signed area ≈ 1
-   Hole subtracts area correctly
