# cad2d Roadmap: Next Milestones Toward an AutoCAD-like 2D CAD Core

## Purpose

This roadmap defines the next practical development steps for `cad2d` after the completion of:

- topology foundation
- geometry-aware validation
- wire geometric length
- polygonal face signed area and orientation utilities

The long-term goal is to move toward a 2D CAD core with capabilities similar in spirit to AutoCAD for sketching and region construction, while preserving the current disciplined architecture:

- `topo`: topology ownership and invariants
- `build`: controlled construction and mutation helpers
- `validate`: explicit correctness checks
- `geom`: geometry storage and evaluation
- `algo`: higher-level geometric/topological algorithms
- `numerics`: reusable numerical building blocks

This roadmap is intentionally staged so that later high-level editing and boolean tools are built on robust geometric decomposition primitives rather than ad hoc special cases.

---

# Milestone: vNext+4 --- Curve Intersections Foundation

## Goal

Introduce a robust and explicit intersection layer for 2D curve spans. This milestone provides the geometric basis for trimming, splitting, fragmentation, region extraction, and eventually boolean operations.

---

## Issue 8 --- Public 2D Intersection Result Types

**Priority:** High  
**Domain:** cad2d/geom  
**Type:** Feature / Foundation

### Description

Define public result types for 2D curve-curve intersection queries.

These types should represent:

- isolated point intersections
- overlap / coincident intervals
- tangent intersections where relevant
- failure / unsupported cases with explicit diagnostics

The API should remain kernel-agnostic at the `cad2d` surface even if internally backed by OCCT.

### Acceptance Criteria

- Public intersection result types exist with full documentation.
- Result model distinguishes point intersections from overlapping spans.
- Results include parameters on both input curves.
- Diagnostics are explicit and stable.

### Tests

- line-line crossing returns one point with parameters on both curves
- disjoint line-line returns no intersections
- coincident overlapping segments produce overlap result rather than ambiguous point set

---

## Issue 9 --- Segment-First Curve-Curve Intersection API

**Priority:** High  
**Domain:** cad2d/geom  
**Type:** Feature

### Description

Implement an initial intersection API for bounded curve spans, starting with segment-first support.

Recommended initial support:

- segment-segment
- segment-arc
- arc-arc

General curve support can be added later without changing the public result model.

### Acceptance Criteria

- Bounded span intersection API exists.
- Segment-segment is robust and deterministic.
- Returned parameters are consistent with span direction.
- Unsupported combinations fail explicitly via `Result`.

### Tests

- orthogonal segments intersect correctly
- non-overlapping collinear segments return no point intersection
- segment-arc and arc-arc representative cases pass

---

## Issue 10 --- HalfEdge Span Intersection Utility

**Priority:** High  
**Domain:** cad2d/algo  
**Type:** Feature / Integration

### Description

Add a utility that intersects two topology half-edge spans by resolving their curves from `CurveStore` and calling the geometry intersection API.

This should bridge topology and geometry cleanly without embedding topology assumptions into `geom`.

### Acceptance Criteria

- Takes two half-edges and a `CurveStore`
- Returns intersection results in edge/span terms
- Rejects invalid or missing curve bindings
- Deterministic output ordering

### Tests

- crossing half-edges return correct intersection
- invalid curve id fails cleanly
- same geometry with disjoint parameter spans returns no intersection

---

# Milestone: vNext+5 --- Edge and Wire Fragmentation

## Goal

Make it possible to split topology entities at geometric parameters and build fragment-level representations. This is the minimum required substrate for trim, break, and booleans.

---

## Issue 11 --- Edge Split Operation

**Priority:** High  
**Domain:** cad2d/topo + build  
**Type:** Feature / Controlled Refactor

### Description

Introduce a controlled split operation for a first-class `topo::Edge` at a parameter value.

The operation should:

- create a new vertex at the split point
- split both half-edges consistently
- preserve edge ownership and twin invariants
- keep curve bindings consistent

### Acceptance Criteria

- Splitting one edge yields two valid edges
- Twin and owner invariants remain valid
- New parameter spans are consistent and non-degenerate

### Tests

- segment edge split at midpoint yields two valid child edges
- splitting near an endpoint is rejected by tolerance rules
- edge validation passes for both resulting edges

---

## Issue 12 --- Wire Split and Fragment Extraction

**Priority:** High  
**Domain:** cad2d/algo + build  
**Type:** Feature

### Description

Build utilities for splitting a wire at one or more edge parameters and extracting fragment sequences.

This milestone should support:

- ordered split points per edge
- fragment half-edge sequences
- deterministic fragment ordering

### Acceptance Criteria

- Wire can be fragmented at one or more geometric split locations
- Fragment ordering is deterministic
- Boundary continuity is preserved within each fragment

### Tests

- splitting a rectangular wire at one edge yields expected fragment counts
- multiple splits on one edge are handled in sorted parameter order
- invalid split requests fail explicitly

---

## Issue 13 --- Planar Arrangement Fragment Graph

**Priority:** Medium  
**Domain:** cad2d/algo  
**Type:** Feature / Foundation

### Description

Construct a fragment graph from intersecting edges/wires.

This graph should represent:

- fragment vertices
- directed fragment edges
- adjacency and incidence needed for loop extraction

This is the topological decomposition layer booleans will later depend on.

### Acceptance Criteria

- Graph can be built deterministically from fragmented inputs
- Connectivity is explicit and documented
- Debug/inspection utilities exist for testing

### Tests

- two intersecting rectangles produce expected fragment graph topology
- graph connectivity is stable across repeated runs

---

# Milestone: vNext+6 --- Sketch Region Construction

## Goal

Build region extraction from fragmented sketches so closed loops and faces can be created automatically from intersecting input geometry.

---

## Issue 14 --- Loop Extraction from Fragment Graph

**Priority:** High  
**Domain:** cad2d/algo  
**Type:** Feature

### Description

Extract closed loops from the planar fragment graph.

The extractor should identify bounded cycles and produce them in a deterministic order suitable for later face construction.

### Acceptance Criteria

- Closed loops can be extracted from fragmented planar arrangements
- Loop orientation is classified deterministically
- Duplicate/redundant loops are filtered consistently

### Tests

- intersecting rectangles yield expected bounded loops
- simple single rectangle yields one loop
- open sketches yield no closed loop result

---

## Issue 15 --- Face Construction from Sketch Regions

**Priority:** High  
**Domain:** cad2d/build + algo  
**Type:** Feature / Integration

### Description

Create faces automatically from extracted loops.

This should classify:

- outer loops
- hole loops

using the signed-area/orientation utilities already added earlier.

### Acceptance Criteria

- Valid faces can be built from loop sets
- Hole assignment is correct for nested regions
- Face orientation can be normalised to standard convention

### Tests

- single rectangle sketch becomes one face
- nested loops become outer face plus hole
- invalid ambiguous nesting fails explicitly

---

## Issue 16 --- Region Validation Utilities

**Priority:** Medium  
**Domain:** cad2d/validate + algo  
**Type:** Feature

### Description

Add validation helpers for sketch-derived regions and loop sets before final face construction.

### Acceptance Criteria

- Region diagnostics are explicit
- Invalid nesting or inconsistent orientation is detected
- Validation is deterministic

### Tests

- invalid hole nesting is caught
- duplicate loops are rejected
- ambiguous region assignment fails cleanly

---

# Milestone: vNext+7 --- Sketch Editing Operations

## Goal

Introduce user-facing CAD editing operations on top of the new intersection and fragmentation foundations.

---

## Issue 17 --- Trim Operation

**Priority:** High  
**Domain:** cad2d/algo  
**Type:** Feature

### Description

Add a trim operation for bounded curve/edge spans based on intersection and splitting results.

### Acceptance Criteria

- Can trim a span against another selected boundary
- Resulting topology is valid
- Builder/validator integration remains explicit

### Tests

- trim a segment against another crossing segment
- trimming outside valid span fails
- resulting edge set validates

---

## Issue 18 --- Break / Split-at-Point Operation

**Priority:** High  
**Domain:** cad2d/algo + build  
**Type:** Feature

### Description

Expose a user-level operation that breaks a curve/edge/wire at a specified point or parameter.

### Acceptance Criteria

- Produces valid fragments
- Works with deterministic tolerance rules
- Reuses underlying edge split functionality

### Tests

- break segment at midpoint yields two fragments
- break at endpoint is rejected or no-op by rule
- resulting topology validates

---

## Issue 19 --- Join / Coalesce Operation

**Priority:** Medium  
**Domain:** cad2d/algo  
**Type:** Feature

### Description

Join collinear/compatible neighbouring spans into larger spans when geometrically and topologically legal.

### Acceptance Criteria

- Compatible segment fragments can be merged
- Invalid joins are rejected
- Resulting topology remains valid

### Tests

- adjacent collinear segments join successfully
- angular mismatch prevents join
- merged result validates

---

# Milestone: vNext+8 --- 2D Boolean Operators

## Goal

Introduce robust 2D region booleans after the arrangement and region-construction foundations are in place.

---

## Issue 20 --- Face Boolean Classification Rules

**Priority:** High  
**Domain:** cad2d/algo  
**Type:** Feature / Foundation

### Description

Define and implement inside/outside classification rules for fragmented regions under:

- union
- intersection
- subtraction

### Acceptance Criteria

- Classification is deterministic
- Rules are documented clearly
- Works on polygonal baseline first

### Tests

- rectangle union classification correct
- rectangle subtraction classification correct
- rectangle intersection classification correct

---

## Issue 21 --- Polygonal Boolean Operators

**Priority:** High  
**Domain:** cad2d/algo + build  
**Type:** Feature

### Description

Implement boolean operations for polygonal faces using the region-construction pipeline.

### Acceptance Criteria

- Union works for overlapping rectangles
- Intersection works for overlapping rectangles
- Subtraction works for hole-producing cases
- Resulting faces validate and orient correctly

### Tests

- overlapping rectangles union/intersection/subtraction pass
- subtraction can create hole when appropriate
- disjoint cases behave predictably

---

## Issue 22 --- Boolean Result Reconstruction

**Priority:** Medium  
**Domain:** cad2d/build + algo  
**Type:** Feature

### Description

Reconstruct final face topology from classified result regions, preserving standard orientation conventions and explicit diagnostics.

### Acceptance Criteria

- Result faces are valid cad2d faces
- Outer/hole relationships are reconstructed correctly
- Validation passes on boolean outputs

### Tests

- boolean results validate structurally and geometrically
- multiple-region outputs are handled deterministically

---

# Milestone: vNext+9 --- Drafting and Convenience Geometry

## Goal

Add high-value drafting operations expected from a practical 2D CAD system.

---

## Issue 23 --- Offset Curves / Offset Wires

**Priority:** Medium  
**Domain:** cad2d/algo + geom  
**Type:** Feature

### Description

Generate offsets for segment-first and arc-first geometries with explicit failure paths for unsupported or unstable cases.

### Acceptance Criteria

- segment wire offsets work reliably
- corner handling is documented
- invalid self-intersection cases fail explicitly or produce diagnostic output

### Tests

- rectangle offset outward and inward
- invalid offset on too-small feature fails cleanly

---

## Issue 24 --- Fillet Operation

**Priority:** Medium  
**Domain:** cad2d/algo + build  
**Type:** Feature

### Description

Insert tangent arc fillets between compatible segment pairs.

### Acceptance Criteria

- creates valid tangent connection
- trims/extends adjacent spans as needed
- resulting topology validates

### Tests

- right-angle segment pair fillet succeeds
- impossible radius fails explicitly

---

## Issue 25 --- Chamfer Operation

**Priority:** Medium  
**Domain:** cad2d/algo + build  
**Type:** Feature

### Description

Insert chamfer spans between compatible segment pairs.

### Acceptance Criteria

- valid chamfer span created
- adjacent spans updated consistently
- result validates

### Tests

- simple corner chamfer succeeds
- oversized chamfer fails explicitly

---

# Milestone: vNext+10 --- User-Level CAD Workflows

## Goal

Move from low-level primitives toward the workflows expected from a practical sketching/CAD environment.

---

## Issue 26 --- Region Creation from User Sketches

**Priority:** High  
**Domain:** cad2d/algo + build  
**Type:** Feature / Workflow

### Description

Given an arbitrary user sketch set, detect valid closed regions and create faces automatically.

### Acceptance Criteria

- simple sketch collections produce faces automatically
- ambiguous/open sketches return clear diagnostics
- deterministic results

### Tests

- sketch with one rectangle produces one face
- sketch with nested loops produces hole
- open sketch produces no face

---

## Issue 27 --- Constraint-Friendly Topology Utilities

**Priority:** Medium  
**Domain:** cad2d/topo + algo  
**Type:** Feature / Future-proofing

### Description

Prepare topology utilities that will later support sketch constraints and parametric editing, without implementing a full solver yet.

### Acceptance Criteria

- stable references for editable spans are documented
- split/join/edit operations preserve usable identity where possible
- diagnostics for invalidated references are explicit

### Tests

- editing operations preserve expected identity rules
- invalidated references are detectable

---

## Issue 28 --- DXF-Oriented Sketch Export/Import Foundation

**Priority:** Medium  
**Domain:** cad2d/io + geom  
**Type:** Feature

### Description

Lay the foundation for importing/exporting practical 2D CAD sketches in a DXF-oriented way.

### Acceptance Criteria

- minimal line/arc export exists
- import/export mapping rules are documented
- geometry/topology reconstruction path is clear

### Tests

- exported simple sketch round-trips structurally
- unsupported entities fail explicitly

---

# Recommended Order of Execution

The recommended implementation order is:

1. **vNext+4** — intersections foundation  
2. **vNext+5** — edge and wire fragmentation  
3. **vNext+6** — sketch region construction  
4. **vNext+7** — editing operations  
5. **vNext+8** — polygonal booleans  
6. **vNext+9** — drafting operations  
7. **vNext+10** — workflow and exchange foundations  

This order is intentional:

- booleans should not be attempted before fragmentation and region extraction
- trim/break/join become much easier once splitting infrastructure exists
- drafting operations such as offset/fillet/chamfer are more reliable once the arrangement/editing pipeline is mature

---

# Strategic Notes

## Why not start with booleans immediately?

Boolean operators depend on a large amount of prior machinery:

- curve intersections
- robust splitting
- fragment graph construction
- loop extraction
- region classification
- face reconstruction

Attempting booleans before those pieces typically leads to brittle special-case code that must later be rewritten.

## What is realistically achievable?

An AutoCAD-like **2D CAD core** is realistically achievable if the project stays disciplined and incremental.

The practical target should be:

- robust 2D topology and geometry core
- sketch-to-region workflow
- editing operations
- polygonal and later curved booleans
- drafting-style operations
- file exchange foundations

This is a strong and realistic long-term direction for `cad2d`.

---

# Immediate Recommendation

The next actual implementation milestone should be:

## **Milestone: vNext+4 --- Curve Intersections Foundation**

That milestone unlocks everything that follows and is the correct next step after the current state of the library.
