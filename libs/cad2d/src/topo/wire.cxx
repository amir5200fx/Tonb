//
// Created by amir on 1/21/26.
//
#include <tonb/cad2d/topo/wire.hxx>

#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/vertex.hxx>

namespace tonb::cad2d::topo {
    std::vector<std::shared_ptr<HalfEdge>> Wire::edges_locked() const {
        std::vector<std::shared_ptr<HalfEdge>> out;
        out.reserve(boundary_.size());
        for (const auto& w: boundary_) out.push_back(w.lock());
        return out;
    }

    Result<void> Wire::check_closed(const Tolerance &tol) const {
        // Closed implies continuous plus last connects to first.
        const auto cont = check_continuous(tol);
        if (!cont) return cont;

        if (boundary_.empty()) {
            return {}; // treat empty as trivially closed if desired
        }

        const auto first = boundary_.front().lock();
        const auto last = boundary_.back().lock();
        if (!first || !last) {
            return Result<void>(ResultError{
                "Wire closed check failed: first or last edge reference is expired",
                ErrorCode::topology_error
            });
        }

        const auto first_start = first->start();
        const auto last_end = last->end();
        if (!first_start || !last_end) {
            return Result<void>(ResultError{
                "Wire closed check failed: first or last edge has expired vertex references",
                ErrorCode::topology_error
            });
        }

        const auto& p0 = first_start->position();
        const auto& p1 = last_end->position();
        if (!tol.equal(p0.x(), p0.y(), p1.x(), p1.y())) {
            return Result<void>(ResultError{
                "Wire closed check failed: last end vertex does not match first start vertex within tolerance",
                ErrorCode::validation_failed
            });
        }
        return {};
    }

    Result<void> Wire::check_continuous(const Tolerance &tol) const {
        if (boundary_.empty()) {
            return {}; // emtpy chain is trivially continuous
        }

        for (std::size_t i = 0; i + 1 < boundary_.size(); ++i) {
            const auto a = boundary_[i].lock();
            const auto b = boundary_[i + 1].lock();
            if (!a || !b) {
                return Result<void>(ResultError{
                    "Wire continuity check failed: and edge reference is expired",
                    ErrorCode::topology_error
                });
            }

            const auto a_end = a->end();
            const auto b_start = b->start();
            if (!a_end || !b_start) {
                return Result<void>(ResultError{
                    "Wire continuity check failed: an edge has expired vertex references",
                    ErrorCode::topology_error
                });
            }

            const auto pa = a_end->position();
            const auto pb = b_start->position();
            if (!tol.equal(pa.x(), pa.y(), pb.x(), pb.y())) {
                return Result<void>(ResultError{
                    "Wire continuity check failed: end and start vertices do not match withing tolerance",
                    ErrorCode::validation_failed
                });
            }
        }
        return {};
    }
}
