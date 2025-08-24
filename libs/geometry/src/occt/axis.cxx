//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/axis.hxx>
#include <tonb/geometry/occt/transform.hxx>
#include <tonb/geometry/occt/core/axis_helpers.hxx>
#include <tonb/geometry/occt/core/point_helpers.hxx>
#include <tonb/geometry/occt/core/vector_helpers.hxx>
#include <tonb/geometry/occt/core/transform_helpers.hxx>
#include <tonb/geometry/occt/vector.hxx>

// OCCT
#include <opencascade/gp_Ax1.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Dir.hxx>

namespace tonb::geometry::occt {

    static inline bool near_zero3(const real x, const real y, const real z, const real eps = 1.e-15) {
        return (x*x + y*y + z*z) <= eps *eps;
    }

    Axis::Axis() noexcept : pimpl_(std::make_shared<Impl>()) {
        pimpl_->ax=gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(0, 0, 1));
        pimpl_->valid = true;
    }

    Axis Axis::from_point_dir(const Point &origin, const Vector &dir) noexcept {
        auto impl = std::make_shared<Axis::Impl>();
        if (near_zero3(dir.u(), dir.v(), dir.w())) {
            impl->ax=gp_Ax1(gp_Pnt(0, 0, 1), gp_Dir(0, 0, 1));
            impl->valid=false;
        } else {
            impl->ax = gp_Ax1(core::occt_point_access::get(origin), core::occt_vector_access::get(dir));
            impl->valid=true;
        }
        return Axis(std::move(impl));
    }

    bool Axis::is_valid() const noexcept {
        return pimpl_ && pimpl_->valid;
    }

    Point Axis::origin() const noexcept {
        if (!pimpl_) return {0, 0, 0};
        const gp_Pnt p = pimpl_->ax.Location();
        return core::occt_point_access::make(p);
    }

    Vector Axis::direction() const noexcept {
        if (!is_valid()) return {0, 0, 0};
        const gp_Dir d = pimpl_->ax.Direction();
        return core::occt_vector_access::make(d);
    }

    Axis Axis::with_origin(const Point &origin) const noexcept {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis::Impl>(*pimpl_);
        impl->ax.SetLocation(core::occt_point_access::get(origin));
        return Axis(std::move(impl));
    }

    Axis Axis::with_direction(const Vector &dir) const noexcept {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis::Impl>(*pimpl_);
        if (near_zero3(dir.u(), dir.v(), dir.w())) {
            impl->valid = false;
        } else {
            impl->ax.SetDirection(core::occt_vector_access::get(dir));
            impl->valid=true;
        }
        return Axis(std::move(impl));
    }

    Axis Axis::moved(const Vector &delta) const {
        if (!pimpl_) return *this;
        const auto o = origin();
        return with_origin({o.x() + delta.u(), o.y() + delta.v(), o.z() + delta.w()});
    }

    Axis Axis::reversed() const {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis::Impl>(*pimpl_);
        impl->ax.Reverse();
        // validity unchanged
        return Axis(std::move(impl));
    }

    Axis Axis::transformed(const Transform &t) const {
        if (!pimpl_) return *this;
        auto impl = std::make_shared<Axis::Impl>(*pimpl_);
        impl->ax.Transform(core::occt_trsf_access::get(t));
        // validity unchanged
        return Axis(std::move(impl));
    }
}

#else
static_assert(true, "src/occt/axis.cxx compiled without TONB_WITH_OCCT");
#endif