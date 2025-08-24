//
// Created by amir on 8/24/25.
//

#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/vector.hxx>
#include <tonb/geometry/occt/transform.hxx>
#include <tonb/geometry/occt/point.hxx>
#include <tonb/geometry/occt/core/vector_helpers.hxx>
#include <tonb/geometry/occt/core/point_helpers.hxx>
#include <tonb/geometry/occt/core/transform_helpers.hxx>

// OCCT
#include <opencascade/gp_Vec.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Trsf.hxx>

namespace tonb::geometry::occt {

    Vector::Vector() noexcept : pimpl_(std::make_shared<Impl>()) {pimpl_->v = gp_Vec(0, 0, 0);}
    Vector::Vector(const real u, const real v, const real w) noexcept : pimpl_(std::make_shared<Impl>()) { pimpl_->v = gp_Vec(u, v, w);}

    Vector Vector::from_points(const Point& a, const Point& b) noexcept {
        const auto pa = core::occt_point_access::get(a);
        const auto pb = core::occt_point_access::get(b);
        Vector out; out.pimpl_->v = gp_Vec(pa, pb); return out;
    }

    real Vector::u() const noexcept {return pimpl_->v.X();}
    real Vector::v() const noexcept {return pimpl_->v.Y();}
    real Vector::w() const noexcept {return pimpl_->v.Z();}

    Vector& Vector::set_u(const real v) noexcept {pimpl_->v.SetX(v); return *this;}
    Vector& Vector::set_v(const real v) noexcept {pimpl_->v.SetY(v); return *this;}
    Vector& Vector::set_w(const real v) noexcept {pimpl_->v.SetZ(v); return *this;}

    real Vector::squared_norm() const noexcept {
        return pimpl_->v.SquareMagnitude();
    }
    real Vector::norm() const noexcept {
        return pimpl_->v.Magnitude();
    }

    bool Vector::is_zero(const real eps) const noexcept {
        return norm() <= eps;
    }

    Vector Vector::normalized(const real eps) const noexcept {
        if (is_zero(eps)) return Vector{};
        Vector r = *this; r.pimpl_->v.Normalize(); return r;
    }
    Vector Vector::scaled(const real scale) const noexcept {
        Vector r = *this; r.pimpl_->v.Scale(scale); return r;
    }
    Vector Vector::negated() const noexcept {
        return scaled(-1.0);
    }
    Vector Vector::added(const Vector &v) const noexcept {
        Vector r = *this; r.pimpl_->v.Add(v.pimpl_->v); return r;
    }
    Vector Vector::subtracted(const Vector &v) const noexcept {
        Vector r = *this; r.pimpl_->v.Subtract(v.pimpl_->v); return r;
    }

    real Vector::dot(const Vector &v) const noexcept { return pimpl_->v.Dot(v.pimpl_->v); }
    Vector Vector::cross(const Vector &v) const noexcept { Vector r = *this; r.pimpl_->v.Cross(v.pimpl_->v); return r;}

    Vector Vector::transformed(const Transform &t) const noexcept {
        Vector r = *this; r.pimpl_->v.Transform(core::occt_trsf_access::get(t)); return r;
    }

}
#else
static_assert(true, "src/occt/vector.cxx compiled without TONB_WITH_OCCT");
#endif