//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_QUAD_MESH_2D_FWD_HXX
#define TONB_GEOMETRY_META_QUAD_MESH_2D_FWD_HXX
#include <cstdint>
#include <cstddef>
/**
 * @file
 * @brief Forward declarations for 2D quad mesh types
 *
 * This header declares the minimal types required to reference a 2D quad mesh
 * in function signatures without pulling full definitions. It forward--declares:
 * - `tonb::geometry::Pnt2d` — a 2D point type;
 * - `tonb::geometry::meta::Connectivity<N, Tag>` — fixed-arity element connectivity;
 * - `tonb::geometry::meta::GeometrySet<Point, IDs>` — a pair of point storage and
 *  element connectivity;
 *  and provides the alias `QuadMesh2d` for a quad mesh
 *  (`GeometrySet<Pnt2d, Connectivity<4, void>>`).
 *
 *  @note This is a **forward-only** header: include the corresponding implementation
 *        headers if you need to construct or iterate these types.
 */
namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;
    namespace meta {
        // Forward Declarations
        template<std::size_t N, class Tag>
        class Connectivity;

        template<class Point, class IDs>
        class GeometrySet;

        using QuadMesh2d = GeometrySet<Pnt2d, Connectivity<4, void>>;
    }
}
#endif //TONB_GEOMETRY_META_QUAD_MESH_2D_FWD_HXX