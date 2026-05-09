//
// Created by amir on 28/08/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_HXX
#define TONB_GEOMETRY_OCCT_HXX

#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/geometry/pnt_3d.hxx>
#include <tonb/geometry/occt/point.hxx>
#include <tonb/geometry/occt/point_2d.hxx>
#include <tonb/geometry/occt/vector_2d.hxx>
#include <tonb/geometry/occt/vector.hxx>

#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/axis.hxx>

namespace tonb::geometry::occt {
    inline Point2d to_gp(const Pnt2d& pt) {
        return Point2d{pt.components()};
    }
    inline Point to_gp(const Pnt3d& pt) {
        return Point{pt.components()};
    }
    inline Pnt2d from_gp(const Point2d& pt) {
        return Pnt2d{pt.xy()};
    }
    inline Pnt3d from_gp(const Point& pt) {
        return Pnt3d{pt.xyz()};
    }

    struct gp {
        inline static const Point2d origin2d = {0, 0};
        inline static const Point origin = {0, 0, 0};

        inline static const Vector2d dx2d = {1, 0};
        inline static const Vector2d dy2d = {0, 1};

        inline static const Vector dx = {1, 0, 0};
        inline static const Vector dy = {0, 1, 0};
        inline static const Vector dz = {0, 0, 1};

        inline static const Axis2d ox2d = Axis2d::from_point_dir(origin2d, dx2d);
        inline static const Axis2d oy2d = Axis2d::from_point_dir(origin2d, dy2d);

        inline static const Axis ox = Axis::from_point_dir(origin, dx);
        inline static const Axis oy = Axis::from_point_dir(origin, dy);
        inline static const Axis oz = Axis::from_point_dir(origin, dz);
    };
}

#endif  // TONB_GEOMETRY_OCCT_HXX
