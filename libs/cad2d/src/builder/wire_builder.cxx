//
// Created by amir on 1/22/26.
//
#include <tonb/cad2d/builder/wire_builder.hxx>

#include <tonb/cad2d/topo/wire.hxx>

#include "tonb/cad2d/topo/halfedge.hxx"

namespace tonb::cad2d::build {
    topo::Result<std::shared_ptr<topo::Wire>> WireBuilder::create(
        const std::vector<std::shared_ptr<topo::HalfEdge>> &edges, bool requireClosed, bool setNextPrev) const {
        if (edges.empty()) return topo::Result<std::shared_ptr<topo::Wire>>(topo::ResultError{
            "WireBuilder: edge list is empty", topo::ErrorCode::invalid_input
        });

        for (const auto& e : edges) {
            if (!e) return topo::Result<std::shared_ptr<topo::Wire>>(topo::ResultError{
                "WireBuilder: an edge in the list is null", topo::ErrorCode::invalid_input
            });
        }

        auto w = shape_.make_wire();
        if (!w) return topo::Result<std::shared_ptr<topo::Wire>>(topo::ResultError{
            "WireBuilder: failed to allocate wire", topo::ErrorCode::internal
        });

        std::vector<std::weak_ptr<topo::HalfEdge>> boundary;
        boundary.reserve(edges.size());
        for (const auto& e : edges) boundary.emplace_back(e);

        w->set_boundary(std::move(boundary));

        if (const auto r = w->check_continuous(tol_); !r) {
            return topo::Result<std::shared_ptr<topo::Wire>>(topo::ResultError{
                "WireBuilder: continuity check failed (" + r.error().message + ")", r.error().code
            });
        }

        if (requireClosed) {
            if (const auto rc = w->check_closed(tol_); !rc) {
                return topo::Result<std::shared_ptr<topo::Wire>>(topo::ResultError{
                    "WireBuilder: closure check failed (" + rc.error().message + ")", rc.error().code
                });
            }
        }

        if (setNextPrev) {
            const std::size_t n = edges.size();
            for (std::size_t i = 0; i < n; ++i) {
                const auto& curr = edges[i];
                const auto& next = edges[(i + 1) % n];
                const auto& prev = edges[(i + n - 1) % n];
                curr->set_next(next);
                curr->set_prev(prev);
            }
            if (!requireClosed) {
                // For open chains, do not wrap around.
                edges.front()->set_prev(std::weak_ptr<topo::HalfEdge>{});
                edges.back()->set_next(std::weak_ptr<topo::HalfEdge>{});
            }
        }
        return topo::ok(std::move(w));
    }
}
