## ⚙️ What's going on
Inside the `HashGrid`, we've got two main containers:
```c++
std::vector<T> items_;                                          // actual items (vertices, edges, etc.)
std::unordered_map<Key, std::vector<size_t>, Hash> buckets_;    // Cell -> item indices
```
Each bucket stores **indices** (not pointers) into `items_`.

When you `erase(id)`, the code removes `id` from its bucket but does **not** remove `items_[id]`.

---
## 💀 What is a "tombstone"?
A _tombstone_ is a slot that used to hold a valid object, but has now been marked as deleted or simply ignored. The slot
stays allocated so that existing indices remain valid — even though the content isn't used anymore.

It's a common design trick when you want **stable indices**.

---
## 💡 Why keep it instead of removing it?
Because removing from a `std::vector` by index breaks _every_ other index after it.

For example:
```c++
std::vector<int> v = {10, 20, 30, 40};
v.erase(v.begin() + 1); // remove 20
// Now v = {10, 30, 40}, but indices have shifted!
// Old index 2 is now index 1, etc.
```

In your grid:
- Each bucket stores indices like `17, 42, 123`.
- If you remove one element form `items_`, **every subsequent index becomes wrong**.
- You'd have to go through all buckets and fix them — which is O(N).

By keeping a tombstone (just leaving the slot), you keep all other indices stable. That makes `erase()` O(1) instead of 
O(N).

---
## 🧠 Analogy
Think of `items_` as a table of citizens with unique ID numbers. When someone leaves the city (erase), you don't
renumber everyone else — you just mark their record as inactive. That way, all existing ID numbers still point to the 
right person.

---
## ⚖️ Trade-offs
| Approach                      | Pros                                                                  | Cons                                          |
| ----------------------------- | --------------------------------------------------------------------- | --------------------------------------------- |
| **Keep tombstones (current)** | O(1) erase, stable indices, simple logic                              | `items_` grows forever if many inserts+erases |
| **Compact immediately**       | Saves memory, no unused slots                                         | O(N) per erase, invalidates all indices       |
| **Deferred compaction**       | Best of both worlds: keep tombstones short term, occasionally rebuild | Slightly more code but efficient              |

---
## 🔄 Typical solution: add a `compact()` method
A deferred compaction pass cleans up tombstones occasionally:
```c++
void compact() {
    std::vector<T> new_items;
    std::vector<size_t> remap(items_.size(), size_t(-1));

    new_items.reserve(items_.size());
    for (size_t i=0; i<items_.size(); ++i) {
        if (!is_tombstone(i)) {
            remap[i] = new_items.size();
            new_items.push_back(std::move(items_[i]));
        }
    }

    // Rebuild all buckets with new indices
    for (auto& [key, vec] : buckets_) {
        for (auto& id : vec) id = remap[id];
    }

    items_.swap(new_items);
}
```
You'd call `compact()` every so often — for example, after a full front expansion or before serializing the mesh.

---
## 🧩 When tombstones are useful
They're especially useful in **dynamix algorithms** like:
- advancing-front meshing (adding/removing edges and points as the front evolves);
- particle systems;
- physics broad-phase grids.

These systems constantly add and remove objects but almost never re-index the whole dataset. Stable IDs are more 
valuable than a perfectly compact array.

---
## 🧭 Summary
| Concept       | Meaning                                                             |
| ------------- | ------------------------------------------------------------------- |
| **Tombstone** | A deleted item’s slot left in place so indices remain stable.       |
| **Why**       | Avoids shifting all later elements in `items_` (keeps O(1) erase).  |
| **Cost**      | Slightly higher memory usage until you compact.                     |
| **Fix**       | Add an optional `compact()` method to rebuild `items_` when needed. |

---

# 💡 Why not `std::map` or `std::set`?
Let's compare the trade-offs:

| Choice                               | Typical complexity                            | Memory layout     | Pros                                        | Cons                                                 |
| ------------------------------------ | --------------------------------------------- | ----------------- | ------------------------------------------- | ---------------------------------------------------- |
| **`std::vector`**                    | O(1) insert at end, O(1) random access        | contiguous        | fast lookups by ID, cache-friendly, compact | erasing by index shifts elements (unless tombstoned) |
| **`std::map`**                       | O(log N) insert/erase/find                    | scattered (nodes) | true erase without reindexing               | poor cache locality, heavy allocation overhead       |
| **`std::set`**                       | O(log N)                                      | scattered         | automatically unique keys                   | no direct value access, same memory cost as map      |
| **`unordered_map`** (direct storage) | O(1) average                                  | scattered buckets | flexible keys                               | doubles memory, pointer chasing                      |
| **`deque`**                          | O(1) append/remove at ends, stable references | segmented         | stable references, fairly cache-friendly    | no compact contiguity, slightly more indirection     |

## 1. Performance
`std::vector` is extremely fast because all data lives contiguously in memory. In numerical algorithms line meshing, 
90% of runtime is memory access — the fewer pointer jumps, the better.

`std::map` and `std::set` allocate one node per element (three pointers plus bookkeeping). They cost about **5-10x more 
memory** and cause **cache misses** on each access. That's unacceptable when you might have 100k-10M items.

---
## 2. Stable indexing
If you switch to `std::map`, you would have to ude keys (like a unique ID field) instead of vector indices, e.g.:
```c++
std::map<int, T> items_;
```
But now your `buckets_` need to store iterators or IDs instead of integers, and you lose the simple `items_[id]` O(1)
access.

`std::set` is even worse because you cannot modify an item's value once inserted without breaking ordering.

---
## 3. Erasing
A `map` can erase efficiently (O(log N)) and doesn't invalidate other iterators, but for your algorithm, you rarely
erase many items at random. Most of the time you _add new points_, and occasionally remove a few. Using tombstones + 
optional compaction is still faster overall than making every insert O(log N).

---
## 4. Memory
Roughly, a `vector<T>` storing 1M vertices uses-size(T)*1M bytes. A `map<int, T>` storing 1M vertices uses **at least 3 
pointers per node**, plus allocator overhead — easily **3-5x more memory**.

---
## 5. Predictability
Vectors are deterministic in ordering and performance. Three-based maps can have variability depending on key 
distribution and allocator behavior. For geometry algorithms where you want repeatable results, that determinism is 
useful.

---
# 🧠 Design reasoning in short
Using a **vector + integer IDs** gives:
- **O(1)** insertion (push_back)
- **O(1)** access by ID
- Simple numeric indices (good for serialization and debugging)
- Cache-friendly memory layout

We pay only one cost: we cannot physically remove elements cheaply. We fix that with **tombstones + optional 
compaction** — a standard pattern in high-performance geometry and simulation engines.

---
# 🧩 Where a map/set would make sense
You might use a map or set **only for higher-level indexing**:
- mapping _global identifiers_ (like vertex GUIDs) to local IDs;
- maintaining _sorted_ sets of boundary edges;
- storing _rare_ auxiliary data (e.g. named entities, metadata).

But the **core spatial grid** should remain vector-based.

---
# 🧭 Summary
| Question           | Answer                                                     |
| ------------------ | ---------------------------------------------------------- |
| Why not map/set?   | Too slow and memory-hungry for dense spatial data          |
| Why vector?        | Contiguous, cache-friendly, O(1) ID lookup                 |
| What about erase?  | Leave tombstones, rebuild occasionally                     |
| When map/set is OK | For metadata, sparse or ordered lookups, not main geometry |
