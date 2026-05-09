//
// Created by amir on 8/27/25.
//
#pragma once
#include <tonb/geometry/occt/point_2d.hxx>
#include <tonb/geometry/pnt_2d.hxx>
#include <opencascade/gp_Pnt2d.hxx>
namespace tonb::geometry::occt {
    struct Point2d::Impl {gp_Pnt2d p;};
}
namespace tonb::geometry::occt::core {
    struct occt_point_2d_access {
        static Point2d make(const gp_Pnt2d& p) {
            return {static_cast<real>(p.X()), static_cast<real>(p.Y())};
        }
        static gp_Pnt2d get(const Point2d& p) {
            return (p.pimpl_ ? p.pimpl_->p : gp_Pnt2d());
        }
    };
}