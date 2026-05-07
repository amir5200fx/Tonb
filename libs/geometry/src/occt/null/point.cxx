//
// Created by amir on 8/24/25.
//
#include <tonb/geometry/occt/point.hxx>

#include <cmath>
#include <limits>

namespace tonb::geometry::occt {

    struct Point::Impl{ real x{0}, y{0}, z{0}; };

    Point::Point() noexcept : pimpl_(std::make_shared<Impl>()) {}
    Point::Point(const real x, const real y, const real z) noexcept : pimpl_(std::make_shared<Impl>()) { pimpl_->x=x; pimpl_->y=y; pimpl_->z=z; }

    real Point::x() const noexcept { return pimpl_->x; }
    real Point::y() const noexcept { return pimpl_->y; }
    real Point::z() const noexcept { return pimpl_->z; }

    Point& Point::set_x(const real v) noexcept { pimpl_->x=v; return *this; }
    Point& Point::set_y(const real v) noexcept { pimpl_->y=v; return *this; }
    Point& Point::set_z(const real v) noexcept { pimpl_->z=v; return *this; }

    std::array<real, 3> Point::xyz() const noexcept {
        return {x(), y(), z()};
    }

    Point Point::moved(const std::array<real, 3>& d) const noexcept {
        return Point(x() + d[0], y() + d[1], z() + d[2]);
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
        const auto a = xyz();
        return std::isfinite(a[0]) && std::isfinite(a[1]) && std::isfinite(a[2]);
    }

    bool Point::almost_equal(const Point& p, const real tol) const noexcept {
        return distance_sq(p) < tol*tol;
    }
}