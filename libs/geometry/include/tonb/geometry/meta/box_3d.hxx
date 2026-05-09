//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_BOX_3D_HXX
#define TONB_GEOMETRY_META_BOX_3D_HXX

#include <tonb/geometry/meta/box_3d_fwd.hxx>
#include <tonb/geometry/meta/box.hxx>
#include <tonb/geometry/pnt_3d.hxx>

namespace tonb::geometry::meta {

    template<>
    struct Box3d::Utility {
        enum class Volume {
            half_down,
            half_top,
            half_left,
            half_right,
            half_front,
            half_back,
            fwd_eighth_down_left,
            fwd_eighth_down_right,
            fwd_eighth_top_left,
            fwd_eighth_top_right,
            bwd_eighth_down_left,
            bwd_eighth_down_right,
            bwd_eighth_top_left,
            bwd_eighth_top_right
        };

        enum class Corner {
            fwd_down_left,
            fwd_down_right,
            fwd_top_left,
            fwd_top_right,
            bwd_down_left,
            bwd_down_right,
            bwd_top_left,
            bwd_top_right
        };
    };


    /**
     * @brief Return a named sub-box (half or octant) of this 3D axis-aligned box.
     *
     * Full specialization of `Box3d::subdivide<U>()` for
     * `U = Box3d::Utility::Volume`. The function constructs the requested
     * sub-volume using the current box’s corners, edge/face midpoints, and center.
     *
     * Conventions:
     * - `corner1()` = (xmin, ymin, zmin), `corner2()` = (xmax, ymax, zmax)
     * - `left/right`  → xmin/xmax, `down/top` → ymin/ymax, `bwd/fwd` → zmin/zmax
     * - `avg(A,B)` is the component-wise midpoint of points A and B
     *
     * Halves (split along one axis):
     * - `half_down`  → `{ corner1(),  avg(corner(fwd_down_right),  corner(fwd_top_right)) }`
     * - `half_top`   → `{ avg(corner(bwd_down_left),  corner(bwd_top_left)),  corner2() }`
     * - `half_left`  → `{ corner1(),  avg(corner(fwd_top_left),    corner(fwd_top_right)) }`
     * - `half_right` → `{ avg(corner(bwd_down_left), corner(bwd_down_right)), corner2() }`
     * - `half_back`  → `{ corner1(),  avg(corner(bwd_top_right),   corner(fwd_top_right)) }`
     * - `half_front` → `{ avg(corner(bwd_down_left), corner(fwd_down_left)),  corner2() }`
     *
     * Octants (eighths = half × half × half):
     * - `bwd_eighth_down_left`  → `{ corner1(), center() }`
     * - `bwd_eighth_down_right` → `{ avg(corner1(), corner(bwd_down_right)),  avg(corner2(), corner(bwd_down_right)) }`
     * - `bwd_eighth_top_right`  → `{ avg(corner1(), corner(bwd_top_right)),   avg(corner2(), corner(bwd_top_right)) }`
     * - `bwd_eighth_top_left`   → `{ avg(corner1(), corner(bwd_top_left)),    avg(corner2(), corner(bwd_top_left)) }`
     * - `fwd_eighth_down_left`  → `{ avg(corner1(), corner(fwd_down_left)),   avg(corner2(), corner(fwd_down_left)) }`
     * - `fwd_eighth_down_right` → `{ avg(corner1(), corner(fwd_down_right)),  avg(corner2(), corner(fwd_down_right)) }`
     * - `fwd_eighth_top_right`  → `{ center(), corner2() }`
     * - `fwd_eighth_top_left`   → `{ avg(corner1(), corner(fwd_top_left)),    avg(corner2(), corner(fwd_top_left)) }`
     *
     * @param sub Selector from `Utility::Volume` indicating which half or octant to return.
     * @return Box3d The requested sub-box; if @p sub is not recognized, returns a
     *         default-constructed (empty) box.
     *
     * @pre The box is valid with `corner1()` as the minimum corner and `corner2()` as the maximum.
     * @note Edges and faces are shared between adjacent sub-boxes; boundary inclusion
     *       follows the default `Box3d` semantics.
     * @complexity O(1)
     * @see Utility::Volume, Utility::Corner, center(), avg(), corner(), corner1(), corner2()
     */
    template<>
    template<>
    TNBGEOM_ND_EXPORT Box3d Box3d::subdivide<Box3d::Utility::Volume>(Utility::Volume sub) const;

    /**
     * @brief Return the coordinates of a named 3D corner of this axis-aligned box.
     *
     * Full specialization of `Box3d::corner<U>()` for `U = Box3d::Utility::Corner`.
     * Corners are defined relative to the box extrema:
     * `corner1()` = (xmin, ymin, zmin) and `corner2()` = (xmax, ymax, zmax).
     *
     * Mapping:
     * - `fwd_down_left`  → (xmin, ymin, zmax) = `{ p0.x(), p0.y(), p1.z() }`
     * - `fwd_down_right` → (xmax, ymin, zmax) = `{ p1.x(), p0.y(), p1.z() }`
     * - `fwd_top_right`  → (xmax, ymax, zmax) = `p1`
     * - `fwd_top_left`   → (xmin, ymax, zmax) = `{ p0.x(), p1.y(), p1.z() }`
     *
     * - `bwd_down_left`  → (xmin, ymin, zmin) = `p0`
     * - `bwd_down_right` → (xmax, ymin, zmin) = `{ p1.x(), p0.y(), p0.z() }`
     * - `bwd_top_right`  → (xmax, ymax, zmin) = `{ p1.x(), p1.y(), p0.z() }`
     * - `bwd_top_left`   → (xmin, ymax, zmin) = `{ p0.x(), p1.y(), p0.z() }`
     *
     * Conventions: “left/right” → xmin/xmax, “down/top” → ymin/ymax,
     * “bwd/fwd” → zmin/zmax.
     *
     * @param c Corner selector from `Utility::Corner`.
     * @return Pnt3d The requested corner point; if @p c is not recognized,
     *         a default-constructed point is returned.
     *
     * @pre The box is valid with `corner1()` as the minimum and `corner2()` as the maximum.
     * @see corner1(), corner2(), Utility::Corner
     */
    template<>
    template<>
    TNBGEOM_ND_EXPORT Pnt3d Box3d::corner<Box3d::Utility::Corner>(Utility::Corner c) const;
}

#endif //TONB_GEOMETRY_META_BOX_3D_HXX