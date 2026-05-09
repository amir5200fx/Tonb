//
// Created by amir on 30/09/2025.
//
#pragma once
#include <tonb/geometry/occt/axis2_2d.hxx>
#include <opencascade/gp_Ax22d.hxx>
namespace tonb::geometry::occt {
    //------- Impl ---------
    struct Axis22d::Impl {
        gp_Ax22d ax;
        bool has{false};
    };

    namespace core {
        struct occt_axis2_2d_access {
            static gp_Ax22d get(const Axis22d& a) {
                return a.is_valid() ? a.pimpl_->ax : gp_Ax22d();
            }
            static Axis22d make(const gp_Ax22d& ax) {
                Axis22d out;
                out.pimpl_ = std::make_shared<Axis22d::Impl>();
                out.pimpl_->ax = ax;
                out.pimpl_->has = true;
                return out;
            }
        };
    }


}