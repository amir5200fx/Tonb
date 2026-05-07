//
// Created by amir on 8/24/25.
//
#pragma once
#include <tonb/geometry/occt/axis.hxx>
#include <opencascade/gp_Ax1.hxx>

namespace tonb::geometry::occt {
    struct Axis::Impl {
        gp_Ax1 ax;
        bool valid{true};
    };
}

namespace tonb::geometry::occt::core {
    struct occt_axis_access {
        static Axis make(const gp_Ax1& ax) {
            auto impl = std::make_shared<Axis::Impl>();
            impl->ax = ax;
            // gp_Ax1 always carries a dir; treat as valid.
            impl->valid = true;
            return Axis{std::move(impl)};
        }
        static gp_Ax1 get(const Axis& a) {
            return a.pimpl_ ? a.pimpl_->ax : gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
        }
    };
}