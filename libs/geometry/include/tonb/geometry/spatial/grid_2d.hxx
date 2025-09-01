//
// Created by amir on 8/31/25.
//
#pragma once
#ifndef TONB_GEOMETRY_SPATIAL_GRID_2D_HXX
#define TONB_GEOMETRY_SPATIAL_GRID_2D_HXX

/**
 * @file grid_2d.hxx
 * @brief A lightweight uniform grid (spatial hash) for 2D point-like items.
 *
 * @details
 * `SpatialGrid2d` indexes items in fixed-size square cells for quick insertion,
 * merging, and neighbourhood queries. It does not balance or rebin—operations
 * are strictly local to a cell and its neighbours.
 *
 * @section sg2d_concepts Concepts
 * - @b GetXY: callable `get_xy(const T&) -> std::pair<double,double>`
 * - @b Merge: callable `merge(T& existing, const T& incoming)`
 *
 * @section sg2d_complexity Complexity (amortised)
 * - Insert / insert-or-merge: ~O(1) average (visits ≤ 9 buckets).
 * - AABB query: visits only buckets overlapping the box; per-bucket linear in occupancy.
 *
 * @section sg2d_choose_cell Choosing cell size
 * Pick `cell_size` near your merge/search radius. For merge radius `r`, use
 * `cell_size ∈ [r, 2r]`. This keeps neighbour scans tiny while limiting collisions.
 *
 * @section sg2d_example Example
 * @code{.cpp}
 * struct Hit { double x, y; int count = 1; };
 *
 * struct GetHitXY {
 *   std::pair<double,double> operator()(const Hit& h) const noexcept { return {h.x, h.y}; }
 * };
 *
 * struct MergeCount {
 *   void operator()(Hit& a, const Hit& b) const {
 *     // simple arithmetic mean for position; accumulate count
 *     a.x = 0.5*(a.x + b.x);
 *     a.y = 0.5*(a.y + b.y);
 *     a.count += b.count;
 *   }
 * };
 *
 * tonb::geometry::spatial::SpatialGrid2d<Hit, GetHitXY, MergeCount> grid(0.1);
 * grid.insert_or_merge({0.01, 0.02, 1}, 0.08);
 * grid.insert_or_merge({0.05, 0.00, 1}, 0.08);
 *
 * std::vector<std::size_t> ids;
 * grid.query_aabb(-0.1, -0.1, 0.1, 0.1, std::back_inserter(ids));
 * for (auto idx : ids) {
 *   const auto& h = grid[idx]; // access merged item
 * }
 * @endcode
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>

#include <unordered_map>
#include <vector>
#include <cmath>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <limits>
#include <algorithm>

namespace tonb::geometry::spatial {
    /**
     * @brief Default GetXY policy that reads `x` and `y` data members.
     * @tparam T Item type holding ~real T::*` members for `x` and `y`.
     */
    template<class T>
    struct MemberXY {
        real T::* x{};
        real T::* y{};
        std::pair<real, real> operator()(const T& v) const noexcept {return {v.*x, v.*y};}
    };

    /**
     * @brief  Default Merge policy that replaces existing with incoming.
     */
    struct ReplaceMerge {
        template<class T>
        void operator()(T& existing, const T& incoming) const {existing = incoming;}
    };

    namespace detail {
        struct Key {
            int32_t i{}, j{};
            bool operator==(const Key & o) const noexcept {return i == o.i && j == o.j;}
        };
        struct KeyHash {
            std::size_t operator()(const Key & k) const noexcept {
                // 64-bit mix of two 32-bit ints (splitmax64-ish)
                uint64_t x = static_cast<uint32_t>(k.i);
                uint64_t y = static_cast<uint32_t>(k.j);
                uint64_t z = (x << 32) ^ y;
                z ^= z >> 33; z *= 0xff51afd7ed558ccdULL;
                z ^= z >> 33; z *= 0xc4ceb9fe1a85ec53ULL;
                z ^= z >> 33;
                return static_cast<std::size_t>(z);
            }
        };
    }

    /**
     * @brief A generic 2D spatial index based on a uniform grid (spatial hash).
     *
     * @tparam T item type.
     * @tparam GetXY Policy to extract `(x,y)` from `const T&`. Calculate as `std::pair<double,double>(const T&)`.
     * @tparam Merge Policy to merge incoming into an existing item found within the merge radius.
     * @tparam KeyHash for internal grid keys (customise to swap hash map type).
     */
    template<class T, class GetXY, class Merge, class KeyHash = detail::KeyHash>
    class Grid2d {
    public:
        using index_type = std::size_t;

        explicit Grid2d(real cell_size, GetXY get_xy = GetXY{}, Merge merge = Merge{}, KeyHash hasher = KeyHash{})
            : h_(cell_size)
            , invh_(1.0/ cell_size)
            , get_xy_(std::move(get_xy))
            , merge_(std::move(merge))
            , buckets_(0, std::move(hasher))
        {}

        /**
         * @brief Remove all items and buckets.
         */
        void clear() {
            items_.clear();
            buckets_.clear();
        }

        /**
         * @brief Number of items stored (after merges).
         */
        TNB_NODISCARD std::size_t size() const noexcept { return items_.size(); }

        index_type insert_or_merge(const T& item, real merge_radius) {
            const auto [x, y] = get_xy_(item);
            const detail::Key k = key_(x, y);
            ensure_bucket_(k);

            index_type found = npos;
            const real r2 = merge_radius * merge_radius;

            auto scan_bucket = [&](const detail::Key& kk) {
                const auto it = buckets_.find(kk);
                if (it == buckets_.end()) return;
                for (const auto& vec = it->second; index_type idx : vec) {
                    const auto [qx,qy] = get_xy_(items_[idx]);
                    const double dx = qx - x, dy = qy - y;
                    if ((dx*dx + dy*dy) <= r2) { found = idx; return; }
                }
            };

            // check 3x3 neighbourhood
            for (int dj = -1; dj <= 1 && found == npos; ++dj)
                for (int di = -1; di <= 1 && found == npos; ++di) {
                    scan_bucket(detail::Key{k.i + di, k.j + dj});
                }

            if (found != npos) {
                merge_(items_[found], item);
                return found;
            }

            const auto idx = static_cast<index_type>(items_.size());
            items_.push_back(item);
            buckets_[k].push_back(idx);
            return idx;
        }

        /**
         * @brief Insert/merge a range of items with a single merge radius.
         *
         * @tparam Range A range whose value_type is `T` (e.g., std::vector<t>).
         * @param range Items to insert.
         * @param merge_radius Merge radius applied to each item.
         *
         * @return Number of items after the operation (post-merge size).
         */
        template<class Range>
        std::size_t insert_or_merge_range(const Range& range, real merge_radius) {
            for (const auto& v : range) insert_or_merge(v, merge_radius);
            return items_.size();
        }

        /**
         * @brief Query items whose coordinates fall inside an axis-aligned bounding box.
         *
         * @tparam OutputIt Output iterator receiving indices of matches.
         * @param xmin Minimum x of the box.
         * @param ymin Minimum y of the box.
         * @param xmax Maximum x of the box.
         * @param ymax Maximum y of the box.
         * @param out  Output iterator for matched indices.
         *
         * @note The method scans only buckets overlapping the AABB; items are re-checked
         *      against the box to avoid edge false positives.
         */
        template<class OutputIt>
        void query_aabb(real xmin, real ymin, real xmax, real ymax, OutputIt out) const {
            const detail::Key kmin{ static_cast<int>(std::floor(xmin * invh_)),
                      static_cast<int>(std::floor(ymin * invh_)) };
            const detail::Key kmax{ static_cast<int>(std::floor(xmax * invh_)),
                              static_cast<int>(std::floor(ymax * invh_)) };

            for (int j = kmin.j; j <= kmax.j; ++j)
                for (int i = kmin.i; i <= kmax.i; ++i) {
                    auto it = buckets_.find(detail::Key{i,j});
                    if (it == buckets_.end()) continue;
                    for (index_type idx : it->second) {
                        const auto [x,y] = get_xy_(items_[idx]);
                        if (x >= xmin && x <= xmax && y >= ymin && y <= ymax)
                            *out++ = idx;
                    }
                }
        }

        /**
         * @brief Radius (disc) query centred at (cx, cy).
         *
         * @tparam OutputIt Output iterator receiving indices of matches.
         * @param cx Centre x.
         * @param cy Centre y.
         * @param r  Radius.
         * @param out Output iterator for matched indices.
         */
        template<class OutputIt>
        void query_radius(real cx, real cy, real r, OutputIt out) const {
            const double r2 = r * r;
            const int i0 = static_cast<int>(std::floor((cx - r) * invh_));
            const int j0 = static_cast<int>(std::floor((cy - r) * invh_));
            const int i1 = static_cast<int>(std::floor((cx + r) * invh_));
            const int j1 = static_cast<int>(std::floor((cy + r) * invh_));

            for (int j = j0; j <= j1; ++j)
                for (int i = i0; i <= i1; ++i) {
                    auto it = buckets_.find(detail::Key{i,j});
                    if (it == buckets_.end()) continue;
                    for (index_type idx : it->second) {
                        const auto [x,y] = get_xy_(items_[idx]);
                        const double dx = x - cx, dy = y - cy;
                        if ((dx*dx + dy*dy) <= r2) *out++ = idx;
                    }
                }
        }

        /**
         * @brief Direct access to stored items (post-merge).
         */
        const T& operator[](index_type idx) const {return items_[idx];}
        T& operator[](index_type idx) {return items_[idx];}

        /**
         * @brief Access underlying storage (useful for iteration/serialization).
         */
        const std::vector<T>& items() const noexcept { return items_; }
        std::vector<T>& items() noexcept { return items_; }


        /// Sentinel invalid index.
        static constexpr index_type npos = static_cast<index_type>(-1);

        /**
         * @brief Return the configured cell size (edge length).
         */
        TNB_NODISCARD real cell_size() const noexcept { return h_; }

    private:

        // static_assert(std::is_invocable_r_v<std::pair<real ,real>, GetXY, const T&>,
        //         "GetXY must be callable as get_xy(const T&) -> pair<double,double>");
        // static_assert(std::is_invocable_v<Merge, T&, const T&>,
        //               "Merge must be callable as merge(T& existing, const T& incoming)");

        /*Private Data*/
        real h_{1.0}, invh_{1.0};
        GetXY get_xy_;
        Merge merge_;
        std::vector<T> items_;
        std::unordered_map<detail::Key, std::vector<index_type>, detail::KeyHash> buckets_;

        // Private functions and operators

        detail::Key key_(real x, real y) const noexcept {
            return detail::Key{
                static_cast<int32_t>(std::floor(x * invh_)),
                static_cast<int32_t>(std::floor(y * invh_)),
            };
        }
        void ensure_bucket_(const detail::Key& k) {
#if defined(__cpp_lib_unordered_map_contains) && __cpp_lib_unordered_map_contains >= 201411
            if (!buckets_.contains(k)) buckets_.emplace(k, std::vector<index_type>{});
#else
            if (buckets_.find(k) == buckets_.end()) buckets_.emplace(k, std::vector<index_type>{});
#endif
        }
    };
}

#endif //TONB_GEOMETRY_SPATIAL_GRID_2D_HXX