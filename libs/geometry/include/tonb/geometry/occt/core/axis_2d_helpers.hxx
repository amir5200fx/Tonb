//
// Created by amir on 8/27/25.
//
#pragma once
#include <tonb/geometry/occt/axis_2d.hxx>
#include <opencascade/gp_Ax2d.hxx>

namespace tonb::geometry::occt {
    struct Axis2d::Impl {
        gp_Ax2d ax;
        bool valid{true};
    };
}

namespace tonb::geometry::occt::core {
    struct occt_axis_2d_access {
        static Axis2d make(const gp_Ax2d& ax) {
            // gp_Ax1 always carries a dir; treat as valid.
            Axis2d r; r.pimpl_->ax = ax; r.pimpl_->valid = true;
            return r;
        }
        static gp_Ax2d get(const Axis2d& a) {
            return a.pimpl_ ? a.pimpl_->ax : gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(1,0));
        }
    };
}