# Hash Utilities for Spatial Indexing
This header provides **fast**, **deterministic hashing utilities** for integer-based spatial grid keys, commonly used in 
computational geometry applications like meshing, voxel grids, and spatial indexing structures.

## Overview
The code implements a **SplitMix64-based hash mixing strategy** designed specifically for:
- 2D grid coordinates `(i, j)`
- 3D voxel coordinates `(i, j, k)`
- Generic tuple-based keys

These are optimized for use with standard library hash containers (`std::unordered_map`, `std::unordered_set`).

## Core Components
### 1. `splitmix64()` - The Mixing Function
```c++
inline std::uint64_t splitmix64(std::uintin64_t x) noexcept;
```
- **Purpose**: High-quality 64-bit integer mixer with strong avalanche properties.
- **Properties**:
  - Fast (just bit shifts, XORs, and multiplies)
  - Deterministic across platforms
  - Excellent distribution for nearby input values
- **Not cryptographic**: Suitable for hash tables, not for security

The function applies a series of mixing operations:
1. Adds a golder ratio constant for bit spreading
2. Three rounds of XOR-shift + multiplication
3. Final XOR for output diffusion

### 2. `mix_combine()` - Hash Composition
```c++
inline std;;uint64_t mix_combine(std::uint64_t h, std::uint64_t v) noexcept
```
- **Purpose**: Combines two 64-bit values into a single hash
- **Usage**: Building multi-component hashes iteratively
- **Method**: XORs inputs then applies `splitmix64()`

---
## Hash Functors
### 3. `PairHash` - 2D Grid Coordinates
```c++
struct PairHash
```
- **Input**: `std::pair<int, int>` representing `(i, j)` grid cell 
- **Strategy**:
  - Packs two 32-bit signed integers into a single 64-bit value
  - Upper 32 bits = first coordinate
  - Lower 32 bits = second coordinate
  - Applies `splitmix64()` to packed value
- **Limitation**: Assumes coordinates fit in 32-bit range

**Use case**: Fast hashing for 3D spatial grids with moderate coordinate ranges.

### 4. `PairHashWide` - Extended Range 2D Coordinates
```c++
struct PairHashWide
```
- **Input**: `std::pair<long long, long long>`
- **Strategy**: Sequential `mix_combine()` instead of bit packing
- **Advantage**: Safe for coordinates exceeding 32-bit range
- **Trade-off**: Slightly more instructions than `PairHash`

### 5. `Int3` - 3D Coordinate Type
```c++
struct Int3 { int x, y, z; }
```
- Simple POD type for 3D integer coordinates
- Provides `operator==` for hash table equality comparison
- Minimal, replaceable structure

### 6. `Int3Hash` - 3D Voxel Hashing
```c++
struct Int3Hash
```
- **Input**: `Int3` representing `(x, y, z)` voxel coordinate
- **Strategy**: Sequential mixing of three components:
  1. Start with `splitmix64(x)`
  2. Combine with `y` using `mix_combine()`
  3. Combine with `z` using `mix_combine()`
- **Use case**: Voxel grids, 3D spatial partitioning

### 7. `TupleHssh` - Generic Tuple Hashing
```c++
template<class... Ts>
struct TupleHash
```
- **Input**: `std::tuple<Ts...>` of arbitrary types
- **Strategy**:
  - Uses `std::hash<T>` for each element
  - Sequentially combines using `mix_combine()`
  - Leverages C++17 fold expressions for clean iteration
- **Flexibility**: Works with any hashable types

The `hash_one()` helper function converts each tuple element via `std::hash<T>`, widens to 64-bit, then mixes.

---
## Design Rationale
## Why Custom Hashing?
1. **Determinism**: `std::hash` implementations vary across platforms/compilers
2. **Quality**: Tailored for spatial access patterns with low collision rates
3. **Performance**: Optimized for integer operations common in geometry code
4. **Simplicity**: Header-only, zero dependencies

## Thread Safety
All functions are **pure** (no side effects) and thread-safe. Concurrency concerns come from the container, not the hash
functions.

## Portability
- Works on both 32-bit and 64-bit architectures
- When `size_t` is 32-bit, the 64-bit hash is safely trucated
- Endianness-independent
- Compliant with modern C++ (C++17)

---
## Usage Example
```c++
#include <tonb/geometry/utils/hash.hxx>
#include <unordered_map>

using namespace tonb::geometry::utils::hash;

// 2D spatial grid
std::unordered_map<std::pair<int, int>, CellData, PairHash> grid2d;
grid2d[{10, 20}] = someData;

// 3D voxel grid
std::unordered_map<Int3, VoxelData, Int3Hash> voxels,
voxels[{5, 10, 15}] = voxelData;

// Generic tuple key
std::unordered_map<std::tuple<int, int, double>, Value, TupleHash<int, int, double>> cache;
```
## Performance Notes
- **Hash computation**: O(1) with very low constant factor
- **Practical performance**: Dominated by hash table cache misses, not hash calculation
- **Collision rate**: Very low for typical spatial coordinate patterns
- **Not for adversarial input**: Use cryptographic hashes for untrusted data

This utility is well-suited for high-performance computational geometry applications where deterministic, fast spatial 
hashing is essential.

---
## References
- [SplitMix64](https://github.com/aappleby/smhasher/blob/master/src/SplitMix64.cpp)
- [Fast Hashing](https://www.eecs.harvard.edu/~michaelm/postscripts/tr-02-05.pdf)