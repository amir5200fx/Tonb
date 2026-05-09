//
// Created by amir on 8/24/25.
//
#pragma once
#include <tonb/geometry/occt/curve.hxx>
#include <opencascade/Geom_Curve.hxx>

namespace tonb::geometry::occt {
    struct Curve::Impl {
        opencascade::handle<Geom_Curve> h;
    };
}

namespace tonb::geometry::occt::core {

    struct occt_curve_access {
        static Curve make(const opencascade::handle<Geom_Curve>& h) {
            if (h.IsNull()) return {};
            return Curve{std::make_shared<Curve::Impl>(Curve::Impl{h})};
        }
        static opencascade::handle<Geom_Curve> get(const Curve& curve) {
            return (curve.pimpl_ ? curve.pimpl_->h : nullptr);
        }
    };
}