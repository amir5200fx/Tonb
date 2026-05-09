//
// Created by amir on 8/24/25.
//
#pragma once

#include <tonb/geometry/occt/point.hxx>
#include <tonb/geometry/pnt_3d.hxx>
#include <opencascade/gp_Pnt.hxx>
namespace tonb::geometry::occt {
    struct Point::Impl {gp_Pnt p;};
}
namespace tonb::geometry::occt::core {
    struct occt_point_access {
        static Point make(const gp_Pnt& p) {
            return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
        }
        static gp_Pnt get(const Point& pt) {
            return (pt.pimpl_ ? pt.pimpl_->p : gp_Pnt());
        }
    };
}