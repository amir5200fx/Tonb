//
// Created by amir on 5/7/26.
//
/**
 * @file wire_length.cxx
 * @brief Implements geometric length utilities for cad2d wires.
 *
 * This implementation computes wire length as the sum of arc lengths of all
 * boundary half-edge spans. Each span is measured against its referenced curve
 * using the public adaptive arc-length integrator provided by tonb::numerics.
 */
#include <tonb/cad2d/algo/wire_length.hxx>

#include <tonb/cad2d/topo/wire.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/geom/curve_store.hxx>
#include <tonb/cad2d/geom/curve_ops.hxx>
#include <tonb/cad2d/point.hxx>
#include <tonb/numerics/arc_length_integration.hxx>

#include <sstream>
#include <array>
#include <cmath>

namespace tonb::cad2d::algo {
    namespace {

        std::string ctx(const std::shared_ptr<topo::Wire>& wire) {
            if (!wire) {
                return "WireLength";
            }
            return "WireLength (wire id=" + std::to_string(wire->id()) + ")";
        }

        bool finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        topo::Result<real> edge_length(const std::shared_ptr<topo::HalfEdge>& edge,
                                       const geom::CurveStore& curves,
                                       const WireLengthOptions& options) {
            if (!edge) {
                return topo::Result<real>(topo::ResultError{
                    "WireLength: boundary contains a null or expired half-edge",
                    topo::ErrorCode::topology_error
                });
            }

            const auto curve_id = edge->curve_id();
            if (curve_id == 0) {
                return topo::Result<real>(topo::ResultError{
                    "WireLength: half-edge stores invalid curve id 0",
                    topo::ErrorCode::geometry_error
                });
            }

            if (!curves.contains(curve_id)) {
                return topo::Result<real>(topo::ResultError{
                    "WireLength: referenced curve id is not present in CurveStore",
                    topo::ErrorCode::geometry_error
                });
            }

            const auto& curve = curves.get(curve_id);
            const auto dom = geom::domain(curve);
            if (!finite(dom.first) || !finite(dom.second)) {
                return topo::Result<real>(topo::ResultError{
                    "WireLength: curve domain is not finite; unbounded curves are not supported",
                    topo::ErrorCode::geometry_error
                });
            }

            const real u0 = edge->u0();
            const real u1 = edge->u1();
            if (!finite(u0) || !finite(u1)) {
                return topo::Result<real>(topo::ResultError{
                    "WireLength: half-edge parameters are not finite",
                    topo::ErrorCode::geometry_error
                });
            }

            auto eval = [&curve](const real u) -> std::array<real, 2> {
                const auto p = geom::value(curve, u);
                return {p.x(), p.y()};
            };

            const auto r = tonb::numerics::integrate_arc_length(eval, u0, u1, options.integration);
            if (!r.converged) {
                std::ostringstream oss;
                oss << "WireLength: arc-length integration failed for edge id=" << edge->id()
                    << " (reason=" << static_cast<int>(r.reason)
                    << ", evals=" << r.evals
                    << ", error_est=" << r.error_est
                    << ")";
                return topo::Result<real>(topo::ResultError{
                    oss.str(),
                    topo::ErrorCode::validation_failed
                });
            }

            return topo::ok(static_cast<real>(r.value));
        }
    }

    topo::Result<real> wire_length(const std::shared_ptr<topo::Wire>& wire,
                                   const geom::CurveStore& curves,
                                   const WireLengthOptions& options) {
        if (!wire) {
            return topo::Result<real>(topo::ResultError{
                "WireLength: wire pointer is null",
                topo::ErrorCode::invalid_input
            });
        }

        if (wire->empty()) {
            return topo::ok(real(0.0));
        }

        real sum = 0.0;
        const auto edges = wire->edges_locked();
        for (std::size_t i = 0; i < edges.size(); ++i) {
            const auto ri = edge_length(edges[i], curves, options);
            if (!ri) {
                return topo::Result<real>(topo::ResultError{
                    ctx(wire) + ": failed on boundary edge index " + std::to_string(i) +
                    " (" + ri.error().message + ")",
                    ri.error().code
                });
            }
            sum += ri.value();
        }

        return topo::ok(static_cast<real>(sum));
    }
}
