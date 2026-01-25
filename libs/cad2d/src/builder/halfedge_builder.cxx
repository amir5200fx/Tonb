//
// Created by amir on 1/22/26.
//

#include <tonb/cad2d/builder/halfedge_builder.hxx>

#include <tonb/cad2d/topo/vertex.hxx>

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::HalfEdge>> HalfEdgeBuilder::create(const std::shared_ptr<topo::Vertex> &start,
        const std::shared_ptr<topo::Vertex> &end, const topo::Id curveId, const double u0, const double u1, const topo::Orientation dir,
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
        if (!ab) return topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(ab.error());

        auto ba = create(b, a, curveId, u0, u1, topo::Orientation::reversed, tol);
        if (!ba) return topo::Result<std::pair<std::shared_ptr<topo::HalfEdge>, std::shared_ptr<topo::HalfEdge>>>(ba.error());

        ab.value()->set_twin(ba.value());
        ba.value()->set_twin(ab.value());

        return topo::ok(std::make_pair(std::move(ab.value()), std::move(ba.value())));
    }
}
