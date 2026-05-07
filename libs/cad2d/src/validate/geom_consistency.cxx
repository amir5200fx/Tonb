//
// Created by amir on 1/25/26.
//
/**
 * @file geom_consistency.cxx
 * @brief Implements report-oriented batch geometry validation for cad2d shapes.
 *
 * This implementation is intentionally aligned with the currently exposed
 * geom_consistency.hxx and topo::Tolerance API.
 *
 * Important note
 * --------------
 * The current public header exposes a minimal ICurveEval2d interface with only
 * point evaluation, and the current GeomIssueCode enumeration does not include
 * domain- or orientation-specific diagnostics. Consequently, this source file
 * performs the subset of consistency checks that can be expressed against that
 * public contract:
 *
 * - missing vertex references
 * - missing curve id
 * - non-finite stored parameters
 * - degenerate parametric span
 * - curve evaluation failure at endpoint parameters
 * - endpoint-to-vertex positional mismatch
 * - optional twin endpoint reversal mismatch
 * - optional shared-vertex agreement mismatch
 *
 * If domain and orientation checks are desired here as well, the public header
 * must first be extended accordingly.
 */
#include <tonb/cad2d/validate/geom_consistency.hxx>

#include <tonb/cad2d/topo/shape.hxx>
#include <tonb/cad2d/topo/halfedge.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/cad2d/topo/id.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <algorithm>
#include <cmath>
#include <optional>
#include <unordered_map>
#include <vector>

namespace tonb::cad2d::validate {
    namespace {

        /**
         * @brief Return true when a scalar is finite.
         */
        TNB_NODISCARD bool finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        /**
         * @brief Compute the effective linear tolerance used for endpoint checks.
         *
         * The effective tolerance is the maximum of:
         * - the configured override linear tolerance,
         * - the half-edge local tolerance,
         * - the start vertex local tolerance,
         * - the end vertex local tolerance.
         *
         * This mirrors the practical intent of the validator: do not use a
         * tolerance smaller than any participating entity has explicitly asked
         * for.
         */
        TNB_NODISCARD real max_linear_tol(const std::shared_ptr<topo::HalfEdge>& edge,
                                          const std::shared_ptr<topo::Vertex>& v0,
                                          const std::shared_ptr<topo::Vertex>& v1,
                                          const topo::Tolerance& tol) noexcept {
            real out = tol.linear();
            if (edge) {
                out = std::max(out, edge->tolerance());
            }
            if (v0) {
                out = std::max(out, v0->tolerance());
            }
            if (v1) {
                out = std::max(out, v1->tolerance());
            }
            return out;
        }

        /**
         * @brief Distance helper between cad2d point abstractions.
         */
        TNB_NODISCARD real dist(const Point& a, const geometry::Pnt2d& b) noexcept {
            return a.distance({b.x(), b.y()});
        }

        /**
         * @brief Resolve the tolerance object used by this validator.
         *
         * The current public Tolerance type carries linear and angular fields
         * only. This batch validator uses the linear part for geometric distance
         * checks; parametric degeneracy uses cfg.param_eps directly.
         */
        TNB_NODISCARD topo::Tolerance resolved_tol(const GeomValidationConfig& cfg) noexcept {
            topo::Tolerance t{};
            if (cfg.tol_override.linear() > 0.0) {
                t.set_linear(cfg.tol_override.linear());
            }
            if (cfg.tol_override.angular() > 0.0) {
                t.set_angular(cfg.tol_override.angular());
            }
            return t;
        }

        /**
         * @brief Produce a compact textual edge context for diagnostics.
         */
        TNB_NODISCARD std::string edge_ctx(const std::shared_ptr<topo::HalfEdge>& edge) {
            return edge ? ("edge id=" + topo::to_string(edge->id()))
                        : std::string{"edge id=<null>"};
        }

        /**
         * @brief Evaluate the point on an incident edge corresponding to a given shared vertex.
         *
         * @param edge Incident half-edge.
         * @param vertex_id Shared vertex identifier.
         * @param curves Curve evaluator.
         * @return Endpoint point associated with the supplied vertex, or std::nullopt if
         *         the edge does not reference the vertex or evaluation fails.
         */
        TNB_NODISCARD std::optional<Point>
        endpoint_point_for_vertex(const std::shared_ptr<topo::HalfEdge>& edge,
                                  const topo::Id vertex_id,
                                  const ICurveEval2d& curves) {
            if (!edge) {
                return std::nullopt;
            }

            if (const auto start = edge->start(); start && start->id() == vertex_id) {
                return curves.eval(edge->curve_id(), edge->u0());
            }
            if (const auto end = edge->end(); end && end->id() == vertex_id) {
                return curves.eval(edge->curve_id(), edge->u1());
            }
            return std::nullopt;
        }
    }

    GeomReport geom_consistency(const topo::Shape& shape,
                                const ICurveEval2d& curves,
                                const GeomValidationConfig& cfg) {
        GeomReport report;
        const topo::Tolerance tol = resolved_tol(cfg);
        const auto edges = shape.halfedges();

        std::unordered_map<topo::Id, std::vector<std::shared_ptr<topo::HalfEdge>>> incident_edges;
        incident_edges.reserve(edges.size());

        for (const auto& edge : edges) {
            if (!edge) {
                continue;
            }

            const auto v0 = edge->start();
            const auto v1 = edge->end();

            if (!v0) {
                report.add({GeomIssueCode::missing_start_vertex,
                            edge->id(),
                            0,
                            0.0,
                            0.0,
                            edge_ctx(edge) + ": start vertex reference is missing or expired"});
                continue;
            }
            if (!v1) {
                report.add({GeomIssueCode::missing_end_vertex,
                            edge->id(),
                            0,
                            0.0,
                            0.0,
                            edge_ctx(edge) + ": end vertex reference is missing or expired"});
                continue;
            }

            incident_edges[v0->id()].push_back(edge);
            incident_edges[v1->id()].push_back(edge);

            if (edge->curve_id() == 0) {
                report.add({GeomIssueCode::curve_missing,
                            edge->id(),
                            0,
                            0.0,
                            0.0,
                            edge_ctx(edge) + ": curve_id is zero"});
                continue;
            }

            const real u0 = edge->u0();
            const real u1 = edge->u1();
            if (!finite(u0) || !finite(u1)) {
                report.add({GeomIssueCode::param_not_finite,
                            edge->id(),
                            0,
                            0.0,
                            0.0,
                            edge_ctx(edge) + ": stored parameters are not finite"});
                continue;
            }

            const real du = std::abs(u1 - u0);
            if (du <= cfg.param_eps) {
                report.add({GeomIssueCode::param_degenerate,
                            edge->id(),
                            0,
                            du,
                            cfg.param_eps,
                            edge_ctx(edge) + ": parametric span is degenerate"});
                continue;
            }

            const auto p0 = curves.eval(edge->curve_id(), u0);
            const auto p1 = curves.eval(edge->curve_id(), u1);
            if (!p0 || !p1) {
                report.add({GeomIssueCode::curve_eval_failed,
                            edge->id(),
                            0,
                            0.0,
                            0.0,
                            edge_ctx(edge) + ": curve evaluation failed at one or both edge parameters"});
                continue;
            }

            const real ltol = max_linear_tol(edge, v0, v1, tol);

            const real d0 = dist(*p0, v0->position());
            if (d0 > ltol) {
                report.add({GeomIssueCode::endpoint_mismatch_start,
                            edge->id(),
                            v0->id(),
                            d0,
                            ltol,
                            edge_ctx(edge) + ": start vertex does not match evaluated curve start"});
            }

            const real d1 = dist(*p1, v1->position());
            if (d1 > ltol) {
                report.add({GeomIssueCode::endpoint_mismatch_end,
                            edge->id(),
                            v1->id(),
                            d1,
                            ltol,
                            edge_ctx(edge) + ": end vertex does not match evaluated curve end"});
            }

            if (cfg.check_twin) {
                if (const auto twin = edge->twin()) {
                    const auto tp0 = curves.eval(twin->curve_id(), twin->u0());
                    const auto tp1 = curves.eval(twin->curve_id(), twin->u1());
                    if (tp0 && tp1) {
                        const real dt0 = p0->distance(*tp1);
                        const real dt1 = p1->distance(*tp0);
                        if (dt0 > ltol || dt1 > ltol) {
                            report.add({GeomIssueCode::twin_endpoint_mismatch,
                                        edge->id(),
                                        0,
                                        std::max(dt0, dt1),
                                        ltol,
                                        edge_ctx(edge) + ": twin does not reverse the same geometric segment"});
                        }
                    }
                }
            }
        }

        if (cfg.check_shared_vertex) {
            for (const auto& [vertex_id, edges_at_vertex] : incident_edges) {
                if (edges_at_vertex.size() < 2) {
                    continue;
                }

                const auto vertex = shape.vertex(vertex_id);
                if (!vertex) {
                    continue;
                }

                for (const auto& edge : edges_at_vertex) {
                    if (!edge || edge->curve_id() == 0) {
                        continue;
                    }

                    const auto point = endpoint_point_for_vertex(edge, vertex_id, curves);
                    if (!point) {
                        continue;
                    }

                    const real ltol = std::max(tol.linear(), vertex->tolerance());
                    const real d = dist(*point, vertex->position());
                    if (d > ltol) {
                        report.add({GeomIssueCode::shared_vertex_mismatch,
                                    edge->id(),
                                    vertex_id,
                                    d,
                                    ltol,
                                    edge_ctx(edge) + ": incident geometry does not agree with shared vertex position"});
                    }
                }
            }
        }

        return report;
    }
}
