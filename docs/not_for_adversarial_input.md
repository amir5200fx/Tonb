# What "Not for Adversarial Input" means
"Adversarial input" refers to data intentionally crafted by a malicious actor to exploit weaknesses in your hash
function and degrade performance or cause security issues.

## The Problem: Hash Flooding Attacks
### Normal Use Case
```c++
std::unordered_map<std::pair<int, int>, Data, PairHash> grid;
grid[{5, 10}] = data1;  // Fast O(1) insertion
grid[{7, 12}] = data2;  // Fast O(1) insertion 
```
With legitimate spatial coordinates, the hash function distributes keys evenly across hash table buckets.

### Adversarial Attack Scenario
An attacker who knows your hash algorithm could craft inputs that **all hash to the same bucket**:
```c++
// Malicious user discovers these all collide:
grid[evil_pair_1] = ...;    // All hash to bucket 42
grid[evil_pair_2] = ...;    // All hash to bucket 42
grid[evil_pair_3] = ...;    // All hash to bucket 42
```
**Result**: Your O(1) hash table degrades to O(n) linked-list performance. This is called a **hash flooding** or 
**algorithmic complexity attack**.

## Why SplitMix64 Is Vulnerable
1. **Deterministic**: Same input always produces same output
2. **Public algorithm**: Attacker knows exactly how it works
3. **No secret key**: No randomization between program runs
4. **Reversible properties**: Attacker can mathematically find colliding inputs

## When This Matters
### ❌ Vulnerable scenarios (DON'T use this hash):
- **Web servers** processing user-submitted coordinates
- **Network protocols** where adversaries control grid keys
- **Public APIs** accepting arbitrary spatial data
- **Any untrusted input** from external sources
### ✅ Safe scenarios (OK to use):
- **Internal geometry algorithms** (meshing, voxelization)
- **Simulation code** where you generate the coordinates
- **Scientific computing** with trusted datasets
- **Game engines** processing your own level data
- **CAD applications** with user-designed models (typically trusted context)

## Secure Alternatives
For untrusted input, use:
### 1. Randomized hash functions
- [xxHash](https://github.com/Cyan4973/xxHash)
- [MurmurHash3](https://github.com/aappleby/smhasher)
- [FarmHash](https://github.com/google/farmhash)
- [CityHash](https://github.com/google/cityhash)
- [MetroHash](https://github.com/jandrewrogers/MetroHash)
- [SpookyHash](https://github.com/aappleby/smhasher)
- [SipHash](https://github.com/veorq/SipHash)
- [MurmurHash2](https://github.com/aappleby/smhasher)
### 2. Cryptographic hashes:
- [SHA-2](https://en.wikipedia.org/wiki/SHA-2)
- [BLAKE3](https://github.com/BLAKE3-team/BLAKE3)
### 3. Collision-resistant data structures:
- [SkipList](https://en.wikipedia.org/wiki/Skip_list)
- [Bloom Filter](https://en.wikipedia.org/wiki/Bloom_filter)

## Practical Example
### Tonb geometry library: ✅ SAFE
- You're doing computational geometry, mesh generation, spatial indexing
- The coordinates come from your own algorithms or trusted CAD files
- No external attacker can send malicious grid coordinates
- Performance matters more than protection against theoretical attacks

### A web service storing user locations: ❌ VULNERABLE
- Users could send crafted coordinates designed to collide
- This could DOS your server by making hash tables slow

## Bottom Line
The warning means: "_This hash is optimized for speed, not security. Use it when you trust the data source, not when 
processing potentially malicious input._"

For your geometry library's internal spatial indexing, this is perfectly appropriate! 🎯