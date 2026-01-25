//
// Created by amir on 1/22/26.
//

#include <tonb/cad2d/builder/halfedge_builder.hxx>

#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/curve.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::HalfEdge>> HalfEdgeBuilder::create(const std::shared_ptr<topo::Vertex> &start,
        const std::shared_ptr<topo::Vertex> &end, const topo::Id curveId, const double u0, const double u1,
        const topo::Orientation dir,
        const double tol) const {
        if (!start || !end) {
            return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                "HalfEdgeBuilder: start or end vertex is null", topo::ErrorCode::invalid_input
            });
        }
        if (start->id() == end->id()) {
            return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                "HalfEdgeBuilder: start and end vertex must be distinct", topo::ErrorCode::degenerate
            });
        }

        auto e = shape_.make_halfedge(curveId, u0, u1, dir, tol);
        if (!e) {
            return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                "HalfEdgeBuilder: failed to allocate half-edge", topo::ErrorCode::internal
            });
        }

        e->set_start(start);
        e->set_end(end);

        if (!start->has_incident()) start->set_incident(e);
        if (!end->has_incident()) end->set_incident(e);

        return topo::ok(std::move(e));
    }

    topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>> HalfEdgeBuilder::
    create_pair(const std::shared_ptr<topo::Vertex> &a, const std::shared_ptr<topo::Vertex> &b, const topo::Id curveId,
        const double u0, const double u1, const double tol) const {
        auto ab = create(a, b, curveId, u0, u1, topo::Orientation::forward, tol);
        if (!ab) return topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<
            topo::HalfEdge> > >(ab.error());

        auto ba = create(b, a, curveId, u0, u1, topo::Orientation::reversed, tol);
        if (!ba) return topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<
            topo::HalfEdge> > >(ba.error());

        ab.value()->set_twin(ba.value());
        ba.value()->set_twin(ab.value());

        return topo::ok(std::make_pair(std::move(ab.value()), std::move(ba.value())));
    }

    namespace {
        bool in_range(const real u, const real a, const real b, const real eps) {
            // Accept slight epsilon overshoot to avoid numerical noise at endpoints.
            return (u >= a - eps && u <= b + eps);
        }

        topo::Result<void> validate_curve_span(const Curve &curve, const real u0, const real u1,
                                               const topo::Orientation dir, const real eps) {
            if (!curve.is_valid()) {
                return topo::fail<void>("HalfEdgeBuilder: curve is not valid", topo::ErrorCode::geometry_error);
            }

            const auto rng = curve.parameter_range();
            if (!rng) {
                return topo::fail<void>("HalfEdgeBuilder: curve is unbounded (parameter_range is empty)",
                                        topo::ErrorCode::geometry_error);
            }

            const real a = rng->first;
            const real b = rng->second;

            if (!in_range(u0, a, b, eps) || !in_range(u1, a, b, eps)) {
                std::ostringstream oss;
                oss << "HalfEdgeBuilder: parameters out of curve domain "
                << "(u0=" << u0 << ", u1=" << u1 << ", domain=[" << a << "," << b << "])";
                return topo::fail<void>(oss.str(), topo::ErrorCode::geometry_error);
            }

            // Degeneracy
            if (std::abs(u1 - u0) < eps) {
                return topo::fail<void>("HalfEdgeBuilder: degenerate param span (u0 and u1 are equal)",
                                        topo::ErrorCode::degenerate);
            }

            // Enforce ordering by orientation to keep the model deterministic.
            if (dir == topo::Orientation::forward && !(u0 < u1)) {
                return topo::fail<void>("HalfEdgeBuilder: forward edge expects u0 < u1",
                                        topo::ErrorCode::invalid_input);
            }
            if (dir == topo::Orientation::reversed && !(u0 > u1)) {
                return topo::fail<void>("HalfEdgeBuilder: reversed edge expects u0 > u1",
                                        topo::ErrorCode::invalid_input);
            }
            return {}; // success
        }
    }

    topo::Result<std::shared_ptr<topo::HalfEdge>> HalfEdgeBuilder::create_from_curve(geom::CurveStore &store,
        const Curve &curve, const std::shared_ptr<topo::Vertex> &start, const std::shared_ptr<topo::Vertex> &end,
        const real u0, const real u1, const topo::Orientation dir, const real tol, const real eps) const {
        if (!start || !end) {
            return topo::fail<std::shared_ptr<topo::HalfEdge> >(
                "HalfEdgeBuilder::create_from_curve: start/end vertex is null", topo::ErrorCode::invalid_input);
        }

        // Validate geometry span first, before registering anything.
        if (const auto ok = validate_curve_span(curve, u0, u1, dir, eps); !ok) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(ok.error().message, ok.error().code);
        }

        topo::Id cid = 0;
        try {
            cid = store.add(curve);
        } catch (const std::exception &e) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(
            std::string("HalfEdgeBuilder::create_from_curve: failed to register curve: ") + e.what(),
            topo::ErrorCode::internal
                );
        }

        // Delegate to the pure topology creator.
        return create(start, end, cid, u0, u1, dir, tol);
    }

    topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>> HalfEdgeBuilder::
    create_pair_from_curve(geom::CurveStore &store, const Curve &curve, const std::shared_ptr<topo::Vertex> &a,
        const std::shared_ptr<topo::Vertex> &b, real u0, real u1, real tol, real eps) const {
        if (!a || !b) {
            return topo::fail<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(
            "HalfEdgeBuilder::create_pair_from_curve: vertex is null",
            topo::ErrorCode::invalid_input
                );
        }

        // For the forward edge we assume forward orientation and u0<u1.
        if (const auto ok = validate_curve_span(curve, u0, u1, topo::Orientation::forward, eps); !ok) {
            return topo::fail<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(
                ok.error().message, ok.error().code
            );
        }

        topo::Id cid = 0;
        try {
            cid = store.add(curve);
        } catch (const std::exception &e) {
            return topo::fail<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(
               std::string("HalfEdgeBuilder::create_pair_from_curve: failed to register curve: ") + e.what(),
               topo::ErrorCode::internal
           );
        }

        // Reuse the existing topology pair creator.
        // It will create (ab, ba). The reverse edge parameters are handled there
        // (if not, we will adjust it in that implementation).
        return create_pair(a, b, cid, u0, u1, tol);
    }
}
