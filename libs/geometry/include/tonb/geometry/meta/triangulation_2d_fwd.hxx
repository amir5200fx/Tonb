//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_TRIANGULATION_2D_FWD_HXX
#define TONB_GEOMETRY_META_TRIANGULATION_2D_FWD_HXX
#include <cstddef>
/**
 * @file
 * @brief Forward declarations for 2D triangulation types.
 *
 * This header declares the minimal types required to reference a 2D triangle
 * mesh in function signatures without pulling full definitions. It forward-declares:
 * - `tonb::geometry::Pnt2d` — a 2D point type;
 * - `tonb::geometry::meta::Connectivity<N, Tag>` — fixed-arity element connectivity;
 * - `tonb::geometry::meta::GeometrySet<Point, IDs>` — a pair of point storage and
 *   element connectivity;
 * and provides the alias `Triangulation2d` for a triangle mesh
 * (`GeometrySet<Pnt2d, Connectivity<3, void>>`).
 *
 * @note This is a **forward-only** header: include the corresponding implementation
 *       headers if you need to construct or iterate these types.
 */
namespace tonb::geometry {
    // Forward Declarations
    class Pnt2d;
    namespace meta {
        // Forward Declarations
        template<std::size_t, class Tag>
        class Connectivity;

        template<class Point, class IDs>
        class GeometrySet;

        using Triangulation2d = GeometrySet<Pnt2d, Connectivity<3, void>>;
    }
}
#endif //TONB_GEOMETRY_META_TRIANGULATION_2D_FWD_HXX