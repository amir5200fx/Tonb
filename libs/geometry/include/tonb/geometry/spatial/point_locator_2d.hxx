/**
* @file point_locator_2d.hxx
 * @brief Locate a point in a 2D triangle mesh using a uniform-grid broad phase + triangle walking.
 *
 * This component is a lightweight, header-only point locator built on
 * - a reusable @ref UniformGrid2d (broad phase over triangle AABBs)
 * - a robust barycentric test + neighbour "walking" strategy (narrow phase)
 *
 * Dependencies: STL + tonb base typedefs + @ref TriMesh2d + @ref UniformGrid2d.
 */
#pragma once
#ifndef TONB_POINT_LOCATOR_2D_HXX
#define TONB_POINT_LOCATOR_2D_HXX

#include <tonb/geometry/spatial/uniform_grid_2d.hxx>

#include <vector>
#include <array>
#include <cmath>
#include <limits>
#include <map>
#include <algorithm>

namespace tonb::geometry::spatial {

    // Forward Declarations
    class TriMesh2d;

    /**
     * @class PointLocator2d
     * @brief Locate a point in a 2D triangle mesh (face + barycentrics) using @ref UniformGrid2d + walking.
     *
     * @section algo Algorithm
     *  1. Build a uniform grid over the mesh domain and insert each triangle by its AABB.
     *  2. For a query point, fetch the bucket from the grid and choose the nearest-centroid triangle as seed
     *     (fallback to global nearest centroid if the bucket is empty).
     *  3. Compute barycentrics; if all >= 0, return. Otherwise, step across the edge opposite the most
     *     negative weight (if neighbour exists) and repeat. On boundary, return clamped barycentrics.
     *
     * @section perf Performance
     *  Average near O(1) per query for well-shaped meshes; worst case proportional to local mesh diameter.
     *
     * @note This class is independent of `Vec2d`; it operates on raw doubles from @ref TriMesh2d.
     */
    class PointLocator2d {

    public:

        /**
         * @brief Result of a point-location query: triangle id + barycentric weights.
         */
        struct Result {
            index_t triangle_id{-1};
            std::array<real, 3> bary{0, 0, 0};
        };

    private:

        /*Private Data*/
        const TriMesh2d& M_;
        UniformGrid2d grid_;

    public:

        /**
         * @brief Construct the locator.
         * @param mesh A reference to @ref TriMesh2d (must outlive the locator).
         * @param grid_cells_per_axis If > 0, explicit resolution; otherwise an automatic choice from |F|.
         */
        TNBGEOM_EXPORT explicit PointLocator2d(const TriMesh2d& mesh, int grid_cells_per_axis = -1);

        /**
         * @brief Locate a point.
         * @param px, py Query point coordinates.
         * @param seed_face Optional seed triangle id. If negative/invalid, a seed is chosen automatically
         * @param max_hops Safety limit on neighbour steps.
         * @return The face index and barycentric weights (clamped on boundary(.
         */
        TNBGEOM_ND_EXPORT Result locate(real px, real py, index_t seed_face = -1, index_t max_hops = 128) const;
    };
}

#endif //TONB_POINT_LOCATOR_2D_HXX