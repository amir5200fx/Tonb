//
// Created by amir on 8/24/25.
//

#include <tonb/cad/occt/edge.hxx>
#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/cad/occt/edge.hxx>
#include <tonb/geometry/occt/bbox.hxx>
#include <tonb/geometry/occt/curve.hxx>
#include <tonb/cad/occt/core/edge_helpers.hxx>
#include <tonb/geometry/occt/core/bbox_helpers.hxx>
#include <tonb/geometry/occt/core/curve_helpers.hxx>
#include <tonb/geometry/occt/core/adapters.hxx>

// OCCT
#include <opencascade/TopoDS_Edge.hxx>
#include <opencascade/TopExp.hxx>
#include <opencascade/TopoDS_Vertex.hxx>
#include <opencascade/BRepBndLib.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/Bnd_Box.hxx>
#include <opencascade/Geom_Curve.hxx>
#include <opencascade/Geom_BoundedCurve.hxx>
#include <opencascade/GeomAdaptor_Curve.hxx>
#include <opencascade/GCPnts_AbscissaPoint.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>

#include "tonb/geometry/occt/bbox.hxx"

namespace tonb::cad::occt {

    using namespace geometry::occt;

    bool Edge::is_valid() const noexcept {
        return pimple_ && !pimple_->edge.IsNull();
    }

    BBox Edge::bbox() const {
        if (is_valid()) {
            return {};
        }

        Bnd_Box box;
        BRepBndLib::Add(pimple_->edge, box, false);
        box.SetGap(0.0);

        return geometry::occt::core::to_bbox(box);
    }

    real Edge::length(const real tol) const {
        if (is_valid()) return 0.0;

        Standard_Real u0 = 0, u1 = 0;
        Handle(Geom_Curve) c = BRep_Tool::Curve(pimple_->edge, u0, u1);
        if (c.IsNull()) return 0.0;

        const GeomAdaptor_Curve gac(c, u0, u1);
        // length with tolerance; fails back to analytic if possible.
        return GCPnts_AbscissaPoint::Length(gac, u0, u1, tol);
    }

    std::optional<std::pair<real, real>> Edge::parameter_range() const {
        if (!is_valid()) return std::nullopt;
        Standard_Real u0 = 0, u1 = 0;
        const Handle(Geom_Curve) c = BRep_Tool::Curve(pimple_->edge, u0, u1);
        if (c.IsNull()) return std::nullopt;

        if (const Handle(Geom_BoundedCurve) bc = Handle(Geom_BoundedCurve)::DownCast(c); bc.IsNull()) return std::nullopt;

        return std::make_pair(static_cast<real>(u0), static_cast<real>(u1));
    }

    Edge::Point3 Edge::value(real u) const {
        gp_Pnt p(0,0,0);
        if (is_valid()) {
            Standard_Real u0 = 0, u1 = 0;
            if (const Handle(Geom_Curve) c = BRep_Tool::Curve(pimple_->edge, u0, u1); !c.IsNull()) {
                c->D0(u, p);
            }
        }
        return geometry::occt::core::from_gp_to_array(p);
    }

    std::array<real, 3> Edge::tangent(real u) const {
        gp_Pnt p(0,0,0);
        gp_Vec v(0,0,0);
        if (is_valid()) {
            Standard_Real u0 = 0, u1 = 0;
            Handle(Geom_Curve) c = BRep_Tool::Curve(pimple_->edge, u0, u1);
            if (!c.IsNull()) {
                c->D1(u, p, v);
            }
        }
        if (v.Magnitude() > 0.0) {v.Normalize();}
        return geometry::occt::core::from_gp_to_array(v);
    }

    std::pair<Edge::Point3, Edge::Point3> Edge::endpoints() const {
        Point3 a{0,0,0}, b{0,0,0};
        if (!is_valid()) {
            return {a, b};
        }

        TopoDS_Vertex v1, v2;
        TopExp::Vertices(pimple_->edge, v1, v2);
        if (!v1.IsNull()) {
            const gp_Pnt p = BRep_Tool::Pnt(v1);
            a = geometry::occt::core::from_gp_to_array(p);
        }
        if (!v2.IsNull()) {
            const auto p = BRep_Tool::Pnt(v2);
            b = geometry::occt::core::from_gp_to_array(p);
        }
        return {a, b};
    }

    Edge::Curve Edge::curve() const {
        if (!is_valid()) return {};
        Standard_Real u0 = 0, u1 = 0;
        Handle(Geom_Curve) c = BRep_Tool::Curve(pimple_->edge, u0, u1);
        if (c.IsNull()) return {};
        return geometry::occt::core::occt_curve_access::make(c);
    }
}

#endif