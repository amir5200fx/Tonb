//
// Created by amir on 2/27/26.
//
/**
 * @file halfedge_geometry.cxx
 * @brief Implements geometry-aware validation routines for topo::HalfEdge.
 *
 * This implementation validates the geometric binding of a topological
 * half-edge against the current cad2d geometry registry. The checks performed
 * here deliberately remain local to a single half-edge and do not attempt to
 * validate full-wire or full-shape consistency.
 *
 * Validation scope:
 * - referenced start and end vertices must exist
 * - referenced curve id must be valid and resolvable in the CurveStore
 * - resolved curve domain must be finite and ordered
 * - stored parameters must be finite and lie within the curve domain
 * - trimmed span must be non-degenerate
 * - stored orientation must agree with parameter ordering
 * - curve evaluations at u0/u1 must match the start/end vertices within the
 *   effective linear tolerance
 *
 * Notes on tolerance handling:
 * - The current topo::Tolerance API provides linear and angular tolerances, but
 *   does not expose a dedicated parametric tolerance. This implementation uses
 *   a small derived parameter epsilon based on the configured linear tolerance,
 *   clamped below by a conservative minimum.
 * - The effective linear tolerance is taken as the maximum of the global
 *   validation tolerance and the local tolerances stored on the half-edge and
 *   its endpoint vertices.
 */
#include <tonb/cad2d/validate/halfedge_geometry.hxx>

#include <tonb/cad2d/geom/curve_ops.hxx>
#include <tonb/cad2d/topo/id.hxx>
#include <tonb/cad2d/topo/vertex.hxx>
#include <tonb/geometry/pnt_2d.hxx>

#include <algorithm>
#include <cmath>
#include <utility>

namespace tonb::cad2d::validate {
    namespace {
        /**
         * @brief Build a stable diagnostic context prefix for a half-edge.
         */
        std::string ctx(const std::shared_ptr<topo::HalfEdge>& e) {
            if (!e) {
                return "HalfEdgeGeometry";
            }
            return "HalfEdgeGeometry (edge id=" + topo::to_string(e->id()) + ")";
        }

        /**
         * @brief Convenience helper for returning a failed result.
         */
        topo::Result<void> fail(std::string msg, const topo::ErrorCode code) {
            return topo::Result<void>(topo::ResultError{std::move(msg), code});
        }

        /**
         * @brief Test whether a scalar is finite.
         */
        bool finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        /**
         * @brief Compute the effective linear tolerance for endpoint agreement.
         *
         * The effective tolerance is the maximum of:
         * - the caller-supplied global validation tolerance,
         * - the half-edge local tolerance,
         * - the local tolerances of the endpoint vertices.
         */
        real effective_linear_tol(const std::shared_ptr<topo::HalfEdge>& e,
                                  const std::shared_ptr<topo::Vertex>& v0,
                                  const std::shared_ptr<topo::Vertex>& v1,
                                  const topo::Tolerance& tol) {
            real out = tol.linear();
            if (e) {
                out = std::max(out, e->tolerance());
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
         * @brief Derive a conservative parameter epsilon from the public
         * tolerance policy.
         *
         * The current tolerance type does not expose a dedicated parametric
         * tolerance value. Until such an API exists, a small positive epsilon is
         * derived from the linear tolerance and clamped to a minimum floor.
         */
        real effective_param_tol(const topo::Tolerance& tol) {
            return std::max(tol.linear(), real(1.0e-14));
        }

        /**
         * @brief Compute Euclidean distance between an evaluated cad2d point and
         * a topology vertex position.
         */
        real dist(const Point& a, const geometry::Pnt2d& b) {
            const real dx = a.x() - b.x();
            const real dy = a.y() - b.y();
            return std::sqrt(dx * dx + dy * dy);
        }
    }

    topo::Result<void> check_halfedge_geometry(const std::shared_ptr<topo::HalfEdge>& e,
                                               const geom::CurveStore& store,
                                               const topo::Tolerance& tol) {
        if (!e) {
            return fail("HalfEdgeGeometry: half-edge pointer is null",
                        topo::ErrorCode::invalid_input);
        }

        const auto v0 = e->start();
        const auto v1 = e->end();
        if (!v0) {
            return fail(ctx(e) + ": start vertex reference is missing or expired",
                        topo::ErrorCode::topology_error);
        }
        if (!v1) {
            return fail(ctx(e) + ": end vertex reference is missing or expired",
                        topo::ErrorCode::topology_error);
        }

        const auto curve_id = e->curve_id();
        if (curve_id == 0) {
            return fail(ctx(e) + ": curve_id is zero and therefore invalid",
                        topo::ErrorCode::geometry_error);
        }

        if (!store.contains(curve_id)) {
            return fail(ctx(e) + ": referenced curve id=" + topo::to_string(curve_id) +
                            " is not present in CurveStore",
                        topo::ErrorCode::geometry_error);
        }

        const auto& curve = store.get(curve_id);
        const auto [umin, umax] = geom::domain(curve);
        if (!finite(umin) || !finite(umax) || umax < umin) {
            return fail(ctx(e) + ": resolved curve reports an invalid parameter domain",
                        topo::ErrorCode::geometry_error);
        }

        const real u0 = e->u0();
        const real u1 = e->u1();
        if (!finite(u0) || !finite(u1)) {
            return fail(ctx(e) + ": stored parameters are not finite",
                        topo::ErrorCode::geometry_error);
        }

        const real ptol = effective_param_tol(tol);
        if (u0 < umin - ptol || u0 > umax + ptol || u1 < umin - ptol || u1 > umax + ptol) {
            return fail(ctx(e) + ": stored parameters lie outside the curve domain",
                        topo::ErrorCode::geometry_error);
        }

        if (std::abs(u1 - u0) <= ptol) {
            return fail(ctx(e) + ": parametric span is degenerate",
                        topo::ErrorCode::degenerate);
        }

        if (e->orientation() == topo::Orientation::forward && !(u1 > u0 + ptol)) {
            return fail(ctx(e) + ": forward-oriented half-edge must satisfy u1 > u0",
                        topo::ErrorCode::geometry_error);
        }
        if (e->orientation() == topo::Orientation::reversed && !(u0 > u1 + ptol)) {
            return fail(ctx(e) + ": reversed-oriented half-edge must satisfy u0 > u1",
                        topo::ErrorCode::geometry_error);
        }

        const auto p0 = geom::value(curve, u0);
        const auto p1 = geom::value(curve, u1);
        const real ltol = effective_linear_tol(e, v0, v1, tol);

        const real d0 = dist(p0, v0->position());
        if (d0 > ltol) {
            return fail(ctx(e) +
                            ": curve evaluation at u0 does not match the start vertex within tolerance",
                        topo::ErrorCode::geometry_error);
        }

        const real d1 = dist(p1, v1->position());
        if (d1 > ltol) {
            return fail(ctx(e) +
                            ": curve evaluation at u1 does not match the end vertex within tolerance",
                        topo::ErrorCode::geometry_error);
        }

        return {};
    }
}
