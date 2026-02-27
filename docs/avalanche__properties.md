# Avalanche Properties
A hash function has **good avalanche properties** when a **very small change in the input (line flipping one bit)** 
causes a **large, seemingly  random change in the output bits**.

So if you change `k.x` from `10` to `11`, you want _most_ of the 64 bits of the hash to flip unpredictably, not just 
one or two. This ensures the neighboring or similar inputs don't land in the same few buckets of your hash table.

---
## 💡 Why it matters
In your spatial grid, keys like `(i, j)` or `(i, j, k)` are _numerically close_ — adjacent cells differ by 1. If the 
hash function didn't "avalanche" well, nearby keys would have very similar hashes, causing them to fall into the same or
nearby buckets in `unordered_map`, which would lead to:
- **collisions** (slow lookups),
- **clustered buckets** (bad cache performance), and 
- **non-uniform distribution** of items.

A good avalanche ensures that these almost-identical cell coordinates get spread widely and uniformly throughout the 
table.

---
## ⚙️ Example
Let's say we have two 64-bit inputs differing by 1 bit:
```text
Input A: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0000
Input B: 00000000 00000000 00000000 00000000 00000000 00000000 00000000 0001
```
If your hash function has good avalanche properties, then:
```text
hash(A) = 11001001 01101000 10010110 ...
hash(B) = 00110011 10001111 01101010 ...
```
— roughly **half** the bits flip (statistically about 50%), and the patterns are uncorrelated.

If the hash were weak (for example, `hash(x) = x * 2654435761`), then consecutive inputs would produce outputs that are 
too close together, producing poor distribution.

---
## 🔬 Formal definition
In hashing literature, this is sometimes called the **avalanche criterion**:
> A function `H(x)` satisfies the avalanche criterion if, when a single input bit is complemented, each output bit 
> changes with probability 0.5.

SplitMix64 (the mixer we use) was designed to approximate that behavior very well for 64-bit integers. That's why it's 
popular for generating pseudo-random numbers, keys, and hash mixing — small differences in input get thoroughly 
scrambled.

---
## Summary
| Term                   | Meaning                                                      | Why it helps                                       |
| ---------------------- | ------------------------------------------------------------ | -------------------------------------------------- |
| **Avalanche property** | Small change in input → large, random change in output bits  | Prevents clustering, keeps buckets uniform         |
| **SplitMix64**         | A simple integer mixing function with near-perfect avalanche | Fast and deterministic                             |
| **Effect**             | Nearby cell keys map to very different hash values           | Faster, more stable performance in `unordered_map` |
