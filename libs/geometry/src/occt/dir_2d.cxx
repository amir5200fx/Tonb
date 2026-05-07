//
// Created by amir on 30/09/2025.
//
#include <tonb/geometry/occt/core/direction_2d_helpers.hxx>
#include <tonb/config.hxx>

#include "tonb/geometry/occt/core/axis_2d_helpers.hxx"

#if defined(TONB_HAS_OCCT_ADAPTERS)

namespace tonb::geometry::occt {
    // helpers
    static inline gp_Dir2d make_dir2d(const real u, const real v) {return gp_Dir2d{u, v};}
    Direction2d::Direction2d(const real u, const real v) : pimpl_(std::make_shared<Impl>()) {
        pimpl_->d = make_dir2d(u, v); // normalises; raises if zero
        pimpl_->has = true;
    }

    Direction2d::Direction2d(const std::array<real, 2> &cmpts) : Direction2d(cmpts[0], cmpts[1]) {
    }

    bool Direction2d::is_valid() const noexcept {
        return s_valid(pimpl_);
    }

    std::array<real, 2> Direction2d::components() const noexcept {
        if (!is_valid()) return {0,0};
        return {static_cast<real>(pimpl_->d.X()), static_cast<real>(pimpl_->d.Y())};
    }

    real Direction2d::u() const noexcept {
        return is_valid() ? static_cast<real>(pimpl_->d.X()) : 0;
    }
    real Direction2d::v() const noexcept {
        return is_valid() ? static_cast<real>(pimpl_->d.Y()) : 0;
    }

    real Direction2d::angle(const Direction2d &other) const {
        if (!is_valid() || !other.is_valid()) return 0;
        return static_cast<real>(pimpl_->d.Angle(other.pimpl_->d));
    }

    bool Direction2d::is_equal(const Direction2d &other, real angular_tol) const {
        if (!is_valid() || !other.is_valid()) return false;
        return pimpl_->d.IsEqual(other.pimpl_->d, angular_tol);
    }

    Direction2d Direction2d::mirrored(const Axis2d &ax) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->d.Mirror(core::occt_axis_2d_access::get(ax));
        return n;
    }

    Direction2d Direction2d::rotated(real ang_rad) const {
        if (!is_valid()) return {};
        auto n = *this;
        n.pimpl_->d.Rotate(ang_rad);
        return n;
    }

    void Direction2d::mirror(const Axis2d &ax) {
        if (!is_valid()) return;
        pimpl_->d.Mirror(core::occt_axis_2d_access::get(ax));
    }

    void Direction2d::rotate(real ang_rad) {
        if (!is_valid()) return;
        pimpl_->d.Rotate(ang_rad);
    }

    void Direction2d::reverse() {
        if (!is_valid()) return;
        pimpl_->d.Reverse();
    }

    bool Direction2d::s_valid(const std::shared_ptr<Impl> & p) noexcept {
        return p && p->has;
    }
}
#else

#endif