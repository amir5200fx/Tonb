# cad2d Shell Roadmap: Toward an AutoCAD-like Command Shell

## Purpose

This roadmap defines the staged development plan for `Tonb/shell/cad2d`.

The goal is to build a command-driven 2D CAD shell on top of the existing `cad2d` library, with capabilities progressively moving toward the style and usability of commercial drafting systems such as AutoCAD, while preserving the disciplined Tonb architecture:

- `foundation`: reusable command-line, workspace, logging, and utility infrastructure
- `libs/cad2d/topo`: topology ownership and invariants
- `libs/cad2d/build`: controlled construction and mutation helpers
- `libs/cad2d/validate`: explicit correctness checks
- `libs/cad2d/geom`: geometry storage and evaluation
- `libs/cad2d/algo`: higher-level geometric and topological algorithms
- `shell/cad2d`: user-facing command shell, session model, and orchestration layer

This roadmap is intentionally staged so the shell evolves from a robust developer-facing command environment into a more practical sketching and drafting shell with workflows closer to professional CAD systems.

---

# Milestone: vNext Shell+0 --- Shell Foundation and Session Core

## Goal

Establish the reusable shell runtime, session model, and command/help infrastructure needed for all later CAD workflows.

---

## Issue 1 --- Root-level cad2d Shell Module

**Priority:** High  
**Domain:** `shell/cad2d`  
**Type:** Feature / Foundation

### Description

Create the root-level `shell/cad2d` module with Tonb-native build integration and public headers.

This module should be separated cleanly from `libs/cad2d` and depend on the new root-level `foundation/` infrastructure where appropriate.

### Acceptance Criteria

- `shell/cad2d` exists as a dedicated module outside `libs/`
- CMake target is integrated into the root build
- Public include layout is Tonb-native
- Shell module depends only on the required Tonb libraries and foundation modules

### Tests

- shell target configures and builds
- public headers install cleanly
- basic link test passes

---

## Issue 2 --- Shell Session Model

**Priority:** High  
**Domain:** `shell/cad2d/session`  
**Type:** Feature / Foundation

### Description

Design and implement the central shell session model for `cad2d`.

The session should own user-facing runtime state such as:

- named curve stores
- named shapes
- active shape
- active curve store
- shape-to-curve-store bindings
- primary selection
- shell runtime flags

The design must remain extensible for future CAD-like workflows such as selection sets, journaling, and undo/redo.

### Acceptance Criteria

- `ShellSession` exists as the orchestration root for shell state
- curve-store and shape domains are first-class session components
- active-context tracking is supported
- session reset and status queries exist
- session design leaves room for future history and selection growth

### Tests

- creating and resetting session state behaves deterministically
- active shape and active curve-store assignment works correctly
- shape-to-curve binding is stored and reported correctly

---

## Issue 3 --- Command Registry and Dispatch Infrastructure

**Priority:** High  
**Domain:** `shell/cad2d/command`  
**Type:** Feature / Foundation

### Description

Implement the shell command registry and dispatch model, using a structure similar in spirit to the iXFract shell and Tonb foundation CLI utilities.

The command system should support:

- hierarchical command paths
- deterministic lookup
- aliases where appropriate
- structured dispatch to command handlers

### Acceptance Criteria

- hierarchical registry exists
- longest-prefix or equivalent deterministic command matching works
- command handlers can be registered cleanly by family
- invalid commands fail with explicit diagnostics

### Tests

- simple commands dispatch correctly
- nested commands dispatch correctly
- unknown commands fail cleanly
- ambiguous resolution is prevented deterministically

---

## Issue 4 --- Help Registry and Help Rendering

**Priority:** High  
**Domain:** `shell/cad2d/help`  
**Type:** Feature / Foundation

### Description

Add a structured help subsystem with command specifications and user-facing help rendering.

This should be a separate metadata subsystem, not ad hoc strings embedded into command handlers.

### Acceptance Criteria

- command metadata model exists
- help registry exists separately from command dispatch
- command help can be rendered by path
- namespace listing is deterministic and readable

### Tests

- `help` lists top-level command groups
- `help <command...>` shows the correct command usage
- unknown command help fails cleanly

---

## Issue 5 --- Tokenisation and Parse Utilities

**Priority:** High  
**Domain:** `shell/cad2d`  
**Type:** Feature / Foundation

### Description

Implement shell tokenisation and basic parse helpers for command-line-style interaction.

The initial design should support:

- whitespace tokenisation
- quoted strings
- straightforward positional parsing

### Acceptance Criteria

- tokenisation is deterministic
- quoted strings are preserved correctly
- parse failures are explicit

### Tests

- simple command tokenises correctly
- quoted token remains intact
- malformed quoted input fails cleanly

---

## Issue 6 --- Core Shell Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Implement the first core shell commands:

- `help`
- `status`
- `reset`
- `quit` / `exit`

These commands establish the basic user interaction model.

### Acceptance Criteria

- core commands execute through the command registry
- `status` reports session state clearly
- `reset` clears session objects deterministically
- exit command sets runtime termination state cleanly

### Tests

- `status` reports empty session correctly
- `reset` clears existing objects
- exit command sets exit-requested state

---

# Milestone: vNext Shell+1 --- Construction, Inspection, and Validation Commands

## Goal

Expose the current `cad2d` capabilities through shell commands for creating geometry/topology, inspecting state, and validating model correctness.

---

## Issue 7 --- Curve Store Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Add commands for creating, listing, selecting, and inspecting curve stores.

Recommended initial commands:

- `curve store create <name>`
- `curve store list`
- `curve store use <name>`
- `curve store show <name>`

### Acceptance Criteria

- named curve stores can be created and listed
- active curve store can be set
- listing and inspection output is deterministic

### Tests

- creating one or more stores works
- duplicate store creation fails cleanly
- active store tracking works

---

## Issue 8 --- Basic Curve Construction Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Add commands for populating curve stores with supported geometric primitives.

Recommended initial commands:

- `curve add segment ...`
- `curve add arc ...`

The shell should expose stable, CAD-like creation workflows while delegating true geometry handling to `cad2d/geom`.

### Acceptance Criteria

- supported curves can be inserted into the active or named curve store
- curve IDs are reported deterministically
- duplicate or invalid IDs fail explicitly

### Tests

- adding a segment works
- adding an arc works
- duplicate curve insertion fails cleanly

---

## Issue 9 --- Shape and Topology Root Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Add commands for creating and listing topology roots.

Recommended initial commands:

- `shape create <name>`
- `shape list`
- `shape use <name>`
- `shape show <name>`
- `shape bind curves <shape> <curve-store>`

### Acceptance Criteria

- named shapes can be created and listed
- active shape can be set
- shape-to-curve-store binding works
- inspection output is deterministic

### Tests

- creating one or more shapes works
- duplicate shape names fail cleanly
- shape binding to a curve store is stored and reported correctly

---

## Issue 10 --- Validation Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Add validation commands that route through the current `cad2d/validate` layer.

Recommended initial support:

- `validate shape <shape>`
- optional curve-store override support where necessary

### Acceptance Criteria

- validation commands resolve named session objects correctly
- bound curve-store associations are used by default when appropriate
- validation failures are reported clearly

### Tests

- validating a valid shape succeeds
- missing bound curve store fails clearly when required
- invalid topology or geometry binding failures are surfaced cleanly

---

## Issue 11 --- Geometry and Topology Inspection Commands

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Add read-only inspection commands for shell users to understand current model state.

Recommended commands:

- `curve show ...`
- `shape show ...`
- later entity-level inspection commands

### Acceptance Criteria

- object inspection is available without mutating state
- output is deterministic and readable
- inspection is suitable for developer and CAD-workflow debugging

### Tests

- inspection commands display correct object summaries
- requesting missing objects fails cleanly

---

# Milestone: vNext Shell+2 --- Selection and Entity Referencing

## Goal

Introduce user-facing entity referencing and selection capabilities similar in spirit to CAD command environments.

---

## Issue 12 --- Entity Reference Model

**Priority:** High  
**Domain:** `shell/cad2d/session`  
**Type:** Feature / Foundation

### Description

Add a shell-level entity reference model for addressing topology entities such as:

- vertex
- edge
- half-edge
- wire
- face

The shell should not rely solely on raw IDs typed repeatedly by the user.

### Acceptance Criteria

- entity reference type exists
- entity kind is explicit
- references carry enough information to resolve against named shapes
- design leaves room for symbolic aliases later

### Tests

- entity references can be constructed and stored deterministically
- invalid kind or missing shape resolution fails cleanly

---

## Issue 13 --- Selection Subsystem

**Priority:** High  
**Domain:** `shell/cad2d/session`  
**Type:** Feature

### Description

Introduce a first-class selection subsystem.

Initial support should include:

- primary selection
- clear selection
- selection inspection

Later this will grow toward more AutoCAD-like selection workflows.

### Acceptance Criteria

- selection is stored separately from topology and geometry domains
- primary selection can be assigned and cleared
- status output includes current selection

### Tests

- selection can be set and cleared
- selection survives non-mutating commands
- selection resets correctly with session reset

---

## Issue 14 --- Last-Result and Alias Handles

**Priority:** Medium  
**Domain:** `shell/cad2d/session + commands`  
**Type:** Feature / CAD Usability

### Description

Add shell aliases and session handles for common user workflows.

Recommended early handles:

- `$last`
- `$last_edge`
- `$last_wire`
- `$last_face`
- `$sel`

This is a key step toward a more practical command-driven CAD experience.

### Acceptance Criteria

- shell can resolve built-in last-result aliases
- aliases update deterministically after creation commands
- invalid alias resolution fails clearly

### Tests

- creating an entity updates the corresponding last-result handle
- alias lookup returns the expected entity reference
- unset aliases fail explicitly

---

## Issue 15 --- Selection Commands

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / CAD Usability

### Description

Add commands for user-facing selection workflows.

Recommended initial commands:

- `select clear`
- `select show`
- `select set <entity-ref>`

Later, this subsystem can grow toward multi-selection and filtered selection.

### Acceptance Criteria

- selection commands work through the session subsystem
- selection state is queryable and deterministic
- invalid selections fail clearly

### Tests

- selection commands update session correctly
- invalid entity references are rejected
- `select clear` behaves correctly

---

# Milestone: vNext Shell+3 --- Algorithm Commands and Geometric Query Workflows

## Goal

Expose existing `cad2d` algorithms through the shell in a form useful for CAD-style workflows and debugging.

---

## Issue 16 --- Wire Length Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Expose wire geometric length computation through the shell.

### Acceptance Criteria

- shell can resolve the target wire and its geometry context
- result is reported clearly
- failures are explicit

### Tests

- shell command returns expected wire length on representative input
- missing geometry bindings fail cleanly

---

## Issue 17 --- Face Area and Orientation Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Expose the current polygonal face area and orientation utilities through the shell.

### Acceptance Criteria

- shell can compute signed area and orientation
- result reporting is deterministic
- unsupported/non-polygonal cases fail explicitly

### Tests

- simple polygonal face area is returned correctly
- unsupported geometry fails cleanly

---

## Issue 18 --- Span Intersection Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature

### Description

Expose bounded span intersection queries at shell level.

Recommended commands:

- `algo intersect spans ...`
- `algo intersect halfedges ...`

### Acceptance Criteria

- shell resolves spans or half-edges correctly
- geometry-level and topology-level intersection APIs are reachable through commands
- output ordering is deterministic

### Tests

- representative span and half-edge intersections work
- invalid bindings fail clearly
- disjoint cases report no intersection cleanly

---

## Issue 19 --- Result Rendering for Geometry Queries

**Priority:** Medium  
**Domain:** `shell/cad2d/render`  
**Type:** Feature / Usability

### Description

Improve rendering for geometric query results so shell output is practical for interactive CAD-style use.

### Acceptance Criteria

- point intersections, overlaps, and empty results render clearly
- tabular or structured output is readable
- output is stable across repeated runs

### Tests

- representative result types render correctly
- empty results are distinguishable from failures

---

# Milestone: vNext Shell+4 --- Topology Editing and Fragmentation Shell

## Goal

Prepare the shell for the next core `cad2d` editing and fragmentation milestones by exposing controlled editing workflows.

---

## Issue 20 --- Edge Split Command

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / CAD Editing

### Description

Expose edge splitting through the shell once the underlying `cad2d` edge-split operation exists.

This is one of the first truly CAD-like editing commands and will underpin many later workflows.

### Acceptance Criteria

- edge split command exists
- split updates session aliases and selection where appropriate
- failures near endpoints or invalid parameters are explicit

### Tests

- midpoint edge split succeeds
- endpoint-near split is rejected by rule
- resulting topology validates

---

## Issue 21 --- Wire Fragmentation Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / CAD Editing

### Description

Expose wire fragmentation and split-point workflows once the underlying fragmentation utilities exist.

### Acceptance Criteria

- wire fragmentation command exists
- resulting fragments are inspectable
- fragment ordering is deterministic

### Tests

- representative fragmentation scenario succeeds
- invalid split requests fail explicitly

---

## Issue 22 --- Selection-Aware Editing Workflow Support

**Priority:** Medium  
**Domain:** `shell/cad2d/session + commands`  
**Type:** Feature / CAD Usability

### Description

Improve shell editing workflows so commands can naturally consume current selection and last-result handles, closer to commercial CAD command flows.

### Acceptance Criteria

- edit commands can consume selection defaults where appropriate
- command output updates selection and last-result state deterministically
- workflow remains explicit and debuggable

### Tests

- selection-driven split workflow behaves correctly
- last-result handles update after editing commands

---

# Milestone: vNext Shell+5 --- Sketch Region Construction Shell

## Goal

Support region extraction and face construction from sketch geometry in a more user-facing shell workflow.

---

## Issue 23 --- Loop Extraction Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / CAD Workflow

### Description

Expose loop extraction from fragment graphs once the underlying `cad2d` region machinery exists.

### Acceptance Criteria

- shell command exists for loop extraction
- extracted loops are inspectable
- loop ordering and orientation reporting are deterministic

### Tests

- intersecting rectangle-style case returns expected loops
- open sketches return no loop result cleanly

---

## Issue 24 --- Region-to-Face Construction Commands

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / CAD Workflow

### Description

Expose face construction from closed loops and sketch regions.

### Acceptance Criteria

- valid regions can be converted into faces through the shell
- hole classification is reported clearly
- resulting topology validates

### Tests

- simple closed region becomes one face
- nested loop case produces outer face plus hole
- ambiguous invalid input fails explicitly

---

## Issue 25 --- Sketch Inspection and Region Diagnostics

**Priority:** Medium  
**Domain:** `shell/cad2d/commands + render`  
**Type:** Feature / CAD Workflow

### Description

Add shell-side diagnostics for fragmented sketches, extracted loops, and candidate regions so the shell supports practical region debugging and user interpretation.

### Acceptance Criteria

- extracted regions can be inspected clearly
- invalid sketch states produce useful diagnostics
- output is deterministic and readable

### Tests

- region diagnostics are available for representative valid and invalid cases

---

# Milestone: vNext Shell+6 --- AutoCAD-like Editing Commands

## Goal

Introduce user-facing editing commands associated with practical CAD shells.

---

## Issue 26 --- Trim Command

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / AutoCAD-like Editing

### Description

Expose trim workflows once the underlying trim-capable splitting infrastructure exists.

The shell design should support both explicit arguments and future selection-driven interaction.

### Acceptance Criteria

- trim command exists
- resulting topology remains valid
- selection and last-result handles integrate cleanly

### Tests

- representative trim case succeeds
- out-of-span trim request fails explicitly
- result validates

---

## Issue 27 --- Break / Split-at-Point Command

**Priority:** High  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / AutoCAD-like Editing

### Description

Expose break-style workflows similar to commercial CAD systems.

### Acceptance Criteria

- break command exists
- midpoint break or explicit parameter split works
- invalid endpoint break cases follow explicit rules

### Tests

- representative break case succeeds
- endpoint no-op or rejection behaves deterministically

---

## Issue 28 --- Join / Coalesce Command

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / AutoCAD-like Editing

### Description

Expose join/coalesce workflows for compatible neighbouring spans.

### Acceptance Criteria

- compatible spans can be joined
- incompatible spans fail cleanly
- result validates

### Tests

- adjacent collinear segments join successfully
- incompatible join is rejected

---

# Milestone: vNext Shell+7 --- Drafting Commands

## Goal

Add drafting-oriented shell commands similar to those expected in practical 2D CAD systems.

---

## Issue 29 --- Offset Command

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / Drafting

### Description

Expose offset workflows for supported segment-first and arc-first geometry.

### Acceptance Criteria

- basic offset command exists
- offset result is inspectable
- invalid or self-intersecting cases fail explicitly

### Tests

- rectangle-style offset succeeds
- invalid small-feature case fails cleanly

---

## Issue 30 --- Fillet Command

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / Drafting

### Description

Expose tangent fillet insertion workflows for compatible geometry.

### Acceptance Criteria

- fillet command exists
- adjacent geometry is updated consistently
- result validates

### Tests

- simple right-angle fillet succeeds
- impossible radius fails explicitly

---

## Issue 31 --- Chamfer Command

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / Drafting

### Description

Expose chamfer creation workflows for compatible geometry.

### Acceptance Criteria

- chamfer command exists
- adjacent spans update consistently
- result validates

### Tests

- representative chamfer succeeds
- oversized chamfer fails cleanly

---

# Milestone: vNext Shell+8 --- CAD Workflow and Productivity Features

## Goal

Move beyond primitive command execution toward workflows associated with practical commercial CAD shells.

---

## Issue 32 --- Named Selection Sets and Groups

**Priority:** Medium  
**Domain:** `shell/cad2d/session + commands`  
**Type:** Feature / CAD Workflow

### Description

Introduce named selection sets or groups so users can persist and reuse working sets of entities.

### Acceptance Criteria

- named sets can be created, listed, and reused
- set membership is deterministic
- invalid entities are rejected cleanly

### Tests

- named set creation and reuse works
- duplicate set naming fails explicitly

---

## Issue 33 --- Command History and Repeat Support

**Priority:** Medium  
**Domain:** `shell/cad2d/session + runtime`  
**Type:** Feature / Productivity

### Description

Add command-history infrastructure and support for repeating recent commands where appropriate.

### Acceptance Criteria

- command history is stored
- recent-command listing works
- repeat-last-command behavior is deterministic where enabled

### Tests

- history records executed commands
- repeat support replays the expected command safely

---

## Issue 34 --- Command Journaling and Replay Foundation

**Priority:** Medium  
**Domain:** `shell/cad2d`  
**Type:** Feature / Future-proofing

### Description

Lay the foundation for command journaling, replay, and eventually undo/redo or scripting workflows.

### Acceptance Criteria

- command journal model exists
- session mutations can be logged consistently
- replay design is documented clearly

### Tests

- representative mutating commands can be journaled
- replay ordering is deterministic in simple cases

---

## Issue 35 --- Workspace-backed Session Save/Load

**Priority:** Medium  
**Domain:** `shell/cad2d/session + foundation/workspace`  
**Type:** Feature / Workflow

### Description

Integrate the shell session with the Tonb foundation workspace layer so shell state can later be saved, restored, and exported consistently.

### Acceptance Criteria

- shell can resolve a workspace root
- session save/load foundation exists
- file locations are deterministic and documented

### Tests

- representative session state can be saved and restored
- invalid or missing workspace paths fail cleanly

---

# Milestone: vNext Shell+9 --- Exchange and Interoperability

## Goal

Support practical data exchange and scripting-oriented workflows expected from serious CAD command environments.

---

## Issue 36 --- DXF-Oriented Sketch Export Commands

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / Interoperability

### Description

Expose DXF-oriented export workflows once the underlying exchange layer exists.

### Acceptance Criteria

- supported sketch entities can be exported
- export path handling is clear and deterministic
- unsupported entities fail explicitly

### Tests

- simple line/arc sketch export succeeds
- unsupported content fails cleanly

---

## Issue 37 --- DXF-Oriented Sketch Import Commands

**Priority:** Medium  
**Domain:** `shell/cad2d/commands`  
**Type:** Feature / Interoperability

### Description

Expose DXF-oriented import workflows once the underlying exchange layer exists.

### Acceptance Criteria

- supported sketch entities can be imported into shell-managed objects
- reconstruction path is deterministic
- invalid files fail explicitly

### Tests

- simple sketch import succeeds
- malformed or unsupported input fails cleanly

---

## Issue 38 --- Scripting-Friendly Batch Execution

**Priority:** Medium  
**Domain:** `shell/cad2d`  
**Type:** Feature / Automation

### Description

Support batch execution of shell command files for repeatable workflows and automated testing.

### Acceptance Criteria

- shell can execute commands from a script file
- error handling is explicit
- deterministic behavior is preserved in batch mode

### Tests

- representative command script executes successfully
- script failure surfaces the correct error

---

# Milestone: vNext Shell+10 --- Advanced CAD-like Session Features

## Goal

Lay the groundwork for more advanced commercial-CAD-like shell behavior.

---

## Issue 39 --- Undo/Redo Foundation

**Priority:** Medium  
**Domain:** `shell/cad2d/session`  
**Type:** Feature / CAD Infrastructure

### Description

Introduce the foundational session-edit journaling and reversible-operation framework needed for future undo/redo.

### Acceptance Criteria

- session mutation model is compatible with reversible edits
- undo/redo design is documented
- representative reversible operations can be demonstrated

### Tests

- representative reversible command model behaves deterministically

---

## Issue 40 --- Interactive Command State Foundation

**Priority:** Low  
**Domain:** `shell/cad2d/runtime`  
**Type:** Feature / Future-proofing

### Description

Prepare the runtime model for multi-step interactive command workflows, such as future selection-driven trim or fillet commands.

### Acceptance Criteria

- runtime can represent active command state and pending picks
- interactive state model is documented clearly
- model does not interfere with normal single-line commands

### Tests

- runtime can enter and leave transient interactive states cleanly

---

## Issue 41 --- Constraint-friendly Reference Preservation

**Priority:** Low  
**Domain:** `shell/cad2d/session + topo`  
**Type:** Feature / Future-proofing

### Description

Prepare shell-level identity and reference handling so future constraint-driven or parametric editing workflows can be built on top of stable or diagnosable entity references.

### Acceptance Criteria

- reference-preservation rules are documented
- invalidated references can be detected explicitly
- shell design remains compatible with future parametric workflows

### Tests

- representative edit invalidation or preservation cases are detectable

---

# Recommended Order of Execution

The recommended implementation order is:

1. **vNext Shell+0** — shell foundation and session core  
2. **vNext Shell+1** — construction, inspection, and validation commands  
3. **vNext Shell+2** — selection and entity referencing  
4. **vNext Shell+3** — algorithm commands and geometric query workflows  
5. **vNext Shell+4** — topology editing and fragmentation shell  
6. **vNext Shell+5** — sketch region construction shell  
7. **vNext Shell+6** — AutoCAD-like editing commands  
8. **vNext Shell+7** — drafting commands  
9. **vNext Shell+8** — CAD workflow and productivity features  
10. **vNext Shell+9** — exchange and interoperability  
11. **vNext Shell+10** — advanced CAD-like session features  

This order is intentional:

- the shell should first become a robust orchestration environment
- editing commands should not arrive before stable references and selection exist
- drafting commands such as offset, fillet, and chamfer should build on editing and fragmentation foundations
- practical interoperability and scripting should come after the basic command model is stable

---

# Strategic Notes

## Why not jump directly to AutoCAD-like commands?

Commands such as trim, fillet, chamfer, offset, and region creation depend on substantial foundations:

- session state
- object naming and active-context handling
- selection and entity references
- geometry and topology inspection
- fragmentation and editing infrastructure
- clear result rendering and diagnostics

Trying to expose commercial-style commands too early typically leads to brittle shell behavior and poor long-term UX.

## What is realistically achievable?

A command shell with behavior increasingly similar to AutoCAD is realistic if the shell remains disciplined and builds on the existing `cad2d` foundations rather than bypassing them.

The practical target should be:

- robust command-driven construction and inspection
- selection-aware editing workflows
- sketch-to-region workflows
- drafting operations
- export/import and scripting support
- future-friendly session infrastructure for undo/redo and constraint-like workflows

---

# Immediate Recommendation

The next actual implementation milestone should be:

## **Milestone: vNext Shell+0 --- Shell Foundation and Session Core**

That milestone provides the correct base for everything that follows and should be treated as the first implementation target for `shell/cad2d`.
