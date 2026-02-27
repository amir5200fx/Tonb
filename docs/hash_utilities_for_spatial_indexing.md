# Hash Utilities for Spatial Indexing
This small header provides high-quality, fast hashing for integer cell keys used in spatial grids and voxel indices. It
is designed for geometry algorithms such as advancing-front meshing where keys are grid coordinates like `(i, j)` or 
`(i, j, k)`.

### Why a custom hash?
- **Deterministic across platforms**: avoids variability between standard library implementations.
- **Good avalanche properties**: based on a splitmix64-style mixer that spreads nearby integer keyys well.
- **Tiny and dependency-free**: header-only, no external libraries.
- **Reusable**: centralises hashing policy for 2D and 3D grids and any future voxel or cache maps.

### Provided types and functions
- `splitmix64(uint64_t)`: a fast 64-bit mixing function.
- `mix_combine(uint64_t h, uint64_t v)`: combine a new 64-bit value into an existing hash state.
- `PairHash`: `std::unordered_map` compatible hasher for `std::pair<int, int>`.
- `Int3`: minimal `(x, y, z)` integer key type.
- `Int3Hash`: hasher for `Int3`.
- `TupleHash<std::tuple<...>>`: generic hasher for tuples (optional but handy).

All are under `namespace tonb::geometry::util::hash`

### Big-O and practical performance
- Hash computational is a handful of integer operations. In practice time is dominated by cache misses in the hash table
rather than these operations.
- For 2D and 3D integer grid coordinates, the collision rate is very low under typical spatial access patterns.

### Ranges and safety:
- The `PairHash` packs two 32-bit signed coordinates into one 64-bit lane before mixing. This is safe for typical cell 
index ranges.
- If coordinates can exceed 32-bit range, replace the pack with a two-step `mix_combine` approach (shown in the Doxygen 
header) to avoid aliasing.

### Security note
This hash is **not** intended for adversarial input. It is a performance hash for geometry and simulation code. For 
untrusted keys choose a table with internal protection or a stronger keyed hash.

### Threading
The hashers are pure functions and are thread-safe. Concurrency concerns come from the container you use, not from the hash 
functions.

### Portability
- Works on 32-bit and 64-bit targets. When `size_t` is 32-bit, the mixed 64-bit value is truncated, which still performs
well due to the good avalanche properties of splitmix64.
- Endianness independent.