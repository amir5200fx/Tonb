//
// Created by amir on 8/24/25.
//
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/occt/curve.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>
#include <tonb/geometry/occt/core/curve_helpers.hxx>
#include <tonb/geometry/occt/core/point_helpers.hxx>

// OCCT
#include <opencascade/GeomAPI_ProjectPointOnCurve.hxx>
#include <opencascade/GCPnts_AbscissaPoint.hxx>
#include <opencascade/Geom_Curve.hxx>
#include <opencascade/Geom_BoundedCurve.hxx>
#include <opencascade/Geom_TrimmedCurve.hxx>
#include <opencascade/Geom_BSplineCurve.hxx>
#include <opencascade/GeomAdaptor_Curve.hxx>
#include <opencascade/GeomConvert.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>
#include <opencascade/Standard_Failure.hxx>

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

    bool Curve::is_bspline() const noexcept {
        return is_valid() && Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
    }
    int Curve::nb_poles() const noexcept {
        if (!is_valid()) return 0;
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        return bspline ? bspline->NbPoles() : 0;
    }
    std::vector<Point> Curve::poles() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        std::vector<Point> poles; poles.reserve(bspline->NbPoles());
        for (const auto& p: bspline->Poles()) {
            poles.emplace_back(p.X(), p.Y(), p.Z());
        }
        return poles;
    }

    Point Curve::pole(const int index) const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        return core::occt_point_access::make(bspline->Pole(index));
    }

    bool Curve::is_nurbs() const noexcept {
        if (!is_valid()) return false;
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return false;
        return static_cast<bool>(bspline->Weights());
    }

    std::vector<real> Curve::weights() const noexcept {
        if (!is_valid()) return {};
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return {};
        if (!bspline->Weights()) return {};
        std::vector<real> weights; weights.reserve(bspline->NbPoles());
        for (const auto w: *bspline->Weights()) weights.emplace_back(w);
        return weights;
    }

    real Curve::weight(const int index) const {
        if (!is_valid()) return -1;
        const auto bspline = Handle(Geom_BSplineCurve)::DownCast(pimpl_->h);
        if (!bspline) return -1;
        if (!bspline->Weights()) return -1;
        try {
            return bspline->Weight(index);
        } catch (const Standard_Failure& err) {
            throw std::invalid_argument("Curve::weight: bad index");
        }
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

    Curve Curve::reversed() const {
        if (!is_valid()) return {};
        auto r = pimpl_->h->Reversed();
        if (r.IsNull()) return {};
        return Curve{std::make_shared<Impl>(Impl{std::move(r)})};
    }

    Curve Curve::bspline() const {
        if (!is_valid()) return {};
        Handle(Geom_BSplineCurve) converted = GeomConvert::CurveToBSplineCurve(pimpl_->h);
        if (converted.IsNull()) return {};
        return Curve{std::make_shared<Impl>(Impl{std::move(converted)})};
    }

    void Curve::reverse() const {
        if (!is_valid()) return;
        pimpl_->h->Reverse();
    }

    Curve::MinDistanceProjected Curve::project(const Point & pt) const {
        if (!is_valid()) {
            throw std::runtime_error("Curve::project(): Curve is not valid");
        }
        GeomAPI_ProjectPointOnCurve projector;
        projector.Init(occt::core::occt_point_access::get(pt), pimpl_->h);
        if (projector.NbPoints() > 0) {
            return {
                core::occt_point_access::make(projector.NearestPoint()),
                static_cast<real>(projector.LowerDistanceParameter())
            };
        }
        throw std::runtime_error("Projection failed!");
    }

    std::expected<std::optional<Curve::ProjectionResult>, Curve::ProjectionError> Curve::try_project_point(
        const std::array<double, 3> & pt) const noexcept {
        if (!is_valid()) {
            return std::unexpected(ProjectionError{ProjectionErrc::null_curve, "Null curve handle"});
        }
        try {
            GeomAPI_ProjectPointOnCurve projector;
            projector.Init({pt[0], pt[1], pt[2]}, pimpl_->h);

            if (projector.NbPoints() == 0) {
                return std::optional<ProjectionResult>{};
            }
            const auto ppt = projector.NearestPoint();
            ProjectionResult r{
                {ppt.X(), ppt.Y(), ppt.Z()},
                projector.LowerDistanceParameter(),
                projector.LowerDistance()
            };
            return std::optional<Curve::ProjectionResult>{r};
        } catch (Standard_Failure& e) {
            const char* msg = e.GetMessageString();
            return std::unexpected(ProjectionError{ProjectionErrc::null_curve, msg ? msg: "OCCT Standard_Failure"});
        }
    }

    double Curve::calc_length() const {
        if (!is_valid()) return 0;
        const auto& c = pimpl_->h;
        // Ensure the curve has a finite range.
        const Standard_Real u1 = c->FirstParameter();
        const Standard_Real u2 = c->LastParameter();

        if (!Precision::IsInfinite(u1) && !Precision::IsInfinite(u2)) {
            const GeomAdaptor_Curve ac(c, u1, u2);
            return GCPnts_AbscissaPoint::Length(ac, u1, u2);
        }
        return std::numeric_limits<double>::infinity();
    }


    // ---- interop friend access


}

#endif