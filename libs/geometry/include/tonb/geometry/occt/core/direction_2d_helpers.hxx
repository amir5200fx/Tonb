//
// Created by amir on 30/09/2025.
//
#pragma once
#include <tonb/geometry/occt/direction_2d.hxx>
#include <opencascade/gp_Dir2d.hxx>
namespace tonb::geometry::occt {
    struct Direction2d::Impl {
        gp_Dir2d d;
        bool has{false};
    };

    namespace core {
        struct occt_dir_2d_access {
            static gp_Dir2d get(const Direction2d& d) {
                return d.is_valid() ? d.pimpl_->d : gp_Dir2d(1.0, 0.0);
            }
            static Direction2d make(const gp_Dir2d& gd) {
                Direction2d out;
                out.pimpl_ = std::make_shared<Direction2d::Impl>();
                out.pimpl_->d = gd;
                out.pimpl_->has = true;
                return out;
            }
        };
    }
}