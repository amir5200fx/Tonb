//
// Created by amir on 1/24/26.
//
#include <tonb/cad2d/validate/wire_checks.hxx>

#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/id.hxx>

namespace tonb::cad2d::validate {
    namespace {
        std::string ctx(const std::shared_ptr<topo::Wire>& w) {
            if (!w) return "WireChecks";
            return "WireChecks (wire id=" + topo::to_string(w->id()) + ")";
        }

        topo::Result<std::shared_ptr<topo::HalfEdge>> edge_at(const std::shared_ptr<topo::Wire>& w, const std::vector<std::shared_ptr<topo::HalfEdge>>& edges, const std::size_t i) {
            if (i >= edges.size() || !edges[i]) {
                return topo::Result<std::shared_ptr<topo::HalfEdge>>(topo::ResultError{
                    ctx(w) + ": boundary edge reference is missing or expired at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }
            // Copying shared_ptr here is intentional: it keeps ownership semantics explicit.
            return topo::ok(std::shared_ptr<topo::HalfEdge>(edges[i]));
        }
    }


    topo::Result<void> check_boundary_refs(const std::shared_ptr<topo::Wire> &w, const bool allowEmpty) {
        if (!w) {
            return topo::Result<void>(topo::ResultError{
                "WireChecks: wire pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        if (w->empty()) {
            if (allowEmpty) return {};
            return topo::Result<void>(topo::ResultError{
                ctx(w) + ": wire boundary is emtpy",
                topo::ErrorCode::validation_failed
            });
        }

        // This locks all boundary weak pointers into shared pointers, returning nullptr for expired ones.
        const auto edges = w->edges_locked();
        if (edges.empty()) {
            // Defensive: empty after lock is unusual; treat as invalid unless allowEmtpy.
            if (allowEmpty) return {};
            return topo::Result<void>(topo::ResultError{
                ctx(w) + ": Boundary lock produces an empty edge list",
                topo::ErrorCode::topology_error
            });
        }

        for (std::size_t i = 0; i < edges.size(); ++i) {
            if (!edges[i]) {
                return topo::Result<void>(topo::ResultError{
                    ctx(w) + ": boundary contains an expired edge reference at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }
        }
        return {};
    }

    topo::Result<void> check_continuity(const std::shared_ptr<topo::Wire> &w, const topo::Tolerance &tol,
        const bool requireClosed) {
        if (!w) {
            return topo::Result<void>(topo::ResultError{
                "WireChecks: wire pointer is null", topo::ErrorCode::invalid_input
            });
        }

        // We prefer to use Wire's own checks so there is a single of truth for continuity rules.
        if (const auto rc = w->check_continuous(tol); !rc) {
            return topo::Result<void>(topo::ResultError{
                ctx(w) + ": continuity check failed (" + rc.error().message + ")", rc.error().code
            });
        }

        if (requireClosed) {
            if (const auto rcl = w->check_closed(tol); !rcl) {
                return topo::Result<void>(topo::ResultError{
                    ctx(w) + ": closure check failed (" + rcl.error().message + ")", rcl.error().code
                });
            }
        }

        return {};
    }

    topo::Result<void> check_next_prev_matches_boundary(const std::shared_ptr<topo::Wire> &w, const bool requireClosed,
        const bool verifyOpenEnds) {
        if (!w) {
            return topo::Result<void>(topo::ResultError{
                "WireChecks: wire pointer is null", topo::ErrorCode::invalid_input
            });
        }

        const auto edges = w->edges_locked();
        if (edges.empty()) {
            return topo::Result<void>(topo::ResultError{
                ctx(w) + ": boundary is emtpy", topo::ErrorCode::validation_failed
            });
        }

        const std::size_t n = edges.size();

        // For open wires, the boundary order is linear. For closed wires, it is cyclic.
        // This check only validates next/rev links when they are present.
        for (std::size_t i = 0; i < n; ++i) {
            const auto& ei = edges[i];
            if (!ei) {
                return topo::Result<void>(topo::ResultError{
                    ctx(w) + ": boundary contains an expired edge reference at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }

            // Determine the expected neighbours in the boundary ordering
            const bool hasNextIndex = (i + 1 < n);
            const bool hasPrevIndex = (i > 0);

            const std::shared_ptr<topo::HalfEdge> expectedNext =
                requireClosed ? edges[(i + 1) % n] : (hasNextIndex ? edges[i + 1] : nullptr);

            const std::shared_ptr<topo::HalfEdge> expectedPrev =
                requireClosed ? edges[(i - 1 + n) % n] : (hasPrevIndex ? edges[i - 1] : nullptr);

            // Validate next if it exists
            if (const auto next = ei->next(); next) {
                if (expectedNext && next->id() != expectedNext->id()) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(w) + ": next link does not match boundary order at index " + std::to_string(i) +
                          " (edge id=" + topo::to_string(ei->id()) + ", next id=" + topo::to_string(next->id()) +
                          ", expected next id=" + topo::to_string(expectedNext->id()) + ")",
                        topo::ErrorCode::validation_failed
                    });
                }
                if (!expectedNext && !requireClosed && verifyOpenEnds) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(w) + ": open wire end has a next link but none is expected (edge id=" + topo::to_string(ei->id()) + ")",
                        topo::ErrorCode::validation_failed
                    });
                }
            } else {
                // next() == nullptr
                if (!requireClosed && verifyOpenEnds && i == n - 1) {
                    // ok: open chain end should not have a next link
                }
            }

            // Validate prev if it exists.
            if (const auto prev = ei->prev(); prev) {
                if (expectedPrev && prev->id() != expectedPrev->id()) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(w) + ": prev link does not match boundary order at index " + std::to_string(i) +
                            " (edge id=" + topo::to_string(ei->id()) + ", prev id=" + topo::to_string(prev->id()) +
                                ", expected prev id=" + topo::to_string(expectedPrev->id()) + ")",
                        topo::ErrorCode::validation_failed
                    });
                }
                if (!expectedPrev && !requireClosed && verifyOpenEnds) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(w) + ": open wire start has a prev link but not is expected (edge id=" + topo::to_string(ei->id()) + ")",
                        topo::ErrorCode::validation_failed
                    });
                }
            } else {
                // prev() == nullptr
                if (!requireClosed && verifyOpenEnds && i == 0) {
                    // ok: open chain start should not have a prev link
                }
            }
        }
        return {};
    }

    topo::Result<void> check_wire(const std::shared_ptr<topo::Wire> &w, const topo::Tolerance &tol, const bool requireClosed,
        const bool verifyOpenEnds) {
        if (const auto r0 = check_boundary_refs(w, /*allowEmpty=*/false); !r0) return r0;

        if (const auto r1 = check_continuity(w, tol, requireClosed); !r1) return r1;

        if (const auto r2 = check_next_prev_matches_boundary(w, requireClosed, verifyOpenEnds); !r2) return r2;

        return {};
    }
}
