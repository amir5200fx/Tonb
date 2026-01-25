//
// Created by amir on 1/24/26.
//
#include <tonb/cad2d/validate/halfedge_checks.hxx>

#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/vertex.hxx>

#include <iostream>

namespace tonb::cad2d::validate {
    namespace {

        /**
         * @brief Build a consistent prefix for error messages.
         *
         * Internal halper so that all error messages identity the same context.
         */
        std::string ctx(const std::shared_ptr<topo::HalfEdge>& e) {
            if (!e) return "HalfEdgeChecks";
            return "HalfEdgeChecks (edge id=" + topo::to_string(e->id()) + ")";
        }

        /**
         * @brief Safely lock a vertex reference and return either the shared pointer
         *        or a Result error.
         */
        topo::Result<std::shared_ptr<topo::Vertex>> lock_vertex(const std::shared_ptr<topo::HalfEdge>& e, const std::weak_ptr<topo::Vertex>& w, const char* which) {
            auto v = w.lock();
            if (!v) {
                return topo::Result<std::shared_ptr<topo::Vertex>>(topo::ResultError{
                    ctx(e) + ": " + std::string(which) + " vertex reference is missing or expired", topo::ErrorCode::topology_error
                });
            }
            return topo::ok(std::move(v));
        }

        /**
         * @brief Safely lock a half-edge reference and return either the shared pointer
         *        or a Result error.
         */
        topo::Result<std::shared_ptr<topo::HalfEdge>> lock_edge(const std::shared_ptr<topo::HalfEdge>& e, const std::weak_ptr<topo::HalfEdge>& w, const char* which) {
            auto he = w.lock();
            if (!he) {
                return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                    ctx(e) + ": " + std::string(which) + " half-edge reference is missing or expired", topo::ErrorCode::topology_error
                });
            }
            return topo::ok(std::move(he));
        }
    }


    topo::Result<void> check_endpoints(const std::shared_ptr<topo::HalfEdge> &e) {
        // Defensive check: callers may pass null during testing or after erasure.
        if (!e) {
            return topo::Result<void>(topo::ResultError{
                "HalfEdgeChecks: edge pointer is null", topo::ErrorCode::invalid_input
            });
        }

        // Lock start and end vertices. Expired weak references indicate broken topology.
        auto rs = lock_vertex(e, e->start(), "start");
        if (!rs) return topo::Result<void>(rs.error());

        auto re = lock_vertex(e, e->end(), "end");
        if (!re) return topo::Result<void>(re.error());

        // Basic non-degeneracy: a half-edge cannot start and end at the same vertex.
        // Builders should prevent this, but validators must catch it.
        if (rs.value()->id() == re.value()->id()) {
            return topo::Result<void>(topo::ResultError{
                ctx(e) + ": degenerate edge, start and end vertices are identical (vetex id=" +
                    topo::to_string(rs.value()->id()) + ")", topo::ErrorCode::degenerate
            });
        }
        return {}; // success
    }

    topo::Result<void> check_twin(const std::shared_ptr<topo::HalfEdge> &e) {
        if (!e) {
            return topo::Result<void>(topo::ResultError{
                "HalfEdgeChecks: edge pointer is null", topo::ErrorCode::invalid_input
            });
        }

        // If no twin is set, this is not a failure in this library stage.
        // Some models are open or not yet paired by the builder.
        if (!e->twin()) {
            return {};
        }

        // Lock twin.
        auto rt = lock_edge(e, e->twin(), "twin");
        if (!rt) return topo::Result<void>(rt.error());

        const auto& t = rt.value();

        // Twin must point back.
        auto t_back = t->twin();
        if (t_back != e) {
            return topo::Result<void>(topo::ResultError{
                ctx(e) + ": twin edge does not point back to this edge (twin id=" + topo::to_string(t->id()) + ")", topo::ErrorCode::topology_error
            });
        }

        if (t_back->id() != e->id()) {
            return topo::Result<void>(topo::ResultError{
                ctx(e) + ": twin symmetry violated, twin->twin does not reference this edge (twin id=" + topo::to_string(t->id()) + ", twin->twin id=" + topo::to_string(t_back->id()) + ")", topo::ErrorCode::validation_failed
            });
        }

        // Endpoint reversal across twins.
        // We validate using vertex ids because pointer identity should align with ids.
        auto es = lock_vertex(e, e->start(), "start");
        if (!es) return topo::Result<void>(es.error());
        auto ee = lock_vertex(e, e->end(), "end");
        if (!ee) return topo::Result<void>(ee.error());

        auto ts = lock_vertex(t, t->start(), "twin.start");
        if (!ts) return topo::Result<void>(ts.error());
        auto te = lock_vertex(t, t->end(), "twin.end");
        if (!te) return topo::Result<void>(te.error());

        if (es.value()->id() != te.value()->id() || ee.value()->id() != ts.value()->id()) {
            return topo::Result<void>(topo::ResultError{
                ctx(e) + ": twin endpoints are not reversed as expected (edge start= " +
                topo::to_string(es.value()->id()) + ", edge end= " + topo::to_string(ee.value()->id()) +
                "), twin start=" + topo::to_string(ts.value()->id()) + ", twin end=" + topo::to_string(te.value()->id())
                + ")",
                topo::ErrorCode::validation_failed
            });
        }
        return {};
    }

    topo::Result<void> check_next_prev(const std::shared_ptr<topo::HalfEdge> &e) {
        if (!e) {
            return topo::Result<void>(topo::ResultError{
                "HalfEdgeChecks: edge pointer is null", topo::ErrorCode::invalid_input
            });
        }

        // next -> prev must point back
        if (e->next()) {
            auto rn = lock_edge(e, e->next(), "next");
            if (!rn) return topo::Result<void>(rn.error());

            const auto n_prev = rn.value()->prev();
            if (!n_prev) {
                return topo::Result<void>(topo::ResultError{
                    ctx(e) + ": next exists but next->prev is missing or expired (next id=" + topo::to_string(rn.value()->id()) + ")", topo::ErrorCode::topology_error
                });
            }

            if (n_prev->id() != e->id()) {
                return topo::Result<void>(topo::ResultError{
                    ctx(e) + ": next/prev consistency violated, next->prev is not this edge (next id=" +
                        topo::to_string(rn.value()->id()) + ", next->prev id=" + topo::to_string(n_prev->id()) + ")",
                    topo::ErrorCode::validation_failed
                });
            }
        }

        // prev -> next must point back
        if (e->prev()) {
            auto rp = lock_edge(e, e->prev(), "prev");
            if (!rp) return topo::Result<void>(rp.error());

            const auto p_next = rp.value()->next();
            if (!p_next) {
                return topo::Result<void>(topo::ResultError{
                    ctx(e) + ": prev exists but prev->next is missing or expired (prev id=" +
                        topo::to_string(rp.value()->id()) + ")",
                    topo::ErrorCode::topology_error
                });
            }

            if (p_next->id() != e->id()) {
                return topo::Result<void>(topo::ResultError{
                    ctx(e) + ": prev/next consistency violated, prev->next is not this edge (prev id=" +
                        topo::to_string(rp.value()->id()) + ", prev->next id=" + topo::to_string(p_next->id()) + ")",
                    topo::ErrorCode::validation_failed
                });
            }
        }
        return {};
    }

    topo::Result<void> check_halfedge(const std::shared_ptr<topo::HalfEdge> &e) {
        // Keep the order deterministic so tests get stable failure messages.
        if (auto r0 = check_endpoints(e); !r0) return r0;

        if (auto r1 = check_twin(e); !r1) return r1;

        if (auto r2 = check_next_prev(e); !r2) return r2;

        return {};
    }
}
