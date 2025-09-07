/**
* @file tri_mesh_2d.hxx
 * @brief Minimal 2D triangle mesh structure for geometry processing and spatial queries.
 *
 * This header defines the TriMesh2d struct, a lightweight container for
 * 2D triangle meshes with optional adjacency information. It is designed to be
 * generic and minimal, providing only the essential data and helpers required
 * by algorithms such as point location, interpolation, or mesh traversal.
 *
 * @details
 * Features:
 *  - Stores vertex positions in 2D and triangle indices (0-based).
 *  - Supports optional per-face adjacency (neighbouring triangles) via
 *    the @ref build_adjacency method.
 *  - Provides a convenient @ref v2 accessor to return vertex coordinates
 *    as a Vec2 type.
 *  - No external dependencies beyond the C++ standard library.
 *
 * Intended usage:
 *  - As an input mesh type for spatial algorithms such as
 *    @ref tonb::geometry::spatial::PointLocator2d.
 *  - For quick prototyping or integration into geometry-processing pipelines.
 *
 * Limitations:
 *  - Does not store per-vertex attributes, normals, or connectivity beyond
 *    direct adjacency.
 *  - Does not enforce manifoldness or orientation consistency.
 *
 * Namespace: tonb::geometry::spatial
 *
 * @note This type is intentionally simple and can be replaced or extended
 *       to suit application-specific mesh representations.
 */

#pragma once
#ifndef TONB_GEOMETRY_SPATIAL_TRI_MESH_2D_HXX
#define TONB_GEOMETRY_SPATIAL_TRI_MESH_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/geometry/vec_2d.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>


#include <vector>
#include <array>

namespace tonb::geometry::spatial {

    /**
     * @class TriMesh2d
     * @brief Minimal 2D triangle mesh container for geometry and spatial queries.
     *
     * @details
     * TriMesh2d is a lightweight, generic structure for representing a 2D triangle mesh.
     * It stores vertex coordinates and face indices, and can optionally store
     * triangle-to-triangle adjacency for traversal-based algorithms.
     *
     * Typical usage:
     *  - Pass to spatial search utilities such as @ref tonb::geometry::spatial::PointLocator2d.
     *  - Use as a generic mesh container for geometry processing or interpolation.
     *
     * Data members:
     *  - @ref V : Vertex positions in 2D (`|V| x 2` array of Real).
     *  - @ref F : Triangle indices (`|F| x 3` array of Index, 0-based).
     *  - @ref neighbors : Per-face adjacency, where `neighbors[f][e]` is the face across
     *    edge `e` of triangle `f`, or -1 if the edge lies on the mesh boundary.
     *  - @ref v2f : Optional per-vertex seed face index, useful for initialisation.
     *
     * Helper methods:
     *  - @ref v2 : Returns a vertex position as a `Vec2`.
     *  - @ref build_adjacency : Computes @ref neighbors from @ref F in O(|F| log |F|) time.
     *
     * @note
     *  - This class does not enforce manifoldness or mesh orientation.
     *  - Only contains the minimal fields required by point-location and similar algorithms.
     *  - Can be extended with additional attributes (normals, colours, etc.) if needed.
     *
     * @see tonb::geometry::spatial::PointLocator2d
     */
    struct TriMesh2d {

        std::vector<std::array<real, 2>> V;             ///< Vertex positions
        std::vector<std::array<index_t, 3>> F;          ///< Triangle vertex indices (0-based)
        std::vector<std::array<index_t, 3>> neighbors;  ///< Adjacent face across each edge, or -1

        /// Optional: seed face per vertex (not required by the locator, but handy for custom seeding).
        std::vector<index_t> v2f;

        /**
         * @brief Get the 2D position of a vertex.
         *
         * @param vi Index of the vertex (0-based).
         * @return Vec2 The (x, y) coordinates of the vertex.
         *
         * @note This is a lightweight accessor that simply wraps V[vi]
         *       into a Vec2 object.
         */
        inline Vec2d v2(const index_t vi) const { return {V[vi][0], V[vi][1]}; }

        /**
         * @brief Build the triangle-to-triangle adjacency list.
         *
         * @details
         * For each triangle face f and each of its three edges e:
         *  - If another triangle shares that edge, `neighbors[f][e]` is set to
         *    the index of the adjacent triangle.
         *  - If the edge lies on the boundary of the mesh, `neighbors[f][e]` is set to -1.
         *
         * The adjacency is determined purely from vertex indices, ignoring edge orientation.
         * Duplicate or degenerate triangles may result in undefined adjacency.
         *
         * @post
         *  - @ref neighbors is resized to match the number of faces and filled with adjacency data.
         *  - @ref v2f is resized to match the number of vertices and filled with the first face index
         *    that contains each vertex (or -1 if the vertex is unused).
         *
         * @complexity O(|F| log |F|) due to the map-based edge look-up.
         *
         * @warning This method does not check for non-manifold edges or inconsistent orientation.
         */
        TNBGEOM_EXPORT void build_adjacency();
    };
}
#endif //TONB_GEOMETRY_SPATIAL_TRI_MESH_2D_HXX