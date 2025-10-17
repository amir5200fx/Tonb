//
// Created by amir on 30/09/2025.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/geometry/occt/core/axis2_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>
#include <tonb/geometry/occt/core/direction_2d_helpers.hxx>

namespace tonb::geometry::occt {
    // helper: build gp_Dir2d safely

    Axis22d::Axis22d(const Point2d &origin, const Direction2d &xdir, const Direction2d &ydir) : pimpl_(std::make_shared<Impl>()) {
        const auto p = core::occt_point_2d_access::get(origin);
        const auto du = core::occt_dir_2d_access::get(xdir);
        const auto dv = core::occt_dir_2d_access::get(ydir);
        pimpl_->ax = gp_Ax22d{p, du, dv};
        pimpl_->has = true;
    }

    Axis22d::Axis22d(const Point2d &origin, const Direction2d &xdir, const bool sense_direct) : pimpl_(std::make_shared<Impl>()) {
        const auto p = core::occt_point_2d_access::get(origin);
        const auto du = core::occt_dir_2d_access::get(xdir);
        pimpl_->ax = gp_Ax22d{p, du, sense_direct};
        pimpl_->has = true;
    }

    bool Axis22d::is_valid() const noexcept {
        return s_valid(pimpl_);
    }

    Point2d Axis22d::origin() const noexcept {
        if (!is_valid()) return {};
        return core::occt_point_2d_access::make((pimpl_->ax.Location()));
    }

    Axis2d Axis22d::x_direction() const noexcept {
        if (!is_valid()) return {};
        return core::occt_axis_2d_access::make(pimpl_->ax.XAxis());
    }

    Axis2d Axis22d::y_direction() const noexcept {
        if (!is_valid()) return {};
        return core::occt_axis_2d_access::make(pimpl_->ax.YAxis());
    }

    Axis22d Axis22d::with_origin(const Point2d &p) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.SetLocation(core::occt_point_2d_access::get(p));
        return n;
    }

    Axis22d Axis22d::with_x_direction(const Axis2d &x) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.SetXDirection(core::occt_dir_2d_access::get(x.direction()));
        return n;
    }

    Axis22d Axis22d::with_y_direction(const Axis2d &y) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.SetYDirection(core::occt_dir_2d_access::get(y.direction()));
        return n;
    }

    // -------------- transforms (immutable) ---------------
    Axis22d Axis22d::mirrored(const Point2d &p) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.Mirror(core::occt_point_2d_access::get(p));
        return n;
    }

    Axis22d Axis22d::mirrored(const Axis2d &x) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.Mirror(core::occt_axis_2d_access::get(x));
        return n;
    }

    Axis22d Axis22d::rotated(const Point2d &about, const real ang_rad) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.Rotate(core::occt_point_2d_access::get(about), ang_rad);
        return n;
    }

    Axis22d Axis22d::scaled(const Point2d &about, const real s) const {
        if (!is_valid()) return {};
        auto n = *this;
        pimpl_->ax.Scale(core::occt_point_2d_access::get(about), s);
        return n;
    }

    Axis22d Axis22d::translated(const real dx, const real dy) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->ax.Translate(gp_Vec2d(dx, dy));
        return n;
    }

    void Axis22d::mirror(const Point2d &p) {
        if (!is_valid()) return;
        pimpl_->ax.Mirror(core::occt_point_2d_access::get(p));
    }

    void Axis22d::mirror(const Axis2d &a) {
        if (!is_valid()) return;
        pimpl_->ax.Mirror(core::occt_axis_2d_access::get(a));
    }

    void Axis22d::rotate(const Point2d &about, real ang_rad) {
        if (!is_valid()) return;
        pimpl_->ax.Rotate(core::occt_point_2d_access::get(about), ang_rad);
    }

    void Axis22d::scale(const Point2d &about, real s) {
        if (!is_valid()) return;
        pimpl_->ax.Scale(core::occt_point_2d_access::get(about), s);
    }

    void Axis22d::translate(real dx, real dy) {
        if (!is_valid()) return;
        pimpl_->ax.Translate(gp_Vec2d(dx, dy));
    }

    bool Axis22d::s_valid(const std::shared_ptr<Impl>& p) noexcept {
        return p && p->has;
    }
}
#else
#endif