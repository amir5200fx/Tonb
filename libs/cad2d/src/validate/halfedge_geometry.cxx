/**
* @file halfedge_geometry.cxx
 * @brief Implements geometry-aware half-edge validation.
 */
#include <tonb/cad2d/validate/halfedge_geometry.hxx>

#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <cmath>
#include <sstream>
#include <stdexcept>

namespace tonb::cad2d::validate {
    namespace {
        std::string ctx(const std::shared_ptr<topo::HalfEdge>& e) {
            if (!e) return "HalfEdgeGeometry";
            std::ostringstream oss;
            oss << "HalfEdgeGeometry: edge id=" << topo::to_string(e->id());
            return oss.str();
        }
    }

    topo::Result<void> check_halfedge_geometry(const std::shared_ptr<topo::HalfEdge> &e, const geom::CurveStore &store,
        const topo::Tolerance &tol) {
        if (!e) {
            return topo::Result<void>(topo::ResultError{
                "HalfEdgeGeometry: null half-edge",
                topo::ErrorCode::validation_failed
            });
        }

        // Defensive: required links.
        const auto v0 = e->start();
        const auto v1 = e->end();
        if (!v0 || !v1) {
            return topo::Result<void>(topo::ResultError{
                ctx(e) + ": start/end vertex is null",
                topo::ErrorCode::validation_failed
            });
        }

        const topo::Id cid = e->curve_id();
        if (cid == 0) {
            std::ostringstream oss;
            oss << ctx(e) <<": curve_id is invalid (0)"
                << " (u0=" << e->u0() << ", u1=" << e->u1() << ")";
            return topo::Result<void>(topo::ResultError{
                oss.str(),
                topo::ErrorCode::validation_failed
            });
        }

        // Resolve curve via store: CurveStore uses exceptions for programmer error,
        // so we translate them into Result failures here.
        const cad2d::Curve* cptr = nullptr;
        try {
            cptr = &store.get(cid);
        } catch (const std::out_of_range&) {
            std::ostringstream oss;
            oss << ctx(e) << ": curve not found in CurveStore"
                << " (curve id=" << cid << ", u0=" << e->u0() << ", u1=" << e->u1() << ")";
            return topo::Result<void>(topo::ResultError{
                oss.str(),
                topo::ErrorCode::validation_failed
            });
        } catch (const std::exception& ex) {
            std::ostringstream oss;
            oss << ctx(e) << ": failed to resolve curve from store"
                << " (curve id=" << cid << "): " << ex.what();
            return topo::Result<void>(topo::ResultError{
                oss.str(),
                topo::ErrorCode::internal
            });
        }

        const auto& curve = *cptr;

        // Evaluate curve at parameters.
        // No OCCT here; cad2d::Curve is a wrapper.
        geometry::Pnt2d p0;
        geometry::Pnt2d p1;
        try {
            p0 = geometry::Pnt2d{curve.value(e->u0())};
            p1 = geometry::Pnt2d{curve.value(e->u1())};
        } catch (const std::exception& ex) {
            std::ostringstream oss;
            oss << ctx(e) << ": curve evaluation failed"
                << " (curve id=" << cid << ", u0=" << e->u0() << ", u1=" << e->u1()
                << "): " << ex.what();
            return topo::Result<void>(topo::ResultError{
                oss.str(),
                topo::ErrorCode::geometry_error
            });
        }

        const auto& q0 = v0->position();
        const auto& q1 = v1->position();

        // Prefer exact Tolerance policy if available (equal helper).
        // We still compute numerical distances for diagnostics as required by the issue.
        const double d0 = geometry::distance(p0, q0);
        const double d1 = geometry::distance(p1, q1);

        // Tolerance interface in your cad2d/topo is expected to provide:
        // - tol.linear() -> double
        // - tol.equal(xa, ya, xb, yb) -> bool
        //
        // If your Tolerance differs, adjust the lines below locally (only here).
        const double lim = tol.linear();

        if (d0 > lim || d1 > lim) {
            std::ostringstream oss;
            oss << ctx(e)
                << ": vertex–curve endpoint mismatch"
                << " (curve id=" << cid
                << ", u0=" << e->u0() << ", u1=" << e->u1()
                << ", d_start=" << d0 << ", d_end=" << d1
                << ", tol=" << lim << ")";
            return topo::Result<void>(topo::ResultError{
                oss.str(),
                topo::ErrorCode::validation_failed
            });
        }

        return topo::Result<void>{}; // ok
    }
}
