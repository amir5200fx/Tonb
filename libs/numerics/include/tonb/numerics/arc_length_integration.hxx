//
// Created by amir on 5/7/26.
//
/**
 * @file arc_length_integration.hxx
 * @brief Public adaptive arc-length integration utilities for parametric planar curves.
 *
 * This header provides a robust and deterministic arc-length estimator for
 * planar parametric curves when only point evaluation is available.
 *
 * Design intent
 * -------------
 * The existing scalar integration utilities in @ref integration.hxx integrate
 * scalar-valued functions f(u). Arc length, however, is naturally expressed as:
 *
 *     L = integral_a^b ||C'(u)|| du
 *
 * which requires either:
 * - direct derivative access, or
 * - a reliable geometric refinement strategy when only point evaluation is
 *   available.
 *
 * This module implements the second option as a public numerics API using
 * adaptive chord refinement:
 *
 * - the curve is sampled at interval endpoints and midpoint,
 * - the coarse estimate is the endpoint chord length,
 * - the refined estimate is the sum of the two midpoint chords,
 * - recursion continues until the local error estimate satisfies the requested
 *   tolerance, or deterministic work limits are reached.
 *
 * The algorithm is robust, deterministic, and well suited for bounded curve
 * spans used by higher-level CAD utilities such as cad2d wire length.
 *
 * Input convention
 * ----------------
 * The caller supplies a point-evaluation callable:
 *
 *     P = eval(u)
 *
 * where P is represented as std::array<real, 2>.
 *
 * This keeps numerics independent of any particular geometry or CAD module.
 */
#pragma once
#ifndef TONB_NUMERICS_ARC_LENGTH_INTEGRATION_HXX
#define TONB_NUMERICS_ARC_LENGTH_INTEGRATION_HXX

#include <tonb/base/precision.hxx>
#include <tonb/numerics/integration.hxx>

#include <array>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>

namespace tonb::numerics {

    /**
     * @brief Runtime controls for adaptive arc-length estimation.
     *
     * Convergence is accepted when the estimated local refinement error is less
     * than or equal to:
     *
     *     max(atol, rtol * |length|)
     *
     * Deterministic work caps are enforced through @ref max_depth and
     * @ref max_evals.
     */
    struct ArcLengthOptions {
        /** Absolute tolerance for arc length. */
        real atol = 1.0e-8;
        /** Relative tolerance for arc length. */
        real rtol = 1.0e-8;
        /** Maximum recursive subdivision depth. */
        int max_depth = 20;
        /** Maximum number of point evaluations. */
        int max_evals = 1 << 16;
        /** Minimum accepted depth before convergence is allowed. */
        int min_depth = 0;
    };

    /**
     * @brief Result of adaptive arc-length estimation.
     */
    struct ArcLengthResult {
        /** Estimated arc length. */
        real value = std::numeric_limits<real>::quiet_NaN();
        /** Accumulated error estimate. */
        real error_est = std::numeric_limits<real>::quiet_NaN();
        /** Number of point evaluations performed. */
        int evals = 0;
        /** Maximum recursion depth reached. */
        int depth_used = 0;
        /** True if the requested tolerance was satisfied. */
        bool converged = false;
        /** Termination reason. */
        IntegrateStop reason = IntegrateStop::HitMaxEvals;
    };

    namespace detail {

        inline bool arc_length_finite(const real x) noexcept {
            return std::isfinite(x) != 0;
        }

        inline bool arc_length_finite(const std::array<real, 2>& p) noexcept {
            return arc_length_finite(p[0]) && arc_length_finite(p[1]);
        }

        inline real arc_length_goal(const ArcLengthOptions& opt, const real approx) {
            return std::max(opt.atol, opt.rtol * std::abs(approx));
        }

        inline real chord_length(const std::array<real, 2>& a,
                                 const std::array<real, 2>& b) noexcept {
            const real dx = b[0] - a[0];
            const real dy = b[1] - a[1];
            return std::sqrt(dx * dx + dy * dy);
        }
    }

    /**
     * @brief Estimate the arc length of a planar parametric curve over [a, b].
     *
     * @tparam Eval Callable returning std::array<real, 2> for a parameter u.
     * @param eval Point-evaluation callable.
     * @param a Lower parameter bound.
     * @param b Upper parameter bound.
     * @param opt Adaptive refinement options.
     * @return Arc-length estimate and convergence metadata.
     *
     * Robustness
     * ----------
     * - If a == b, the result is zero and converged.
     * - If the evaluator returns a non-finite point, the run stops with
     *   IntegrateStop::DomainError.
     * - If deterministic work limits are reached before convergence, the result
     *   is returned with converged=false and the appropriate stop reason.
     */
    template<class Eval>
    ArcLengthResult integrate_arc_length(Eval&& eval, const real a_in, const real b_in, ArcLengthOptions opt = {}) {
        ArcLengthResult out{};

        real a = a_in;
        real b = b_in;
        if (b < a) {
            std::swap(a, b);
        }

        if (!(b > a)) {
            out.value = 0.0;
            out.error_est = 0.0;
            out.converged = true;
            out.reason = IntegrateStop::Converged;
            return out;
        }

        struct Node {
            real a = 0.0;
            real b = 0.0;
            std::array<real, 2> pa{};
            std::array<real, 2> pm{};
            std::array<real, 2> pb{};
            real coarse = 0.0;
            real tol = 0.0;
            int depth = 0;
        };

        Node stack[64];
        int sp = 0;
        const int maxD = std::min(opt.max_depth, static_cast<int>(std::size(stack)) - 2);

        const real m0 = std::midpoint(a, b);
        const auto pa = eval(a);
        const auto pm = eval(m0);
        const auto pb = eval(b);
        out.evals = 3;

        if (!detail::arc_length_finite(pa) ||
            !detail::arc_length_finite(pm) ||
            !detail::arc_length_finite(pb)) {
            out.reason = IntegrateStop::DomainError;
            return out;
        }

        const real coarse0 = detail::chord_length(pa, pb);
        stack[sp++] = Node{a, b, pa, pm, pb, coarse0, detail::arc_length_goal(opt, coarse0), 0};

        real app_sum = 0.0;
        real err_sum = 0.0;
        int depth_hit = 0;
        bool hit_max_depth = false;

        while (sp > 0) {
            Node n = stack[--sp];
            depth_hit = std::max(depth_hit, n.depth);

            const real mid = std::midpoint(n.a, n.b);
            const real left_mid = std::midpoint(n.a, mid);
            const real right_mid = std::midpoint(mid, n.b);

            const auto plm = eval(left_mid);
            const auto prm = eval(right_mid);
            out.evals += 2;

            if (out.evals > opt.max_evals) {
                out.value = app_sum;
                out.error_est = err_sum;
                out.depth_used = depth_hit;
                out.reason = IntegrateStop::HitMaxEvals;
                return out;
            }

            if (!detail::arc_length_finite(plm) || !detail::arc_length_finite(prm)) {
                out.value = app_sum;
                out.error_est = err_sum;
                out.depth_used = depth_hit;
                out.reason = IntegrateStop::DomainError;
                return out;
            }

            const real left_refined = detail::chord_length(n.pa, n.pm);
            const real right_refined = detail::chord_length(n.pm, n.pb);
            const real refined = left_refined + right_refined;
            const real err = std::abs(refined - n.coarse);

            const bool depth_ok = (n.depth >= opt.min_depth);
            if (err <= n.tol && depth_ok) {
                app_sum += refined;
                err_sum += err;
                continue;
            }

            if (n.depth >= maxD) {
                app_sum += refined;
                err_sum += err;
                hit_max_depth = true;
                continue;
            }

            const real child_tol = 0.5 * n.tol;
            stack[sp++] = Node{mid, n.b, n.pm, prm, n.pb, right_refined, child_tol, n.depth + 1};
            stack[sp++] = Node{n.a, mid, n.pa, plm, n.pm, left_refined, child_tol, n.depth + 1};
        }

        out.value = app_sum;
        out.error_est = err_sum;
        out.depth_used = depth_hit;
        out.converged = (out.error_est <= detail::arc_length_goal(opt, out.value)) && !hit_max_depth;
        out.reason = out.converged ? IntegrateStop::Converged :
                     (hit_max_depth ? IntegrateStop::HitMaxDepth : IntegrateStop::HitMaxEvals);
        return out;
    }
}

#endif // TONB_NUMERICS_ARC_LENGTH_INTEGRATION_HXX
