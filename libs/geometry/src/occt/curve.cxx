//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/curve.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/curve_helpers.hxx>

// OCCT
#include <opencascade/Geom_Curve.hxx>
#include <opencascade/Geom_BoundedCurve.hxx>
#include <opencascade/Geom_TrimmedCurve.hxx>
#include <opencascade/GeomAdaptor_Curve.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>

namespace tonb::geometry::occt {

    bool Curve::is_valid() const noexcept {
        return pimpl_ && !pimpl_->h.IsNull();
    }

    bool Curve::is_closed() const noexcept {
        return is_valid() && pimpl_->h->IsClosed();
    }

    bool Curve::is_periodic() const noexcept {
        return is_valid() && pimpl_->h->IsPeriodic();
    }

    int Curve::degree() const noexcept {
        if (!is_valid()) return -1;
        const GeomAdaptor_Curve gac(pimpl_->h);
        // Note: Degree() is meaningful for polynomial/spline curves; for others is returns a small value.
        return gac.Degree();
    }

    std::optional<std::pair<real, real> > Curve::parameter_range() const noexcept {
        if (!is_valid()) return std::nullopt;
        const auto bc = Handle(Geom_BoundedCurve)::DownCast(pimpl_->h);
        if (bc.IsNull()) return std::nullopt;
        return std::make_pair(static_cast<real>(bc->FirstParameter()), static_cast<real>(bc->LastParameter()));
    }

    std::array<real, 3> Curve::value(const double u) const {
        gp_Pnt p;
        if (is_valid()) {pimpl_->h->D0(u, p);}
        return core::from_gp_to_array(p);
    }

    Curve::D1 Curve::d1(const double u) const {
        gp_Pnt p; gp_Vec v;
        if (is_valid()) {pimpl_->h->D1(u, p, v);}
        return {core::from_gp_to_array(p), core::from_gp_to_array(v)};
    }

    Curve Curve::trimmed(const double u0, const double u1) const {
        if (!is_valid()) return {};
        Handle(Geom_TrimmedCurve) t = new Geom_TrimmedCurve(pimpl_->h, u0, u1, true);
        if (t.IsNull()) return {};
        return Curve{std::make_shared<Impl>(Impl{std::move(t)})};
    }

    // ---- interop friend access


}

#endif