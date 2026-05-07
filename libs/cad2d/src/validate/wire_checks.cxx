//
// Created by amir on 1/24/26.
//
/**
 * @file wire_checks.cxx
 * @brief Implements topology-only validation routines for topo::Wire.
 */
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

        topo::Result<void> fail(std::string msg, const topo::ErrorCode code) {
            return topo::Result<void>(topo::ResultError{std::move(msg), code});
        }
    }

    topo::Result<void> check_boundary_refs(const std::shared_ptr<topo::Wire>& w, const bool allowEmpty) {
        if (!w) {
            return fail("WireChecks: wire pointer is null", topo::ErrorCode::invalid_input);
        }

        if (w->empty()) {
            if (allowEmpty) return {};
            return fail(ctx(w) + ": wire boundary is empty", topo::ErrorCode::validation_failed);
        }

        const auto edges = w->edges_locked();
        if (edges.empty()) {
            if (allowEmpty) return {};
            return fail(ctx(w) + ": locking the boundary produced an empty edge list",
                        topo::ErrorCode::topology_error);
        }

        for (std::size_t i = 0; i < edges.size(); ++i) {
            if (!edges[i]) {
                return fail(ctx(w) + ": boundary contains an expired edge reference at index " + std::to_string(i),
                            topo::ErrorCode::topology_error);
            }
        }

        return {};
    }

    topo::Result<void> check_continuity(const std::shared_ptr<topo::Wire>& w,
                                        const topo::Tolerance& tol,
                                        const bool requireClosed) {
        if (!w) {
            return fail("WireChecks: wire pointer is null", topo::ErrorCode::invalid_input);
        }

        if (const auto rc = w->check_continuous(tol); !rc) {
            return fail(ctx(w) + ": continuity check failed (" + rc.error().message + ")", rc.error().code);
        }

        if (requireClosed) {
            if (const auto rr = w->check_closed(tol); !rr) {
                return fail(ctx(w) + ": closure check failed (" + rr.error().message + ")", rr.error().code);
            }
        }

        return {};
    }

    topo::Result<void> check_next_prev_matches_boundary(const std::shared_ptr<topo::Wire>& w,
                                                        const bool requireClosed,
                                                        const bool verifyOpenEnds) {
        if (!w) {
            return fail("WireChecks: wire pointer is null", topo::ErrorCode::invalid_input);
        }

        const auto edges = w->edges_locked();
        if (edges.empty()) {
            return fail(ctx(w) + ": wire boundary is empty", topo::ErrorCode::validation_failed);
        }

        const std::size_t n = edges.size();
        for (std::size_t i = 0; i < n; ++i) {
            const auto& ei = edges[i];
            if (!ei) {
                return fail(ctx(w) + ": boundary contains an expired edge reference at index " + std::to_string(i),
                            topo::ErrorCode::topology_error);
            }

            const auto expectedNext = requireClosed ? edges[(i + 1) % n] : (i + 1 < n ? edges[i + 1] : nullptr);
            const auto expectedPrev = requireClosed ? edges[(i + n - 1) % n] : (i > 0 ? edges[i - 1] : nullptr);

            if (const auto next = ei->next()) {
                if (!expectedNext) {
                    if (!requireClosed && verifyOpenEnds) {
                        return fail(ctx(w) + ": open-wire end has an unexpected next link (edge id=" +
                                        topo::to_string(ei->id()) + ")",
                                    topo::ErrorCode::validation_failed);
                    }
                } else if (next->id() != expectedNext->id()) {
                    return fail(ctx(w) + ": next link does not match boundary order at index " + std::to_string(i),
                                topo::ErrorCode::validation_failed);
                }
            } else if (!requireClosed && verifyOpenEnds && i != n - 1) {
                return fail(ctx(w) + ": interior edge is missing a next link (edge id=" + topo::to_string(ei->id()) + ")",
                            topo::ErrorCode::validation_failed);
            }

            if (const auto prev = ei->prev()) {
                if (!expectedPrev) {
                    if (!requireClosed && verifyOpenEnds) {
                        return fail(ctx(w) + ": open-wire start has an unexpected prev link (edge id=" +
                                        topo::to_string(ei->id()) + ")",
                                    topo::ErrorCode::validation_failed);
                    }
                } else if (prev->id() != expectedPrev->id()) {
                    return fail(ctx(w) + ": prev link does not match boundary order at index " + std::to_string(i),
                                topo::ErrorCode::validation_failed);
                }
            } else if (!requireClosed && verifyOpenEnds && i != 0) {
                return fail(ctx(w) + ": interior edge is missing a prev link (edge id=" + topo::to_string(ei->id()) + ")",
                            topo::ErrorCode::validation_failed);
            }
        }

        return {};
    }

    topo::Result<void> check_wire(const std::shared_ptr<topo::Wire>& w,
                                  const topo::Tolerance& tol,
                                  const bool requireClosed,
                                  const bool verifyOpenEnds) {
        if (auto r = check_boundary_refs(w, false); !r) return r;
        if (auto r = check_continuity(w, tol, requireClosed); !r) return r;
        if (auto r = check_next_prev_matches_boundary(w, requireClosed, verifyOpenEnds); !r) return r;
        return {};
    }
}
