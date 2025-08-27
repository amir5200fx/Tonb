//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/curve_2d.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/curve_2d_helpers.hxx>

// OCCT
#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/Geom2d_BoundedCurve.hxx>
#include <opencascade/Geom2d_TrimmedCurve.hxx>
#include <opencascade/Geom2dAdaptor_Curve.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Vec2d.hxx>

#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>

namespace tonb::geometry::occt {

    bool Curve2d::is_valid() const noexcept {
        return pimpl_ && !pimpl_->h.IsNull();
    }
    bool Curve2d::is_closed() const noexcept {
        return is_valid() && pimpl_->h->IsClosed();
    }
    bool Curve2d::is_periodic() const noexcept {
        return is_valid() && pimpl_->h->IsPeriodic();
    }

    int Curve2d::degree() const noexcept {
        if (!is_valid()) return -1;
        const Geom2dAdaptor_Curve gac(pimpl_->h);
        // Note: Degree() is meaningful for polynomial/spline curves; for others is returns a small value
        return gac.Degree();
    }

    std::optional<std::pair<real, real>> Curve2d::parameter_range() const noexcept {
        if (!is_valid()) return std::nullopt;
        const auto bc = Handle(Geom2d_BoundedCurve)::DownCast(pimpl_->h);
        if (bc.IsNull()) return std::nullopt;
        return std::make_pair(static_cast<real>(bc->FirstParameter()), static_cast<real>(bc->LastParameter()));
    }
    real Curve2d::first_parameter() const noexcept {
        if (!is_valid()) return -std::numeric_limits<real>::infinity();
        return pimpl_->h->FirstParameter();
    }
    real Curve2d::last_parameter() const noexcept {
        if (!is_valid()) return std::numeric_limits<real>::infinity();
        return pimpl_->h->LastParameter();
    }

    std::array<real, 2> Curve2d::value(const real u) const {
        gp_Pnt2d p;
        if (is_valid()) {pimpl_->h->D0(u, p);}
        return core::from_gp_to_array(p);
    }
    Curve2d::D1 Curve2d::d1(const real u) const {
        gp_Pnt2d p; gp_Vec2d v;
        if (is_valid()) {pimpl_->h->D1(u, p, v);}
        return {core::from_gp_to_array(p), core::from_gp_to_array(v)};
    }
    Curve2d Curve2d::trimmed(const real u0, const real u1) const {
        if (!is_valid()) return {};
        Handle(Geom2d_TrimmedCurve) t = new Geom2d_TrimmedCurve(pimpl_->h, u0, u1, true);
        if (t.IsNull()) return {};
        return Curve2d{std::make_shared<Impl>(Impl{std::move(t)})};
    }

    Curve2d Curve2d::mirrored(const Axis2d& a) const {
        if (!is_valid()) return {};
        auto mirrored = Handle(Geom2d_Curve)::DownCast(pimpl_->h->Mirrored(core::occt_axis_2d_access::get(a)));
        if (mirrored.IsNull()) return {};
        return Curve2d{std::make_shared<Impl>(std::move(mirrored))};
    }
    Curve2d Curve2d::mirrored(const Point2d& a) const {
        if (!is_valid()) return {};
        auto mirrored = Handle(Geom2d_Curve)::DownCast(pimpl_->h->Mirrored(core::occt_point_2d_access::get(a)));
        if (mirrored.IsNull()) return {};
        return Curve2d{std::make_shared<Impl>(std::move(mirrored))};
    }
}
#else
static_assert(true, "src/occt/curve_2d.cxx compiled without TONB_WITH_OCCT");
#endif