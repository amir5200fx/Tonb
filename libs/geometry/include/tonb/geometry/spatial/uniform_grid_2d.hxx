/**
* @file uniform_grid_2d.hxx
 * @brief Lightweight 2D uniform grid for spatial binning and candidate queries.
 *
 * Generic, header-only grid: you insert items by AABB, and later query by point or AABB.
 * Useful as a broad-phase accelerator for point location, ray casting, range queries, etc.
 */
#pragma once
#ifndef TONB_UNIFORM_GRID_2D_HXX
#define TONB_UNIFORM_GRID_2D_HXX

#include <tonb/geometry/vec_2d.hxx>
#include <tonb/geometry/meta/box_2d_fwd.hxx>
#include <tonb/base/index_types.hxx>

#include <vector>
#include <array>
#include <cmath>
#include <limits>
#include <algorithm>

namespace tonb::geometry::spatial {

    /**
     * @class UniformGrid2d
     * @brief Fixed-resolution uniform grid over a 2D domain for broad-phase queries.
     *
     * @details
     * - Build with a domain box and resolution (nx, ny).
     * - Insert items by their AABB (id + box). The grid stores only IDs in cell buckets.
     * - Query by point (cell) or by AABB (range of cells) to obtain candidate IDs.
     *
     * @note The grid is agnostic to what an "ID" refers to (triangle index, point index, etc.).
     *       De-duplication of candidates from multi-cell coverage is **not** performed; callers
     *       can deduplicate if needed.
     */
    class UniformGrid2d {
        /*Private Data*/

        Vec2d min_{0, 0}, max_{1, 1};
        int nx_{1}, ny_{1};
        real hx_{1}, hy_{1};
        bool built_{false};
        std::vector<std::vector<index_t>> buckets_;

        // Private functions and operators

        inline size_t index(int i, int j) const {return static_cast<size_t>(j * nx_ + i);}

        inline std::pair<int, int> to_idx(const Vec2d& p) const {
            const real px = (p.u() - min_.u()) / hx_;
            const real py = (p.v() - min_.v()) / hy_;
            return {static_cast<int>(std::floor(px)), static_cast<int>(std::floor(py))};
        }

        inline std::pair<int, int> clamp_idx(const std::pair<int, int>& ij) const {
            const int i = std::max(0, std::min(nx_- 1, ij.first));
            const int j = std::max(0, std::min(ny_ - 1, ij.second));
            return {i, j};
        }
    public:

        // default constructor
        UniformGrid2d() = default;

        /**
         * @brief Initialise the grid.
         * @param domain Axis-aligned bounding box of the full domain.
         * @param nx     Grid cells along x (>=1)
         * @param ny     Grid cells along y (>=1)
         */
        TNBGEOM_EXPORT void build(const meta::Box2d& domain, int nx, int ny);

        /**
         * @brief Insert an item by its axis-aligned bounding box
         * @param id Item identifier to store in covered cells.
         * @param box Item AABB (in same coordinate system as build())
         */
        TNBGEOM_EXPORT void insert(index_t id, const meta::Box2d& box);

        /**
         * @brief Gather candidate IDs overlapping on AABB region.
         * @param region Query AABB.
         * @param out Output vector to append IDs into (not deduplicated).
         */
        TNBGEOM_EXPORT void query_aabb(const meta::Box2d& region, std::vector<index_t>& out) const;

        /**
         * @brief Fetch candidate IDs from the cell containing a point.
         * @param p The query point.
         * @return A const reference to the bucket of IDs for that cell (may be empty).
         */
        TNBGEOM_EXPORT const std::vector<index_t>& query_cell(const Vec2d& p) const;

        /// @return Grid resolution (nx, ny).
        std::array<int,2> dims() const { return {nx_, ny_}; }

        /// @return Cell size (hx, hy).
        std::array<real ,2> cell_size() const { return {hx_, hy_}; }

        /// @return Domain AABB.
        TNBGEOM_ND_EXPORT meta::Box2d domain() const;

    };
}
#endif //TONB_UNIFORM_GRID_2D_HXX