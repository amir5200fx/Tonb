//
// Created by amir on 8/26/25.
//
#pragma once
#include <tonb/geometry/occt/curve_2d.hxx>
#include <opencascade/Geom2d_Curve.hxx>

namespace tonb::geometry::occt {
    struct Curve2d::Impl {
        Handle(Geom2d_Curve) h;
    };
}

namespace tonb::geometry::occt::core {
    struct occt_curve_2d_access {
        static Curve2d make(const Handle(Geom2d_Curve)& h) {
            if (h.IsNull()) return {};
            return Curve2d(std::make_shared<Curve2d::Impl>(Curve2d::Impl{h}));
        }
        static Handle(Geom2d_Curve) get(const Curve2d& curve) {
            return (curve.pimpl_ ? curve.pimpl_->h : nullptr);
        }
    };
}