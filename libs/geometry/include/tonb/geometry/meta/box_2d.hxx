//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_BOX_2D_HXX
#define TONB_GEOMETRY_META_BOX_2D_HXX

#include <tonb/geometry/meta/box_2d_fwd.hxx>
#include <tonb/geometry/meta/box.hxx>
#include <tonb/geometry/pnt_2d.hxx>

namespace tonb::geometry::meta {

    template<>
    struct Box<Pnt2d>::Utility {
        enum class Area {
            half_down,
            half_top,
            half_left,
            half_right,
            quarter_down_left,
            quarter_down_right,
            quarter_top_left,
            quarter_top_right
        };
        enum class Corner {
            down_left = 0,
            down_right = 1,
            top_left = 2,
            top_right = 3
        };
    };

    /**
     * @brief Return a named sub-rectangle (half or quarter) of this box.
     *
     * Full specialization of Box2d::subdivide<U>() for
     * U = Box2d::Utility::Area. The function builds and returns the axis-aligned
     * sub-box selected by @p sub using the current box's corners, edge mid-points, and center.
     *
     * The mapping is:
     * - 'half_down'        ->  '{ corner1(), avg(corner(down_right), corner(top-right))}'
     * - 'half_top'         ->  '{ avg(corner(down_left), corner(top_left)), corner2() }'
     * - 'half_left'        ->  '{ corner1(), avg(corner(top_left), corner(top_right)) }'
     * - 'half_right'       ->  '{ avg(corner(down_left), corner(down_right)), corner2() }'
     * - `quarter_down_left` -> `{ corner1(), center() }`
     * - `quarter_down_right`-> `{ avg(corner(down_left), corner(down_right)), avg(corner(down_right), corner(top_right)) }`
     * - `quarter_top_right` -> `{ center(), corner2() }`
     * - `quarter_top_left`  -> `{ avg(corner(down_left), corner(top_left)),  avg(corner(top_left), corner(top_right)) }`
     *
     * Corner names follow `Utility::Corner`:
     * `down_left`, `down_right`, `top_left`, `top_right`. “down” corresponds to
     * the minimum Y of the box and “top” to the maximum Y.
     *
     * @param sub Region selector from `Utility::Area`.
     * @return Box2d The requested sub-box. If @p sub is not a recognized enumerator,
     *         a default-constructed (empty) box is returned.
     *
     * @pre The box must be valid (corner1() is the min corner, corner2() the max).
     * @note Edges are shared between adjacent sub-boxes; inclusion of boundary
     *       points follows the default `Box2d` semantics.
     * @see Utility::Area, Utility::Corner, corner1(), corner2(), corner(), center(), avg().
     */
    template<>
    template<>
    TNBGEOM_ND_EXPORT Box<Pnt2d> Box2d::subdivide<Box2d::Utility::Area>(Utility::Area sub) const;

    /**
     * @brief Return the coordinates of a named corner of this 2D axis-aligned box.
     *
     * Full specialization of `Box2d::corner<U>()` for
     * `U = Box2d::Utility::Corner`. Corners are defined with respect to the box
     * extrema: `corner1()` is the minimum (xmin, ymin) and `corner2()` is the
     * maximum (xmax, ymax).
     *
     * Mapping:
     * - `down_left`  → `corner1()`                    // (xmin, ymin)
     * - `down_right` → `{ corner2().x(), corner1().y() }` // (xmax, ymin)
     * - `top_right`  → `corner2()`                    // (xmax, ymax)
     * - `top_left`   → `{ corner1().x(), corner2().y() }` // (xmin, ymax)
     *
     * “down” corresponds to the minimum Y; “top” to the maximum Y.
     * “left” corresponds to the minimum X; “right” to the maximum X.
     *
     * @param c Corner selector from `Utility::Corner`.
     * @return Pnt2d The requested corner point; if @p c is not recognized,
     *               a default-constructed point is returned.
     *
     * @pre The box must be valid such that `corner1()` is the min corner and
     *      `corner2()` is the max corner.
     * @see corner1(), corner2(), Utility::Corner
     */
    template<>
    template<>
    TNBGEOM_ND_EXPORT Pnt2d Box2d::corner<Box2d::Utility::Corner>(Utility::Corner c) const;
}

#endif //TONB_GEOMETRY_META_BOX_2D_HXX