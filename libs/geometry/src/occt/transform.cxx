//
// Created by amir on 8/24/25.
//

#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/geometry/occt/transform.hxx>
#include <tonb/geometry/occt/point.hxx>
#include <tonb/geometry/occt/axis.hxx>
#include <tonb/geometry/occt/vector.hxx>
#include <tonb/geometry/occt/core/transform_helpers.hxx>
#include <tonb/geometry/occt/core/axis_helpers.hxx>

// OCCT
#include <opencascade/gp_Trsf.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Ax1.hxx>
#include <opencascade//gp_Vec.hxx>
#include <opencascade/gp_Dir.hxx>

#include "tonb/geometry/occt/core/point_helpers.hxx"
#include "tonb/geometry/occt/core/vector_helpers.hxx"

namespace tonb::geometry::occt {

    Transform::Transform() noexcept : pimpl_(std::make_shared<Impl>()) {}
    Transform Transform::identity() noexcept { return {}; }

    Transform Transform::from_translation(const real dx, const real dy, const real dz) noexcept {
        Transform t; t.pimpl_->t.SetTranslation(gp_Vec(dx, dy, dz)); return t;
    }

    Transform Transform::from_rotation(const Axis& axis, real radians) noexcept {
        Transform t;
        const auto o =axis.origin();
        const auto d = axis.direction();
        if (axis.is_valid()) t.pimpl_->t.SetRotation(
            gp_Ax1(core::occt_point_access::get(o), core::occt_vector_access::get(d)), radians);
        return t;
    }

    Transform Transform::from_uniform_scale(const Point &center, real scale) noexcept {
        Transform t;
        const auto a = center.xyz();
        t.pimpl_->t.SetScale(gp_Pnt(a[0], a[1], a[2]), scale);
        return t;
    }

    bool Transform::is_identity() const noexcept {
        return pimpl_->t.Form()==gp_Identity;
    }

    void Transform::to_matrix(Mat4 out) const noexcept {
        // gp_Trsf provides Value(row, col) in 1..3; translation is at (1..3,4); last row = [0 0 0 1]
        for (int r = 0; r < 3; ++r) { for (int c = 0; c < 3; ++c) out[r][c] = static_cast<real>(pimpl_->t.Value(r + 1, c + 1)); }
        out[0][3] = static_cast<real>(pimpl_->t.Value(1,4)); out[1][3] = static_cast<real>(pimpl_->t.Value(2, 4)); out[2][3] = static_cast<real>(pimpl_->t.Value(3, 4));
        out[3][0] = 0; out[3][1] = 0; out[3][2] = 0; out[3][3] = 1;
    }

    Transform Transform::multiplied(const Transform &other) const noexcept {
        Transform r; r.pimpl_->t = pimpl_->t*other.pimpl_->t; return r;
    }

    Transform Transform::inverse() const noexcept {
        Transform r; r.pimpl_->t = pimpl_->t; r.pimpl_->t.Invert(); return r;
    }

    Point Transform::transform_point(const Point &point) const noexcept {
        auto gp = core::occt_point_access::get(point);
        gp.Transform(pimpl_->t);
        return core::occt_point_access::make(gp);
    }

    Axis Transform::transform_axis(const Axis &axis) const noexcept {
        auto gpa = core::occt_axis_access::get(axis);
        gpa.Transform(pimpl_->t);
        return core::occt_axis_access::make(gpa);
    }
}
#else
static_assert(true, "src/occt/transform.cxx built without TONB_WITH_OCCT");
#endif