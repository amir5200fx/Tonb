//
// Created by amir on 11/1/25.
//
/**
 * @file hash_grid_2d.hxx
 * @brief Header-only 2D spatial hash grid for dynamic geometry (advancing-front meshing).
 *
 * The grid partitions the plane into square cells of fixed size. Each inserted item T is mapped
 * to a cell by floor(p / cell_size). Buckets are stored in an unordered_map keyed by (i,j).
 *
 * Typical use: near-neighbor queries, local collision checks, and segment marching while the
 * front evolves. Expected O(1) insertion/update; queries visit only cells overlapping the search
 * region and then perform exact geometric filtering.
 *
 * Template parameter:
 *  - T: item type (e.g. vertex). A point extractor (GetPointFn<T>) provides (x,y).
 */
#ifndef TONB_GEOMETRY_SPATIAL_HASH_GRID_2D_HXX
#define TONB_GEOMETRY_SPATIAL_HASH_GRID_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/geometry/utils/hash.hxx>
#include <tonb/base/precision.hxx>

#include <utility>
#include <functional>
#include <boost/mpl/iterator_range.hpp>

namespace tonb::geometry::spatial {

    template <class P>
    concept PointLike = requires(P p) {
        {p[0]} -> std::convertible_to<real>;
    };

    /// Returns the 2D position of an item as {x, y}.
    /** Override with set_get_point if T does not have .x and .y members*/
    template <class T>
    using GetPointFn = std::function<std::array<real, 2>(const T&)>;

    /**
     * @class HashGrid2d
     * @tparam T Item type (vertex, edge proxy, etc.)
     * @brief Dynamic 2D spatial index with fixed cell size.
     *
     * @section design Design
     * Items are stored contiguously in a vector and referenced by stable indices (std::size_t).
     * Each bucket holds a small vector of item IDs. A side array @ref locate_ maps item ID -> cell key
     * for O(1) updates.
     *
     * @section perf Performance
     * - insert/erase/update: O(1) expected.
     * - radius_query: visits ~ (2R/cell+1)^2 buckets, typically small when cell_size ~ target spacing.
     * - segment_query: Amanatides-Woo grid traversal; visits one bucket per crossed cell.
     *
     * @section usage Usage
     * @code
     * HashGrid2d<Vertex> grid(h);
     * grid.set_get_point([](const Vertex& v){ return std::array<double, 2>{v.x, v.y};});
     * std::size_t id = grid.insert(v);
     * grid.update(id);
     * std::vector<std::size_t> ids;
     * grid.radius_query(std::array{px, py}, r, ids);
     * @endcode
     */
    template <class T>
    class HashGrid2d {
    public:
        using Key = std::pair<int, int>;

        /**
         * @brief Construct a grid with a given cell size.
         * @param cell Square cell size in world units.
         *
         * @note Choose @p cell close to your target edge length for best performance.
         */
        explicit HashGrid2d(real cell);

        /**
         * @brief Set the point extractor used to read (x,y) from items of type T.
         * @param gp Function returning {x, y} for a given item.
         */
        void set_get_point(GetPointFn<T> gp) {get_point_ = std::move(gp);}

        /// Remove all buckets and items. Indices become invalid
        void clear();

        /**
         * @brief Insert an item into the grid.
         * @param item The item to store.
         * @return Stable item ID for subsequent operations.
         *
         * Average O(1). The item is appended and placed into the bucket of its current cell.
         */
        std::size_t insert(const T& item);

        /**
         * @brief Update an item's bucket after its position changed.
         * @param id Item ID returned by @ref insert.
         *
         * If the item remained in the same cell, this is a no-op.
         * Otherwise, it is unlinked from the old bucket and appended to the new one.
         */
        void update(std::size_t id);

        /**
         * @brief Erase an item from its bucket.
         * @param id Item ID returned by @ref insert.
         *
         * Removes @p id from its bucket. The underlying item slot remains allocated to keep
         * indices stable (tombstone). Add a compaction pass if needed for heavy churn workloads.
         */
        void erase(std::size_t id);

        /**
         * @brief Radius search around a point.
         * @tparam P Point-like type with operator[](0/1) -> real.
         * @param p Center {x,y}.
         * @param r Radius.
         * @param out_ids Output vector of candidate IDs within Euclidean distance <= r.
         *
         * Visits a small neighborhood of buckets around @p p and filters candidates by exact distance.
         * @complexity O(k + b) where b is the number of visited buckets and k is the number of matches.
         */
        template <PointLike P>
        void radius_query(const P& p, real r, std::vector<std::size_t>& out_ids) const;

        /**
         * @brief Axis-aligned bounding box query.
         * @tparam P Point-like type.
         * @param bmin Minimum corner {x, y}.
         * @param bmax Maximum corner {x, y}.
         * @param out_ids Output IDs of items inside the AABB.
         */
        template <PointLike P>
        void aabb_query(const P& bmin, const P& bmax, std::vector<std::size_t>& out_ids) const;

        /**
         * @brief March a segment through the grid and return candidate IDs in crossed cells.
         * @tparam P Point-like type.
         * @param a Segment start {x,y}.
         * @param b Segment end {x,y}.
         * @param out_ids Output IDs from all visited buckets (may contain duplicates).
         *
         * Uses Amanatides-Woo traversal. Caller should deduplicate @p out_ids if needed and then
         * perform exact intersection tests (e.g., segment-segment with robut predicates).
         */
        template <PointLike P>
        void segment_query(const P& a, const P& b, std::vector<std::size_t>& out_ids) const;

        /// Const access to an item by ID.
        const T& item(std::size_t id) const {return items_[id];}

        /// Mutable access to an item by ID (remember to call update(id) after moving).
        T& item(std::size_t id) {return items_[id];}

        /// Number of items currently stored (including tombstones if you leave them).
        TNB_NODISCARD std::size_t size() const {return items_.size();}

        /// Cell size used by the grid.
        TNB_NODISCARD real cell_size() const {return cell_size_;}

        /// Returns true if the ratio of dead slots is high enough to justify compaction.
        bool needs_compact(real dead_ratio_threshold = 0.25) const;
        void compact();
    private:
        /*Private Data*/

        /// Compute the bucket key for an item.
        Key key_of(const T& item) const;

        template <PointLike P>
        Key key_of_point(const P& p) const;

        real cell_size_{1.0};
        real inv_cell_{1.0};
        std::unordered_map<Key, std::vector<std::size_t>, utils::hash::PairHash> buckets_;
        std::vector<T> items_;
        mutable std::vector<Key> locate_;
        GetPointFn<T> get_point_ =
            [](const T& t) -> std::array<real, 2> {return {t.x, t.y};};
    };
}
#include <tonb/geometry/spatial/private/hash_grid_2d_imp.hxx>
#endif //TONB_GEOMETRY_SPATIAL_HASH_GRID_2D_HXX