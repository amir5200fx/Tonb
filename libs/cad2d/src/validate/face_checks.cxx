//
// Created by amir on 1/24/26.
//
#include <tonb/cad2d/validate/face_checks.hxx>

#include <tonb/cad2d/topo/face.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/validate/wire_checks.hxx>

#include <unordered_set>


namespace tonb::cad2d::validate {
    namespace {
        std::string ctx(const std::shared_ptr<topo::Face>& f) {
            if (!f) return "FaceChecks";
            return "FaceChecks (face id=" + topo::to_string(f->id()) + ")";
        }

        /**
         * @brief Lock the outer wire and hole wires, returning a flat list.
         *
         * The first entry is the outer wire, followed by holes.
         * Returns errors if references are missing or expired.
         */
        topo::Result<std::vector<std::shared_ptr<topo::Wire>>>
        lock_face_wires(const std::shared_ptr<topo::Face>& f) {
            if (!f) {
                return topo::Result<std::vector<std::shared_ptr<topo::Wire>>>(topo::ResultError{
                    "FaceChecks: face pointer is null", topo::ErrorCode::invalid_input
                });
            }

            const auto outer = f->outer();
            if (!outer) {
                return topo::Result<std::vector<std::shared_ptr<topo::Wire>>>(topo::ResultError{
                    ctx(f) + ": outer wire reference is missing or expired", topo::ErrorCode::topology_error
                });
            }

            std::vector<std::shared_ptr<topo::Wire>> out;
            out.reserve(1 + f->hole_count());
            out.push_back(outer);

            const auto holes = f->holes_locked();
            for (std::size_t i = 0; i < holes.size(); ++i) {
                if (!holes[i]) {
                    return topo::Result<std::vector<std::shared_ptr<topo::Wire>>>(topo::ResultError{
                        ctx(f) + ": hole wire reference is missing or expired at index" + std::to_string(i),
                        topo::ErrorCode::topology_error
                    });
                }
                out.push_back(holes[i]);
            }
            return topo::ok(std::move(out));
        }

        topo::Result<void> insert_wire_edges(const std::shared_ptr<topo::Face>& f, const std::shared_ptr<topo::Wire>& w, std::unordered_set<const topo::HalfEdge*>& set, const char* which) {
            if (!w) {
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ":" + which + " wire pointer is null",
                    topo::ErrorCode::invalid_input
                });
            }

            const auto edges = w->edges_locked();
            for (std::size_t i = 0; i < edges.size(); ++i) {
                if (!edges[i]) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(f) + ":" + which + " wire contains an expired edge at index " + std::to_string(i), topo::ErrorCode::topology_error
                    });
                }

                const topo::HalfEdge* key = edges[i].get();
                if (const auto inserted = set.insert(key).second; !inserted) {
                    return topo::Result<void>(topo::ResultError{
                        ctx(f) + ": half-edge overlap detected while processing " + std::string(which) +
                            " wire (edge id=" + topo::to_string(edges[i]->id()) + ")",
                        topo::ErrorCode::validation_failed
                    });
                }
            }
            return {};

        }
    }

    topo::Result<void> check_face_wires(const std::shared_ptr<topo::Face> &f, const topo::Tolerance &tol,
        const bool requireClosed) {
        if (!f) {
            return topo::Result<void>(topo::ResultError{
                "FaceChecks: face pointer is null", topo::ErrorCode::invalid_input
            });
        }

        const auto outer = f->outer();
        if (!outer) {
            return topo::Result<void>(topo::ResultError{
                ctx(f) + ": outer wire reference is missing or expired", topo::ErrorCode::topology_error
            });
        }

        // Validate outer wire topology.
        if (const auto ro = check_wire(outer, tol, requireClosed, /*verifyOpenEnds=*/true); !ro) {
            return topo::Result<void>(topo::ResultError{
                ctx(f) + ": outer wire validation failed (" + ro.error().message + ")", ro.error().code
            });
        }

        // Validate hole wires and uniqueness by pointer identity.
        std::unordered_set<const topo::Wire*> holeIdentity;
        holeIdentity.reserve(f->hole_count());

        const auto holes = f->holes_locked();
        for (std::size_t i = 0; i < holes.size(); ++i) {
            const auto& h = holes[i];
            if (!h) {
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ": hole wire reference is missing or expired at index " + std::to_string(i),
                    topo::ErrorCode::topology_error
                });
            }

            if (h.get() == outer.get()) {
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ": hole wire references the same object as the outer wire (index " + std::to_string(i) + ")", topo::ErrorCode::validation_failed
                });
            }

            if (const auto inserted = holeIdentity.insert(h.get()).second; !inserted) {
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ": duplicate hole wire detected (wire id=" + topo::to_string(h->id()) + ")"
                    , topo::ErrorCode::validation_failed
                });
            }

            if (const auto rh = check_wire(h, tol, requireClosed, /*verifyOpenEnds=*/true); !rh) {
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ": hole wire validation failed at index " + std::to_string(i) + " (" + rh.error().message + ")", rh.error().code
                });
            }
        }
        return {};
    }

    topo::Result<void> check_face_edge_disjointness(const std::shared_ptr<topo::Face> &f) {
        auto rw = lock_face_wires(f);
        if (!rw) return topo::Result<void>(rw.error());

        // wires[0] is outer, wires[1..] are holes
        const auto wires = std::move(rw.value());
        const auto& outer = wires.front();

        // Strategy:
        // 1) Insert all outer edges into a set.
        // 2) Insert each hole edge into a separate set, checking:
        //    - no overlap with outer
        //    - no overlap with previously inserted holes
        //
        // We use pointer identity (HalfEdge*). This ensures we catch sharing even if
        // ids are reused incorrectly or deserialisation is incomplete.
        std::unordered_set<const topo::HalfEdge*> all;
        all.reserve(128);

        if (auto rOuter = insert_wire_edges(f, outer, all, "outer"); !rOuter) return rOuter;

        for (std::size_t i = 1; i < wires.size(); ++i) {
            const auto& hole = wires[i];
            if (const auto rHole = insert_wire_edges(f, hole, all, "hole"); !rHole) {
                // The helper message already explains the overlap and references edge id.
                // We add which hole index for easier debugging.
                return topo::Result<void>(topo::ResultError{
                    ctx(f) + ": edge overlap detected in hole index " + std::to_string(i - 1) +
                        " (" + rHole.error().message + ")",
                    rHole.error().code
                });
            }
        }
        return {};
    }

    topo::Result<void> check_face(const std::shared_ptr<topo::Face> &f, const topo::Tolerance &tol,
        const bool requireClosed) {
        if (auto r0 = check_face_wires(f, tol, requireClosed); !r0) return r0;

        if (auto r1 = check_face_edge_disjointness(f); !r1) return r1;

        return {};
    }
}
