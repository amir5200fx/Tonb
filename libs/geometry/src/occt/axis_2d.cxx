//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/transform_2d.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/vector_2d_helpers.hxx>
#include <tonb/geometry/occt/core/direction_2d_helpers.hxx>
#include <tonb/geometry/occt/core/transform_2d_helpers.hxx>
#include <tonb/geometry/occt/vector_2d.hxx>

// OCCT
#include <opencascade/gp_Ax2d.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Dir2d.hxx>

namespace tonb::geometry::occt {
    inline bool near_zero2(const real x, const real y, const real eps = 1.e-15) {
        return (x*x + y*y) <= eps;
    }

    Axis2d::Axis2d() noexcept : pimpl_(std::make_unique<Impl>()) {
        pimpl_->ax = gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(1, 0));
        pimpl_->valid = true;
    }

    Axis2d Axis2d::from_point_dir(const Point2d& origin, const Vector2d& dir) noexcept {
        auto impl = std::make_shared<Axis2d::Impl>();
        if (near_zero2(dir.u(), dir.v())) {
            impl->ax=gp_Ax2d(gp_Pnt2d(0, 0), gp_Dir2d(1, 0));
            impl->valid=false;
        } else {
            impl->ax = gp_Ax2d(core::occt_point_2d_access::get(origin), core::occt_vector_2d_access::get(dir));
            impl->valid=true;
        }
        return Axis2d(std::move(impl));
    }

    bool Axis2d::is_valid() const noexcept {
        return pimpl_ && pimpl_->valid;
    }

    Point2d Axis2d::origin() const noexcept {
        if (!pimpl_) return {0, 0};
        const gp_Pnt2d p = pimpl_->ax.Location();
        return core::occt_point_2d_access::make(p);
    }

    Direction2d Axis2d::direction() const noexcept {
        if (!is_valid()) return {0, 0};
        const gp_Dir2d d = pimpl_->ax.Direction();
        return core::occt_dir_2d_access::make(d);
    }

    Axis2d Axis2d::with_origin(const Point2d &origin) const noexcept {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis2d::Impl>(*pimpl_);
        impl->ax.SetLocation(core::occt_point_2d_access::get(origin));
        return Axis2d(std::move(impl));
    }

    Axis2d Axis2d::with_direction(const Direction2d &dir) const noexcept {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis2d::Impl>(*pimpl_);
        if (near_zero2(dir.u(), dir.v())) {
            impl->valid = false;
        } else {
            impl->ax.SetDirection(core::occt_dir_2d_access::get(dir));
            impl->valid=true;
        }
        return Axis2d(std::move(impl));
    }

    Axis2d Axis2d::moved(const Vector2d &delta) const {
        if (!pimpl_) return *this;
        const auto o = origin();
        return with_origin({o.x() + delta.u(), o.y() + delta.v()});
    }

    Axis2d Axis2d::reversed() const {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis2d::Impl>(*pimpl_);
        impl->ax.Reverse();
        // validity unchanged
        return Axis2d(std::move(impl));
    }

    Axis2d Axis2d::transformed(const Transform2d &t) const {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis2d::Impl>(*pimpl_);
        impl->ax.Transform(core::occt_trsf_2d_access::get(t));
        // validity unchanged
        return Axis2d(std::move(impl));
    }

}
#else
static_assert(true, "src/occt/axis_2d.cxx compiled without TONB_WITH_OCCT");
#endif