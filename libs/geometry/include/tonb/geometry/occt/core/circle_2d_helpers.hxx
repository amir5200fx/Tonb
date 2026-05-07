//
// Created by amir on 30/09/2025.
//
#pragma once
#include <tonb/geometry/occt/circle_2d.hxx>
#include <opencascade/gp_Circ2d.hxx>

namespace tonb::geometry::occt {
    struct Circle2D::Impl {
        gp_Circ2d c;
        bool has{false};
    };

    namespace core {
        struct occt_circle_2d_access {
            static gp_Circ2d get(const Circle2D& c) {
                return c.is_valid() ? c.pimpl_->c : gp_Circ2d();
            }
            static Circle2D make(const gp_Circ2d& c) {
                Circle2D out;
                out.pimpl_ = std::make_shared<Circle2D::Impl>();
                out.pimpl_->c = c;
                out.pimpl_->has = true;
                return out;
            }
        };
    }
}