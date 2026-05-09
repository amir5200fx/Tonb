//
// Created by amir on 11/1/25.
//
/**
 * @file hash.hxx
 * @brief Small hashing utilities for integer grid keys used in spatial indexing.
 *
 * This header provides a splimix64-style mixing function and convenient hash functors
 * for common integer call key types used in geometry code:
 *  - (i, j) as std::pair<int, int> via PairHash
 *  - (i, j, k) as Int3 via Int3Hash
 *  - a generic TupleHash for std::tuple<Ts...> when needed.
 *
 * This intent is deterministic, fast hashing with good avalanche properties, suitable for
 * spatial grids and voxel maps in meshing and simulation. This is not a cryptographic hash.
 */
#ifndef TONB_GEOMETRY_UTIL_HASH_HXX
#define TONB_GEOMETRY_UTIL_HASH_HXX
#include <cstddef>
#include <cstdint>
#include <functional>
#include <tuple>
#include <utility>
namespace tonb::geometry::utils::hash {
    /**
     * @brif High-quality 64-bit integer mixer (SplitMix64 algorithm).
     *
     * The SplitMix64 function is often used as a base generator in PCG or xoroshiro
     * random number engines. It provides strong avalanche-behavior-small input
     * changes result in large output changes across all bits.
     *
     * This makes it ideal for use in hash randomisation, spatial hashing, and
     * deduplication tasks where high-quality bit diffusion matters more than raw
     * speed.
     *
     * @param x Input integer to mix.
     * @return Mixed 64-bit hash.
     *
     * @see fnv1a_mix64 for a faster, lighter-weight alternative.
     */
    inline std::uint64_t splitmix64(std::uint64_t x) noexcept {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        x ^= (x >> 31);
        return x;
    }

    /**
     * @brief Lightweight FNV-1a-style 64-bit hash combiner.
     *
     * This function performs a simple XOR-mix operation, inspired by Boost's
     * hash_combine and the classical FNV-1a prime mixing approach. It is very fast
     * and well suited for combining small tuples of integers (e.g. vertex indices)
     * into a single hash value.
     *
     * @param h Current hash value (seed).
     * @param x Next integer value to combine.
     * @return Mixed 64-bit hash.
     *
     * @note This function provides moderate avalanche quality. It is suitable for
     * deterministic, performance-critical internal hashing, but not for cryptographic
     * or adversarial contexts.
     *
     * @see splitmix64 for stronger, slower alternative.
     */
    inline std::size_t fnv1a_mix64(const std::size_t h, const std::uint64_t x) noexcept {
        return (h ^ (x + 0x9e3779b97f4a7c15ull + (h << 6) + (h >> 2)));
    }

    /**
     * @brief Combines two 64-bit hash values into a single mixed value.
     *
     * This function uses the SplitMix64 mixing function to combine the two input values
     * into a single 64-bit result, ensuring strong avalanche properties and a well-distributed
     * hash result. Useful for hash composition or mixing multiple values into a single hash state.
     *
     * @param h The first 64-bit input hash value.
     * @param v The second 64-bit input value to combine with the first.
     * @return A mixed 64-bit hash value derived from the input values.
     */
    inline std::uint64_t mix_combine(const std::uint64_t h, const std::uint64_t v) noexcept {
        return splitmix64(h ^ v);
    }

    /**
     * @brief Hash functor for std::pair<int, int> cell keys (i, j).
     *
     * Packs two signed 32-bit integers into a 64-bit lane and applies splimix64.
     * Suitable for spatial grids where cell indices are within a 32-bit range.
     *
     * If your indices can exceed 32-bit, prefer PairHashWide below.
     */
    struct PairHash {
        std::size_t operator()(const std::pair<int, int>& k) const noexcept {
            const std::uint64_t packed =
                (static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.first)) << 32)
            | static_cast<std::uint64_t>(static_cast<std::uint32_t>(k.second));
            const std::uint64_t h = splitmix64(packed);
            return static_cast<std::size_t>(h);
        }
    };

    /**
     * @brief Wide pair hasher that avoids 32-bit packing.
     *
     * Uses two independent combines rather than bit packing. Slightly more instructions,
     * but safe if indices may exceed the 32-bit range after casting.
     */
    struct PairHashWide {
        std::size_t operator()(const std::pair<long long, long long>& k) const noexcept {
            std::uint64_t h = splitmix64(0);
            h = mix_combine(h, static_cast<std::uint64_t>(k.first));
            h = mix_combine(h, static_cast<std::uint64_t>(k.second));
            return static_cast<std::size_t>(h);
        }
    };

    /**
     * @brief Minimal integer 3D type for (i,j,k) grid coordinates.
     *
     * Provides equality for use in unordered_map. You may replace this with your own Int3
     */
    struct Int3 {
        int x, y, z;
        bool operator==(const Int3& o) const noexcept {return x==o.x && y==o.y && z==o.z;}
    };

    /**
     * @brief Hash functor for Int3 (i,j,k) keys.
     *
     * Mixes three 32-bit coordinates into a 64-bit state using splitmix64.
     * Good distribution for voxel grids and 3D spatial hashing.
     */
    struct Int3Hash {
        std::size_t operator()(const Int3& k) const noexcept {
            std::uint64_t h = splitmix64(static_cast<std::uint32_t>(k.x));
            h = mix_combine(h, static_cast<std::uint32_t>(k.y));
            h = mix_combine(h, static_cast<std::uint32_t>(k.z));
            return static_cast<std::size_t>(h);
        }
    };

    /**
     * @brief Helper to combine arbitrary types into a running 64-bit hash.
     *
     * Uses std::hash<T> to reduce T to a size_t, widens to 64-bit, then mix-combines.
     * This is useful to build TupleHash without depending on Boost.
     */
    template<class T>
    inline void hash_one(std::uint64_t& h, const T& v) {
        h = mix_combine(h, static_cast<std::uint64_t>(std::hash<T>{}(v)));
    }

    /**
     * @brief Hash functor for std::tuple<Ts...>.
     *
     * Applies hash_one sequentially over all tuple elements. This is generic and convenient
     * if you keep composite keys in tuples and want a deterministic policy.
     */
    template<class... Ts>
    struct TupleHash {
        std::size_t operator()(const std::tuple<Ts...>& t) const noexcept {
            std::uint64_t h = splitmix64(0);
            std::apply([&](auto const&... xs){ (hash_one(h, xs), ...);}, t);
            return static_cast<std::size_t>(h);
        }
    };

    /**
     * @brief Generic hash functor for small fixed-size key types.
     *
     * Designed for use with `std::unordered_map` and `std::unordered_set` where
     * keys are small structs containing integer arrays (e.g. FaceKey, EdgeKey).
     *
     * @tparam KeyT Type providing:
     *  - a member `std::array<index_t, N> v`
     *  - a member `std::uint8_t arity`
     */
    template<class KeyT>
    struct FaceKeyHash {
        std::size_t operator()(const KeyT& k) const noexcept {
            std::uint64_t h = 1469598103934665603ull; // FNV-1a 64-bit seed
            h = fnv1a_mix64(h, k.arity);
            for (auto vi : k.v) h = fnv1a_mix64(h, static_cast<std::uint64_t>(vi));
            return static_cast<std::size_t>(h);
        }
    };
}
#endif //TONB_GEOMETRY_UTIL_HASH_HXX