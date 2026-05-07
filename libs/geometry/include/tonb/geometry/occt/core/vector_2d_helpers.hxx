//
// Created by amir on 8/27/25.
//
#pragma once
#include <tonb/geometry/occt/vector_2d.hxx>
#include <tonb/geometry/vec_2d.hxx>
#include <opencascade/gp_Vec2d.hxx>

namespace tonb::geometry::occt {
    struct Vector2d::Impl {gp_Vec2d v;};
}
namespace tonb::geometry::occt::core {
    struct occt_vector_2d_access {
        static Vector2d make(const gp_Vec2d& v) {
            return {static_cast<real>(v.X()), static_cast<real>(v.Y())};
        }
        static gp_Vec2d get(const Vector2d& v) {
            return v.pimpl_ ? v.pimpl_->v : gp_Vec2d();
        }
    };
}