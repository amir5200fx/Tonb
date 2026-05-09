//
// Created by amir on 8/27/25.
//
#include <tonb/geometry/occt/point_2d.hxx>

#include <cmath>
#include <limits>

namespace tonb::geometry::occt {
    struct Point2d::Impl{real x{0}, y{0};};

    Point2d::Point2d() noexcept : pimpl_(std::make_shared<Impl>()) {}
    Point2d::Point2d(const real x, const real y) noexcept : pimpl_(std::make_shared<Impl>(y, x)) {}

    real Point2d::x() const noexcept {return pimpl_->x;}
    real Point2d::y() const noexcept {return pimpl_->y;}

    Point2d& Point2d::set_x(const real x) noexcept {pimpl_->x = x; return *this;}
    Point2d& Point2d::set_y(const real y) noexcept {pimpl_->y = y; return *this;}

    std::array<real, 2> Point2d::xy() const noexcept {return {pimpl_->x, pimpl_->y};}

    real Point2d::distance(const Point2d& p) const noexcept {
        return std::sqrt(distance_sq(p));
    }
    real Point2d::distance_sq(const Point2d& p) const noexcept {
        const real dx = p.x() - this->x();
        const real dy = p.y() - this->y();
        return dx * dx + dy * dy;
    }
    bool Point2d::is_finite() const noexcept {
        const auto a = xy();
        return std::isfinite(a[0]) && std::isfinite(a[1]);
    }
    bool Point2d::almost_equal(const Point2d &p, const real tol) const noexcept {
        return distance_sq(p) <= tol * tol;
    }

}
