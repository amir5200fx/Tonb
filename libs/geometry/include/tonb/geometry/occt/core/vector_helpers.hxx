//
// Created by amir on 8/24/25.
//
#pragma once
#include <tonb/geometry/occt/vector.hxx>
#include <tonb/geometry/vec_3d.hxx>
#include <opencascade/gp_Vec.hxx>

namespace tonb::geometry::occt {
    struct Vector::Impl {gp_Vec v;};
}
namespace tonb::geometry::occt::core {
    struct occt_vector_access {
        static Vector make(const gp_Vec& v) {
            return Vector(std::array{static_cast<real>(v.X()), static_cast<real>(v.Y()), static_cast<real>(v.Z())});
        }
        static gp_Vec get(const Vector& v) {
            return v.pimpl_ ? v.pimpl_->v : gp_Vec();
        }
    };
}