//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/point.hxx>
#include <tonb/geometry/occt/core/point_helpers.hxx>

// OCCT
#include <opencascade/gp_Pnt.hxx>

#include <cmath>

namespace tonb::geometry::occt {

    Point::Point() noexcept : pimpl_(std::make_unique<Impl>()) {pimpl_->p = gp_Pnt(0, 0, 0);}
    Point::Point(const real x, const real y, const real z) noexcept : pimpl_(std::make_unique<Impl>()) {pimpl_->p = gp_Pnt(x, y, z);}

    real Point::x() const noexcept {return pimpl_->p.X();}
    real Point::y() const noexcept {return pimpl_->p.Y();}
    real Point::z() const noexcept {return pimpl_->p.Z();}

    Point& Point::set_x(const real v) noexcept {pimpl_->p.SetX(v); return *this;}
    Point& Point::set_y(const real v) noexcept {pimpl_->p.SetY(v); return *this;}
    Point& Point::set_z(const real v) noexcept {pimpl_->p.SetZ(v); return *this;}

    Point Point::moved(const std::array<real, 3>& d) const noexcept {
        return Point{x() + d[0], y() + d[1], z() + d[2]};
    }

    real Point::distance(const Point& p) const noexcept {
        return std::sqrt(distance_sq(p));
    }

    real Point::distance_sq(const Point& p) const noexcept {
        const real dx = x() - p.x();
        const real dy = y() - p.y();
        const real dz = z() - p.z();
        return dx*dx + dy*dy + dz*dz;
    }

    bool Point::is_finite() const noexcept {
        const auto a= xyz();
        return std::isfinite(a[0]) && std::isfinite(a[1]) && std::isfinite(a[2]);
    }

    bool Point::almost_equal(const Point& p, const real tol) const noexcept {
        return distance_sq(p) <= tol*tol;
    }

}

#else
static_assert(true, "src/occt/point.cxx compiled without TONB_WITH_OCCT");
#endif