//
// Created by amir on 8/27/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/vector_2d.hxx>
#include <tonb/geometry/occt/transform_2d.hxx>
#include <tonb/geometry/occt/core/vector_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/core/transform_2d_helpers.hxx>

// OCCT
#include <opencascade/gp_Vec2d.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Trsf2d.hxx>

namespace tonb::geometry::occt {

    Vector2d::Vector2d() noexcept : pimpl_(std::make_shared<Impl>()) {pimpl_->v = gp_Vec2d(0, 0);}
    Vector2d::Vector2d(const real u, const real v) noexcept : pimpl_(std::make_shared<Impl>()) { pimpl_->v = gp_Vec2d(u, v);}

    Vector2d Vector2d::from_points(const Point2d& a, const Point2d& b) noexcept {
        const auto pa = core::occt_point_2d_access::get(a);
        const auto pb = core::occt_point_2d_access::get(b);
        Vector2d out; out.pimpl_->v = gp_Vec2d(pa, pb); return out;
    }

    real Vector2d::u() const noexcept {return pimpl_->v.X();}
    real Vector2d::v() const noexcept {return pimpl_->v.Y();}

    Vector2d& Vector2d::set_u(const real v) noexcept {pimpl_->v.SetX(v); return *this;}
    Vector2d& Vector2d::set_v(const real v) noexcept {pimpl_->v.SetY(v); return *this;}

    real Vector2d::squared_norm() const noexcept {
        return pimpl_->v.SquareMagnitude();
    }
    real Vector2d::norm() const noexcept {
        return pimpl_->v.Magnitude();
    }

    bool Vector2d::is_zero(const real eps) const noexcept {
        return norm() <= eps;
    }

    Vector2d Vector2d::normalized(const real eps) const noexcept {
        if (is_zero(eps)) return Vector2d{};
        Vector2d r = *this; r.pimpl_->v.Normalize(); return r;
    }
    Vector2d Vector2d::scaled(const real scale) const noexcept {
        Vector2d r = *this; r.pimpl_->v.Scale(scale); return r;
    }
    Vector2d Vector2d::negated() const noexcept {
        return scaled(-1.0);
    }
    Vector2d Vector2d::added(const Vector2d &other) const noexcept {
        Vector2d r = *this; r.pimpl_->v.Add(other.pimpl_->v); return r;
    }
    Vector2d Vector2d::subtracted(const Vector2d &other) const noexcept {
        Vector2d r = *this; r.pimpl_->v.Subtract(other.pimpl_->v); return r;
    }

    real Vector2d::dot(const Vector2d &v) const noexcept { return pimpl_->v.Dot(v.pimpl_->v); }
    real Vector2d::cross(const Vector2d &v) const noexcept { return pimpl_->v.CrossMagnitude(v.pimpl_->v);}

    Vector2d Vector2d::transformed(const Transform2d &t) const noexcept {
        Vector2d r = *this; r.pimpl_->v.Transform(core::occt_trsf_2d_access::get(t)); return r;
    }

}
#else
static_assert(true, "src/occt/vector.cxx compiled without TONB_WITH_OCCT");
#endif