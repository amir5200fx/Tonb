//
// Created by amir on 5/7/26.
//
/**
 * @file edge_checks.cxx
 * @brief Implements validation routines for topo::Edge.
 */

#include <tonb/cad2d/validate/edge_checks.hxx>

#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/edge.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/id.hxx>

namespace tonb::cad2d::validate {
    namespace {
        std::string ctx(const std::shared_ptr<topo::Edge>& edge) {
            if (!edge) return "EdgeChecks";
            return "EdgeChecks (edge id=" + topo::to_string(edge->id()) + ")";
        }

        topo::Result<void> fail(std::string msg, const topo::ErrorCode code) {
            return topo::Result<void>(topo::ResultError{std::move(msg), code});
        }
    }

    topo::Result<void> check_edge_membership(const std::shared_ptr<topo::Edge>& edge) {
        if (!edge) {
            return fail("EdgeChecks: edge pointer is null", topo::ErrorCode::invalid_input);
        }
        const auto fwd = edge->forward();
        const auto rev = edge->reverse();
        if (!fwd) {
            return fail(ctx(edge) + ": forward half-edge reference is missing or expired", topo::ErrorCode::topology_error);
        }
        if (!rev) {
            return fail(ctx(edge) + ": reverse half-edge reference is missing or expired", topo::ErrorCode::topology_error);
        }
        if (fwd->id() == rev->id()) {
            return fail(ctx(edge) + ": forward and reverse half-edges resolve to the same object", topo::ErrorCode::topology_error);
        }
        const auto fwd_owner = fwd->edge();
        const auto rev_owner = rev->edge();
        if (!fwd_owner || fwd_owner->id() != edge->id()) {
            return fail(ctx(edge) + ": forward half-edge does not point back to the owning edge", topo::ErrorCode::topology_error);
        }
        if (!rev_owner || rev_owner->id() != edge->id()) {
            return fail(ctx(edge) + ": reverse half-edge does not point back to the owning edge", topo::ErrorCode::topology_error);
        }
        return {};
    }

    topo::Result<void> check_edge_pair(const std::shared_ptr<topo::Edge>& edge) {
        if (auto r = check_edge_membership(edge); !r) return r;

        const auto fwd = edge->forward();
        const auto rev = edge->reverse();
        const auto tf = fwd->twin();
        const auto tr = rev->twin();
        if (!tf || tf->id() != rev->id()) {
            return fail(ctx(edge) + ": forward half-edge twin does not resolve to the reverse half-edge", topo::ErrorCode::topology_error);
        }
        if (!tr || tr->id() != fwd->id()) {
            return fail(ctx(edge) + ": reverse half-edge twin does not resolve to the forward half-edge", topo::ErrorCode::topology_error);
        }

        const auto a = fwd->start();
        const auto b = fwd->end();
        const auto c = rev->start();
        const auto d = rev->end();
        if (!a || !b || !c || !d) {
            return fail(ctx(edge) + ": one or more endpoint references are missing while checking the pair", topo::ErrorCode::topology_error);
        }
        if (a->id() != d->id() || b->id() != c->id()) {
            return fail(ctx(edge) + ": forward and reverse half-edges do not reverse the same endpoint pair", topo::ErrorCode::topology_error);
        }
        if (fwd->curve_id() != rev->curve_id()) {
            return fail(ctx(edge) + ": half-edge pair uses different curve ids", topo::ErrorCode::topology_error);
        }
        if (fwd->orientation() == rev->orientation()) {
            return fail(ctx(edge) + ": half-edge pair stores the same orientation on both directions", topo::ErrorCode::topology_error);
        }
        if (!(fwd->u0() == rev->u1() && fwd->u1() == rev->u0())) {
            return fail(ctx(edge) + ": half-edge pair does not carry reversed parameter spans", topo::ErrorCode::topology_error);
        }
        return {};
    }

    topo::Result<void> check_edge(const std::shared_ptr<topo::Edge>& edge) {
        if (auto r = check_edge_membership(edge); !r) return r;
        if (auto r = check_edge_pair(edge); !r) return r;
        return {};
    }
}
