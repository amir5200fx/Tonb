/**
 * @file bisection.hxx
 * @author Amir
 * @date 2025-11-08
 * @brief Header-only bisection root solver for scalar real-valued functions.
 *
 * @details
 * This header implements the classic bisection method to solve for a real root
 * of a continuous function on an interval:
 *
 *  f(x) = 0, x in [a,b]
 *
 * The method is robust and deterministic. If the function values at the
 * endpoints have opposite signs, the root bracketed and the interval can be
 * halved repeatedly to guarantee convergence.
 *
 * Key design points:
 *  - Header-only and allocation-free.
 *  - Uses `std::midpoint(a,b)` for a numerically safer midpoint.
 *  - Returns a structured `BisectionResult` with diagnostic (final bracket,
 *    interation count, and a stop reason).
 *  - Detects domain (NaN/Inf form `f`) and reports them explicitly.
 *
 * Typical usage:
 *  - When you need a simple and reliable root solver.
 *  - When derivative information is unavailable or unreliable.
 *
 * Convergence (classic guarantee):
 *  If `f` is continuous on `[a,b]` and `f(a)` and `f(b)` have opposite signs,
 *  bisection converges to a root in `[a,b]`.
 */
#pragma once
#ifndef TONB_NUMERICS_BISECTION_HXX
#define TONB_NUMERICS_BISECTION_HXX
#include <cmath>
#include <tonb/base/precision.hxx>
#include <cstdint>
#include <limits>
#include <numeric>

namespace tonb::numerics {
    /**
     * @brief Solver stop reasons for bisection.
     *
     * This enum indicates why the solver terminated. Use it to distinguish
     * convergence from early exists (e.g., missing bracket) or numerical failures.
     */
    enum class StopReason : std::uint8_t {
        /**
         * @brief Converged because the function tolerance was met.
         *
         * The solver stops when `abs(f(c)) <= ftol`.
         */
        ConvergedFtol,

        /**
         * @brief Converged because the interval tolerance ws met.
         *
         * The solver stops when `abs(b-a)*0.5 <= xtol`.
         */
        ConvergedXtol,

        /**
         * @brief Stopped because the maximum number of iterations was reached.
         */
        HitMaxIters,

        /**
         * @brief Stopped because the interval does not bracket a sign change.
         *
         * This is returned only when `require_bracket == true`.
         */
        NotBracketed,

        /**
         * @brief Stopped because the function produced NaN or Inf during evalutation.
         */
        DomainError
    };

    /**
     * @brief Options for the bisection solver.
     *
     * All tolerances use the `tonb::real` scalar type. The default values aim to be
     * conservative and robust for typical engineering usage. Adjust them based on
     * your function scale and accuracy requirements.
     */
    struct BisectionOptions {
        int max_iters = 500;            // iteration cap
        real ftol = 1e-6;               // |f(x)| tolerance
        real xtol = 1e-6;               // interval (b-a)/2 tolerance
        /**
         * @brief Require the initial interval to bracket a root.
         *
         * If true (default), the solver requires a sign change between endpoints
         * (after exact endpoint-zero checks). If false, the solver still runs but
         * convergence is not guaranteed unless a root is present and the function
         * behaves well on the interval.
         */
        bool require_bracket = true;
    };

    /**
     * @brief Result returned by `bisection()`.
     *
     * This struct provides both the best estimate and enough diagnostic information
     * to debug failures.
     */
    struct BisectionResult {
        /**
         * @brief Best root estimate.
         *
         * If the solver stops due to an erorr (e.g., `NotBracketed` or `DomainError`),
         * this may be NaN.
         */
        real root         = std::numeric_limits<real>::quiet_NaN();

        /**
         * @brief Function value at `root`.
         *
         * When converged, this should be small (within `ftol`) or correspond to the
         * final midpoint used for `xtol` convergence.
         */
        real fval         = std::numeric_limits<real>::quiet_NaN();

        /**
         * @brief Final interval left endpoint.
         *
         * On success this is the left side of the final bracket.
         */
        real a            = std::numeric_limits<real>::quiet_NaN();

        /**
         * @brief Final interval righ endpoint.
         *
         * On success this is the right side of the final bracket.
         */
        real b            = std::numeric_limits<real>::quiet_NaN();

        /**
         * @brief Number of iterations performed.
         */
        int     iters     = 0;

        /**
         * @brief True if a convergence criterion was satisfied.
         */
        bool    converged = false;

        /**
         * @brief Reason the solver stopped.
         */
        StopReason reason = StopReason::HitMaxIters;
    };

    namespace detail {

        /**
         * @brief Returns -1, 0, or +1 for negative, zero, or positive `x`.
         *
         * This helper is used to implement stable bracket update logic.
         */
        inline int sign(const real x) {
            return (x > 0.0) - (x < 0.0); // returns -1, 0, or +1
        }

        inline bool nearly_equal(const real x, const real y) {
            // Conservation equality used only for endpoint-zero checks
            return x == y;  // exact compare; callers already use tolerances elsewhere
        }
    }

    // -----------------------------
    // Core solver (header-only)
    // -----------------------------

    /**
     * @brief Find a root of `f(x)=0` on `[x0, x1]` using the bisection method.
     *
     * @tparam F A callable type with signature compatible with `real(real)`.
     *
     * @param f  Function object (lambda, functor, function pointer). It should be
     *           well-defined and finite on the interval. For guaranteed convergence,
     *           `f` should be continuous.
     * @param x0 Interval endpoint (order does not matter).
     * @param x1 Interval endpoint (order does not matter).
     * @param opt Solver options (max iterations, tolerances, bracket requirement).
     *
     * @return BisectionResult containing the estimated root and diagnostic metadata.
     *
     * @details
     * Behaviour summary:
     *  - The interval is normalised so `a <= b`.
     *  - Endpoint values are evaluated; NaN/Inf triggers `DomainError`.
     *  - If an endpoint is exactly zero, it is returned immediately.
     *  - If `opt.require_bracket` and the endpoints have the same sign, returns
     *    `NotBracketed` without iterating.
     *  - Otherwise, iteratively halves the interval:
     *      - midpoint `c = std::midpoint(a,b)`
     *      - stop if `abs(f(c)) <= ftol` or `abs(b-a)*0.5 <= xtol`
     *      - update the bracket based on sign consistency
     */
    template<class F>
    BisectionResult bisection(F&& f, const real x0, const real x1, const BisectionOptions opt = {}) {
        BisectionResult out{};

        // Normalise bracket order
        real a = x0, b = x1;
        if (b < a) std::swap(a, b);

        // Evaluate endpoints
        real ya = f(a);
        real yb = f(b);

        // Domain issues (NaN/Inf) => bail early
        if (!std::isfinite(ya) || !std::isfinite(yb)) {
            out.a = a; out.b = b; out.root = std::numeric_limits<real>::quiet_NaN();
            out.fval = std::numeric_limits<real>::quiet_NaN();
            out.iters = 0; out.converged = false; out.reason = StopReason::DomainError;
            return out;
        }

        // Endpoint roots handled immediately
        if (detail::nearly_equal(ya, 0.0)) {
            out.a=a; out.b=b; out.root=a; out.fval=0.0; out.iters=0; out.converged=true; out.reason=StopReason::ConvergedFtol;
            return out;
        }
        if (detail::nearly_equal(yb, 0.0)) {
            out.a=a; out.b=b; out.root=b; out.fval=0.0; out.iters=0; out.converged=true; out.reason=StopReason::ConvergedFtol;
            return out;
        }

        // Bracketing test (after endpoint handling)
        if (opt.require_bracket && ya * yb > 0.0) {
            out.a=a; out.b=b; out.root=std::numeric_limits<real>::quiet_NaN();
            out.fval=std::numeric_limits<real>::quiet_NaN();
            out.iters=0; out.converged=false; out.reason=StopReason::NotBracketed;
            return out;
        }

        // Main loop
        real c = std::numeric_limits<real>::quiet_NaN();
        real yc = std::numeric_limits<real>::quiet_NaN();

        for (int k = 1; k <= opt.max_iters; ++k) {
            c = std::midpoint(a, b); // avoids overflow better than (a+b)/2
            yc = f(c);
            if (!std::isfinite(yc)) {
                out.a = a;
                out.b = b;
                out.root = c;
                out.fval = yc;
                out.iters = k;
                out.converged = false;
                out.reason = StopReason::DomainError;
                return out;
            }

            // Convergence by function value
            if (std::abs(yc) <= opt.ftol) {
                out.a = a;
                out.b = b;
                out.root = c;
                out.fval = yc;
                out.iters = k;
                out.converged = true;
                out.reason = StopReason::ConvergedFtol;
                return out;
            }

            // Convergence by interval width (half-interval criterion)
            if (std::abs(b - a) * 0.5 <= opt.xtol) {
                out.a = a;
                out.b = b;
                out.root = c;
                out.fval = yc;
                out.iters = k;
                out.converged = true;
                out.reason = StopReason::ConvergedXtol;
                return out;
            }

            // Decide next bracket
            if (const int s_ac = detail::sign(ya) * detail::sign(yc); s_ac <= 0) {
                b = c; yb = yc; // root in [a, c]
            } else {
                a = c; ya = yc; // root in [c, b]
            }
        }

        // Reached iteration cap
        out.a=a; out.b=b; out.root=std::midpoint(a,b);
        out.fval=f(out.root);
        out.iters=opt.max_iters; out.converged=false; out.reason=StopReason::HitMaxIters;
        return out;
    }
}
#endif //TONB_NUMERICS_BISECTION_HXX