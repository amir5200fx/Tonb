//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)
#include <tonb/geometry/occt/point_2d.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>

namespace tonb::geometry::occt {
    Point2d::Point2d() noexcept : pimpl_(std::make_shared<Impl>()) {pimpl_->p = gp_Pnt2d(0, 0);}
    Point2d::Point2d(const real x, const real y) noexcept : pimpl_(std::make_shared<Impl>()) {pimpl_->p = gp_Pnt2d(x, y);}

    real Point2d::x() const noexcept { return pimpl_->p.X();}
    real Point2d::y() const noexcept { return pimpl_->p.Y();}

    Point2d& Point2d::set_x(const real x) noexcept {pimpl_->p.SetX(x); return *this;}
    Point2d& Point2d::set_y(const real v) noexcept {pimpl_->p.SetY(v); return *this;}

    std::array<real, 2> Point2d::xy() const noexcept {
        return  {pimpl_->p.X(), pimpl_->p.Y()};
    }

    Point2d Point2d::moved(const std::array<real, 2>& v) const noexcept {
        return {pimpl_->p.X() + v[0], pimpl_->p.Y() + v[1]};
    }

    real Point2d::distance(const Point2d& p) const noexcept {
        return std::sqrt(distance_sq(p));
    }
    real Point2d::distance_sq(const Point2d& p) const noexcept {
        return pimpl_->p.SquareDistance(p.pimpl_->p);
    }

    bool Point2d::is_finite() const noexcept {
        const auto a=xy();
        return std::isfinite(a[0]) && std::isfinite(a[1]);
    }
    bool Point2d::almost_equal(const Point2d& p, const real tol) const noexcept {
        return distance_sq(p) <= tol * tol;
    }
}

#else
static_assert(true, "src/occt/point_2d.cxx compiled without TONB_WITH_OCCT");
#endif

