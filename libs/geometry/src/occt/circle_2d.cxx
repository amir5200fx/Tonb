//
// Created by amir on 30/09/2025.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/core/circle_2d_helpers.hxx>
#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>
#include <tonb/geometry/occt/core/axis2_2d_helpers.hxx>

#include <opencascade/gp_Circ2d.hxx>
#include <opencascade/gp_Ax2d.hxx>

#include <cmath>

namespace tonb::geometry::occt {
    Circle2D::Circle2D(const Point2d &centre, const real radius) : pimpl_(std::make_shared<Impl>()) {
        pimpl_->c = gp_Circ2d(gp_Ax2d{core::occt_point_2d_access::get(centre), gp_Dir2d(1.0, 0.0)}, radius);
        pimpl_->has = true;
    }

    Circle2D::Circle2D(const Axis22d &axis, const real radius) : pimpl_(std::make_shared<Impl>()) {
        pimpl_->c = gp_Circ2d(core::occt_axis2_2d_access::get(axis), radius);
        pimpl_->has = true;
    }

    Circle2D::Circle2D(const Axis2d &axis, real radius, bool sense) : pimpl_(std::make_shared<Impl>()) {
        pimpl_->c = gp_Circ2d(core::occt_axis_2d_access::get(axis), radius, sense);
        pimpl_->has = true;
    }

    bool Circle2D::is_valid() const noexcept {
        return s_valid(pimpl_);
    }

    Point2d Circle2D::centre() const noexcept {
        if (!is_valid()) return {};
        return core::occt_point_2d_access::make(pimpl_->c.Location());
    }

    Axis22d Circle2D::axis() const noexcept {
        if (!is_valid()) return {};
        return core::occt_axis2_2d_access::make(pimpl_->c.Axis());
    }

    real Circle2D::radius() const noexcept {
        if (!is_valid()) return 0;
        return static_cast<real>(pimpl_->c.Radius());
    }

    real Circle2D::area() const noexcept {
        if (!is_valid()) return 0;
        return static_cast<real>(pimpl_->c.Area());
    }

    real Circle2D::length() const noexcept {
        if (!is_valid()) return 0;
        return static_cast<real>(pimpl_->c.Length());
    }

    Circle2D Circle2D::with_centre(const Point2d &centre) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.SetLocation(core::occt_point_2d_access::get(centre));
        return n;
    }

    Circle2D Circle2D::with_radius(const real radius) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.SetRadius(radius);
        return n;
    }

    Circle2D Circle2D::mirrored(const Point2d & p) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.Mirror(core::occt_point_2d_access::get(p));
        return n;
    }

    Circle2D Circle2D::mirrored(const Axis2d & a) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.Mirror(core::occt_axis_2d_access::get(a));
        return n;
    }

    Circle2D Circle2D::rotated(const Point2d &about, const real angle) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.Rotate(core::occt_point_2d_access::get(about), angle);
        return n;
    }

    Circle2D Circle2D::scaled(const Point2d &about, const real s) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.Scale(core::occt_point_2d_access::get(about), s);
        return n;
    }

    Circle2D Circle2D::translated(const real dx, const real dy) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->c.Translate(gp_Vec2d(dx, dy));
        return n;
    }

    void Circle2D::mirror(const Point2d &p) {
        if (!is_valid()) return;
        pimpl_->c.Mirror(core::occt_point_2d_access::get(p));
    }

    void Circle2D::mirror(const Axis2d &axis) {
        if (!is_valid()) return;
        pimpl_->c.Mirror(core::occt_axis_2d_access::get(axis));
    }

    void Circle2D::rotate(const Point2d &about, const real angle) {
        if (!is_valid()) return;
        pimpl_->c.Rotate(core::occt_point_2d_access::get(about), angle);
    }

    void Circle2D::scale(const Point2d &about, const real s) {
        if (!is_valid()) return;
        pimpl_->c.Scale(core::occt_point_2d_access::get(about), s);
    }

    void Circle2D::translate(const real dx, const real dy) {
        if (!is_valid()) return;
        pimpl_->c.Translate(gp_Vec2d(dx, dy));
    }

    bool Circle2D::s_valid(const std::shared_ptr<Impl> & p) noexcept {
        if (!p || !p->has) return false;
        const auto r = p->c.Radius();
        return std::isfinite(r) && r > 0;
    }
}
#else

#endif