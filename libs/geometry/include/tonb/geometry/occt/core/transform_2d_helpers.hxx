//
// Created by amir on 8/27/25.
//
#pragma once
#include <tonb/geometry/occt/transform_2d.hxx>
#include <opencascade/gp_Trsf2d.hxx>

namespace tonb::geometry::occt {
    struct Transform2d::Impl{gp_Trsf2d t;};
}
namespace tonb::geometry::occt::core {
    // interop
    struct occt_trsf_2d_access {
        static Transform2d make(const gp_Trsf2d& t) {
            Transform2d r; r.pimpl_->t = t; return r;
        }
        static gp_Trsf2d get(const Transform2d& t) {
            return t.pimpl_->t;
        }
    };
}