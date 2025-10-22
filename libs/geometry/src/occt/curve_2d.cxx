//
// Created by amir on 8/26/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/curve_2d.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/curve_2d_helpers.hxx>
#include <tonb/geometry/occt/core/point_2d_helpers.hxx>
#include <tonb/geometry/occt/axis_2d.hxx>
#include <tonb/geometry/occt/core/axis_2d_helpers.hxx>

// OCCT
#include <opencascade/GeomConvert.hxx>
#include <opencascade/GCPnts_AbscissaPoint.hxx>
#include <opencascade/Geom2dAPI_ProjectPointOnCurve.hxx>
#include <opencascade/Geom2d_Curve.hxx>
#include <opencascade/Geom2d_BoundedCurve.hxx>
#include <opencascade/Geom2d_TrimmedCurve.hxx>
#include <opencascade/Geom2d_BSplineCurve.hxx>
#include <opencascade/Geom2dAdaptor_Curve.hxx>
#include <opencascade/Geom2dConvert.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Vec2d.hxx>

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
    bool Curve2d::is_bspline() const noexcept {
        return is_valid() && Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
    }
    int Curve2d::nb_poles() const noexcept {
        if (!is_valid()) return 0;
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        return bspline ? bspline->NbPoles() : 0;
    }

    std::vector<Point2d> Curve2d::poles() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        std::vector<Point2d> poles; poles.reserve(bspline->NbPoles());
        for (const auto& p: bspline->Poles()) {
            poles.emplace_back(p.X(), p.Y());
        }
        return poles;
    }

    Point2d Curve2d::pole(const int index) const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        return core::occt_point_2d_access::make(bspline->Pole(index));
    }

    bool Curve2d::is_nurbs() const noexcept {
        if (!is_valid()) return false;
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return false;
        return static_cast<bool>(bspline->Weights());
    }
    std::vector<real> Curve2d::weights() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        if (!bspline->Weights()) return {};
        std::vector<real> weights; weights.reserve(bspline->NbPoles());
        for (const auto w: *bspline->Weights()) weights.emplace_back(w);
        return weights;
    }
    real Curve2d::weight(const int index) const {
        if (!is_valid()) return -1;
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return -1;
        if (!bspline->Weights()) return -1;
        try {
            return bspline->Weight(index);
        } catch (const Standard_Failure& err) {
            throw std::invalid_argument("Curve::weight: bad index");
        }
    }

    std::vector<real> Curve2d::knots() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        std::vector<real> knots; knots.reserve(bspline->Knots().Size());
        for (const auto k: bspline->Knots()) knots.emplace_back(k);
        return knots;
    }

    std::vector<int> Curve2d::multiplicities() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom2d_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        std::vector<int> r; r.reserve(bspline->Multiplicities().Size());
        for (const auto m: bspline->Multiplicities()) r.emplace_back(m);
        return r;
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
    Curve2d Curve2d::bspline() const {
        if (!is_valid()) return {};
        Handle(Geom2d_BSplineCurve) r = Geom2dConvert::CurveToBSplineCurve(pimpl_->h);
        if (r.IsNull()) return {};
        return Curve2d{std::make_shared<Impl>(Impl{std::move(r)})};
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

    Curve2d Curve2d::reversed() const {
        if (!is_valid()) return {};
        auto r = pimpl_->h->Reversed();
        if (r.IsNull()) return {};
        return Curve2d{std::make_shared<Impl>(std::move(r))};
    }
    void Curve2d::reverse() const {
        if (!is_valid()) return;
        pimpl_->h->Reverse();
    }

    Curve2d::MinDistanceProjected Curve2d::project(const Point2d& pt) const {
        if (!is_valid()) throw std::runtime_error("Curve2d::project(): curve is not valid!");
        Geom2dAPI_ProjectPointOnCurve projector;
        projector.Init(occt::core::occt_point_2d_access::get(pt), pimpl_->h);
        if (projector.NbPoints() > 0) {
            return {
                core::occt_point_2d_access::make(projector.NearestPoint()),
                static_cast<real>(projector.LowerDistanceParameter())
            };
        }
        throw std::runtime_error("Projection failed!");
    }

    double Curve2d::calc_length() const {
        if (!is_valid()) return 0;
        const auto& c = pimpl_->h;
        // Ensure the curve has a finite range.
        const Standard_Real u1 = c->FirstParameter();
        const Standard_Real u2 = c->LastParameter();

        if (!Precision::IsInfinite(u1) && !Precision::IsInfinite(u2)) {
            const Geom2dAdaptor_Curve ac(c, u1, u2);
            return GCPnts_AbscissaPoint::Length(ac, u1, u2);
        }
        return std::numeric_limits<double>::infinity();
    }
}
#else
static_assert(true, "src/occt/curve_2d.cxx compiled without TONB_WITH_OCCT");
#endif