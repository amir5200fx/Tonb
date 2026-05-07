//
// Created by amir on 1/24/26.
//
/**
 * @file halfedge_checks.cxx
 * @brief Implements topology-only validation routines for topo::HalfEdge.
 */
#include <tonb/cad2d/validate/halfedge_checks.hxx>

#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/orientation.hxx>
#include <tonb/cad2d/topo/id.hxx>

namespace tonb::cad2d::validate {
    namespace {

        std::string ctx(const std::shared_ptr<topo::HalfEdge>& e) {
            if (!e) return "HalfEdgeChecks";
            return "HalfEdgeChecks (edge id=" + topo::to_string(e->id()) + ")";
        }

        topo::Result<void> fail(std::string msg, const topo::ErrorCode code) {
            return topo::Result<void>(topo::ResultError{std::move(msg), code});
        }
    }

    topo::Result<void> check_endpoints(const std::shared_ptr<topo::HalfEdge>& e) {
        if (!e) {
            return fail("HalfEdgeChecks: half-edge pointer is null", topo::ErrorCode::invalid_input);
        }

        const auto v0 = e->start();
        const auto v1 = e->end();
        if (!v0) {
            return fail(ctx(e) + ": start vertex reference is missing or expired", topo::ErrorCode::topology_error);
        }
        if (!v1) {
            return fail(ctx(e) + ": end vertex reference is missing or expired", topo::ErrorCode::topology_error);
        }
        if (v0->id() == v1->id()) {
            return fail(ctx(e) + ": start and end vertices collapse to the same vertex id=" + topo::to_string(v0->id()),
                        topo::ErrorCode::degenerate);
        }
        return {};
    }

    topo::Result<void> check_twin(const std::shared_ptr<topo::HalfEdge>& e) {
        if (!e) {
            return fail("HalfEdgeChecks: half-edge pointer is null", topo::ErrorCode::invalid_input);
        }

        const auto t = e->twin();
        if (!t) return {};

        if (t->id() == e->id()) {
            return fail(ctx(e) + ": twin points to the same half-edge", topo::ErrorCode::topology_error);
        }

        const auto tt = t->twin();
        if (!tt || tt->id() != e->id()) {
            return fail(ctx(e) + ": twin relationship is not reciprocal", topo::ErrorCode::topology_error);
        }

        const auto e0 = e->start();
        const auto e1 = e->end();
        const auto t0 = t->start();
        const auto t1 = t->end();
        if (e0 && e1 && t0 && t1) {
            if (e0->id() != t1->id() || e1->id() != t0->id()) {
                return fail(ctx(e) + ": twin endpoints do not reverse the same directed connection",
                            topo::ErrorCode::topology_error);
            }
        }

        if (e->curve_id() != t->curve_id()) {
            return fail(ctx(e) + ": twin uses a different curve id", topo::ErrorCode::topology_error);
        }

        if (e->orientation() == t->orientation()) {
            return fail(ctx(e) + ": twin has the same orientation instead of the opposite orientation",
                        topo::ErrorCode::topology_error);
        }

        return {};
    }

    topo::Result<void> check_next_prev(const std::shared_ptr<topo::HalfEdge>& e) {
        if (!e) {
            return fail("HalfEdgeChecks: half-edge pointer is null", topo::ErrorCode::invalid_input);
        }

        if (const auto n = e->next()) {
            if (n->id() == e->id()) {
                return fail(ctx(e) + ": next points to the same half-edge", topo::ErrorCode::topology_error);
            }
            const auto np = n->prev();
            if (!np || np->id() != e->id()) {
                return fail(ctx(e) + ": next->prev does not resolve back to the current half-edge",
                            topo::ErrorCode::topology_error);
            }
        }

        if (const auto p = e->prev()) {
            if (p->id() == e->id()) {
                return fail(ctx(e) + ": prev points to the same half-edge", topo::ErrorCode::topology_error);
            }
            const auto pn = p->next();
            if (!pn || pn->id() != e->id()) {
                return fail(ctx(e) + ": prev->next does not resolve back to the current half-edge",
                            topo::ErrorCode::topology_error);
            }
        }

        return {};
    }

    topo::Result<void> check_halfedge(const std::shared_ptr<topo::HalfEdge>& e) {
        if (auto r = check_endpoints(e); !r) return r;
        if (auto r = check_twin(e); !r) return r;
        if (auto r = check_next_prev(e); !r) return r;
        return {};
    }
}
