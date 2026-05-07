//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/geometry/occt/transform_2d.hxx>
#include <tonb/geometry/occt/point_2d.hxx>
#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/vector_2d.hxx>
#include <tonb/geometry/occt/direction_2d.hxx>
#include <tonb/geometry/occt/core/transform_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>

// OCCT
#include <opencascade/gp_Trsf2d.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Ax2d.hxx>
#include <opencascade//gp_Vec2d.hxx>


namespace tonb::geometry::occt {

    Transform2d::Transform2d() noexcept : pimpl_(std::make_shared<Impl>()) {}
    Transform2d Transform2d::identity() noexcept { return {}; }

    Transform2d Transform2d::from_translation(const real dx, const real dy) noexcept {
        Transform2d t; t.pimpl_->t.SetTranslation(gp_Vec2d(dx, dy)); return t;
    }

    Transform2d Transform2d::from_rotation(const Axis2d& axis, real radians) noexcept {
        Transform2d t;
        const auto o =axis.origin();
        const auto d = axis.direction();
        if (axis.is_valid()) t.pimpl_->t.SetRotation(
            core::occt_point_2d_access::get(o), radians);
        return t;
    }

    Transform2d Transform2d::from_uniform_scale(const Point2d &center, real scale) noexcept {
        Transform2d t;
        const auto a = center.xy();
        t.pimpl_->t.SetScale(gp_Pnt2d(a[0], a[1]), scale);
        return t;
    }

    bool Transform2d::is_identity() const noexcept {
        return pimpl_->t.Form()==gp_Identity;
    }


    Transform2d Transform2d::multiplied(const Transform2d &other) const noexcept {
        Transform2d r; r.pimpl_->t = pimpl_->t*other.pimpl_->t; return r;
    }

    Transform2d Transform2d::inverse() const noexcept {
        Transform2d r; r.pimpl_->t = pimpl_->t; r.pimpl_->t.Invert(); return r;
    }

    Point2d Transform2d::transform_point(const Point2d &point) const noexcept {
        auto gp = core::occt_point_2d_access::get(point);
        gp.Transform(pimpl_->t);
        return core::occt_point_2d_access::make(gp);
    }

    Axis2d Transform2d::transform_axis(const Axis2d &axis) const noexcept {
        auto gpa = core::occt_axis_2d_access::get(axis);
        gpa.Transform(pimpl_->t);
        return core::occt_axis_2d_access::make(gpa);
    }
}
#else
static_assert(true, "src/occt/transform_2d.cxx built without TONB_WITH_OCCT");
#endif