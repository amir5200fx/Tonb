//
// Created by amir on 1/22/26.
//
/**
 * @file halfedge_builder.cxx
 * @brief Implements construction of half-edges and first-class topo::Edge pairs.
 */

#include <tonb/cad2d/builder/halfedge_builder.hxx>

#include <sstream>
#include <cmath>

#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/edge.hxx>
#include <tonb/cad2d/curve.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::HalfEdge>> HalfEdgeBuilder::create(
        const std::shared_ptr<topo::Vertex>& start,
        const std::shared_ptr<topo::Vertex>& end,
        const topo::Id curveId,
        const double u0,
        const double u1,
        const topo::Orientation dir,
        const double tol) const {

        if (!start || !end) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(
                "HalfEdgeBuilder: start or end vertex is null", topo::ErrorCode::invalid_input);
        }
        if (start->id() == end->id()) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(
                "HalfEdgeBuilder: start and end vertex must be distinct", topo::ErrorCode::degenerate);
        }

        auto e = shape_.make_halfedge(curveId, u0, u1, dir, tol);
        if (!e) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(
                "HalfEdgeBuilder: failed to allocate half-edge", topo::ErrorCode::internal);
        }

        e->set_start(start);
        e->set_end(end);

        if (!start->has_incident()) start->set_incident(e);
        if (!end->has_incident()) end->set_incident(e);

        return topo::ok(std::move(e));
    }

    namespace {
        bool in_range(const real u, const real a, const real b, const real eps) {
            return (u >= a - eps && u <= b + eps);
        }

        topo::Result<void> validate_curve_span(const Curve& curve, const real u0, const real u1,
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
                oss << "HalfEdgeBuilder: parameters out of curve domain (u0=" << u0 << ", u1=" << u1
                    << ", domain=[" << a << "," << b << "])";
                return topo::fail<void>(oss.str(), topo::ErrorCode::geometry_error);
            }
            if (std::abs(u1 - u0) < eps) {
                return topo::fail<void>("HalfEdgeBuilder: degenerate param span (u0 and u1 are equal)",
                                        topo::ErrorCode::degenerate);
            }
            if (dir == topo::Orientation::forward && !(u0 < u1)) {
                return topo::fail<void>("HalfEdgeBuilder: forward edge expects u0 < u1",
                                        topo::ErrorCode::invalid_input);
            }
            if (dir == topo::Orientation::reversed && !(u0 > u1)) {
                return topo::fail<void>("HalfEdgeBuilder: reversed edge expects u0 > u1",
                                        topo::ErrorCode::invalid_input);
            }
            return {};
        }
    }

    topo::Result<std::shared_ptr<topo::Edge>> HalfEdgeBuilder::create_edge(
        const std::shared_ptr<topo::Vertex>& a,
        const std::shared_ptr<topo::Vertex>& b,
        const topo::Id curveId,
        const double u0,
        const double u1,
        const double tol) const {

        auto ab = create(a, b, curveId, u0, u1, topo::Orientation::forward, tol);
        if (!ab) return topo::fail<std::shared_ptr<topo::Edge>>(ab.error().message, ab.error().code);

        auto ba = create(b, a, curveId, u1, u0, topo::Orientation::reversed, tol);
        if (!ba) return topo::fail<std::shared_ptr<topo::Edge>>(ba.error().message, ba.error().code);

        auto edge = shape_.make_edge();
        if (!edge) {
            return topo::fail<std::shared_ptr<topo::Edge>>(
                "HalfEdgeBuilder: failed to allocate topological edge", topo::ErrorCode::internal);
        }

        ab.value()->set_twin(ba.value());
        ba.value()->set_twin(ab.value());
        ab.value()->set_edge(edge);
        ba.value()->set_edge(edge);
        edge->set_forward(ab.value());
        edge->set_reverse(ba.value());

        return topo::ok(std::move(edge));
    }

    topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>> HalfEdgeBuilder::create_pair(
        const std::shared_ptr<topo::Vertex>& a,
        const std::shared_ptr<topo::Vertex>& b,
        const topo::Id curveId,
        const double u0,
        const double u1,
        const double tol) const {

        auto edge = create_edge(a, b, curveId, u0, u1, tol);
        if (!edge) {
            return topo::fail<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(
                edge.error().message, edge.error().code);
        }
        return topo::ok(std::make_pair(edge.value()->forward(), edge.value()->reverse()));
    }

    topo::Result<std::shared_ptr<topo::HalfEdge>> HalfEdgeBuilder::create_from_curve(
        geom::CurveStore& store,
        const Curve& curve,
        const std::shared_ptr<topo::Vertex>& start,
        const std::shared_ptr<topo::Vertex>& end,
        const real u0,
        const real u1,
        const topo::Orientation dir,
        const real tol,
        const real eps) const {

        if (const auto r = validate_curve_span(curve, u0, u1, dir, eps); !r) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(r.error().message, r.error().code);
        }
        const auto curveId = store.add(curve);
        if (curveId == 0) {
            return topo::fail<std::shared_ptr<topo::HalfEdge>>(
                "HalfEdgeBuilder: CurveStore returned invalid curve id=0", topo::ErrorCode::internal);
        }
        return create(start, end, curveId, u0, u1, dir, tol);
    }

    topo::Result<std::shared_ptr<topo::Edge>> HalfEdgeBuilder::create_edge_from_curve(
        geom::CurveStore& store,
        const Curve& curve,
        const std::shared_ptr<topo::Vertex>& a,
        const std::shared_ptr<topo::Vertex>& b,
        const real u0,
        const real u1,
        const real tol,
        const real eps) const {

        if (const auto r = validate_curve_span(curve, u0, u1, topo::Orientation::forward, eps); !r) {
            return topo::fail<std::shared_ptr<topo::Edge>>(r.error().message, r.error().code);
        }
        const auto curveId = store.add(curve);
        if (curveId == 0) {
            return topo::fail<std::shared_ptr<topo::Edge>>(
                "HalfEdgeBuilder: CurveStore returned invalid curve id=0", topo::ErrorCode::internal);
        }
        return create_edge(a, b, curveId, u0, u1, tol);
    }

    topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>> HalfEdgeBuilder::create_pair_from_curve(
        geom::CurveStore& store,
        const Curve& curve,
        const std::shared_ptr<topo::Vertex>& a,
        const std::shared_ptr<topo::Vertex>& b,
        const real u0,
        const real u1,
        const real tol,
        const real eps) const {

        auto edge = create_edge_from_curve(store, curve, a, b, u0, u1, tol, eps);
        if (!edge) {
            return topo::fail<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(
                edge.error().message, edge.error().code);
        }
        return topo::ok(std::make_pair(edge.value()->forward(), edge.value()->reverse()));
    }
}
