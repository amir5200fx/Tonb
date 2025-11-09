// tonb_numerics_integration.hxx
// -----------------------------------------------------------------------------
// Header-only adaptive 1D integration for Tonb numerics
//
// This header exposes a single, stable API that supports **two** integrators:
//  • Adaptive Simpson (with Richardson error estimate)
//  • Adaptive Gauss–Legendre (n = 7) with split-halving error
//
// Design goals
//  • Small, dependency-light, and exception-free by default
//  • Deterministic evaluation caps (max_depth, max_evals)
//  • Clear separation of *options*, *results*, and *stop reasons*
//  • Callable-based interface (works with lambdas, functors, function pointers)
//  • Ready to extend with new methods (e.g., Gauss–Kronrod or tanh–sinh)
//
// SPDX-License-Identifier: MPL-2.0 (or your project license)
// -----------------------------------------------------------------------------
#pragma once
#ifndef TONB_NUMERICS_INTEGRATION_HXX
#define TONB_NUMERICS_INTEGRATION_HXX

#include <tonb/base/precision.hxx>
#include <cmath>
#include <cstdint>
#include <iterator>
#include <limits>
#include <numeric>
#include <type_traits>
#include <utility>

namespace tonb::numerics {
    // ============================================================================
    // Public API types
    // ============================================================================

    /**
     * @brief Selects the integration algorithm used by integrate().
     *
     * @note The chosen algorithm affects evaluation density, error estimate, and
     *      robustness on different integrand classes. See @ref IntegrateOptions.
     */
    enum class IntegratorKind : std::uint8_t {
        /** Adaptive Simpson's rule with Richardson error control.*/
        Simpson,
        /** Adaptive Gauss-Legendre with n=7 nodes (symmetric, 7-point rule).*/
        Gauss7
    };

    /**
     * @brief Reason why integration terminated.
     */
    enum class IntegrateStop: std::uint8_t {
        /** Global error target satisfied: error_est <= max(atol, rtol*|value|)*/
        Converged,
        /** Evaluation budget exceeded before convergence.*/
        HitMaxEvals,
        /** Subdivision depth limit reached before convergence.*/
        HitMaxDepth,
        /** Non-finite value encountered in f(x) (NaN/Inf).*/
        DomainError
    };

    /**
     * @brief Runtime controls for integrate()
     *
     * Convergence is declared when the accumulated error estimate is less than or
     * equal to @c max(atol, rtol * |value|). The @c max_depth and @c max_evals
     * parameters provide hard safety caps on work.
     */
    struct IntegrateOptions {
        /** Absolute error tolerance (global). Default: 1e-8.*/
        real atol = 1e-8;
        /** Relative error tolerance (global). Default: 1e-8.*/
        real rtol = 1.e-8;
        /** Maximum number of recursive bisections. Default: 20.*/
        int max_depth = 20;
        /** Maximum total f-evaluation across the full integral. Default: 2^16.*/
        int max_evals = 1 << 16;
        /** Minimum subdivision depth required before accepting a node. Default: 0. */
        int min_depth = 0;
        /** Algorithm to use. Default: IntegratorKind::Gauss7.*/
        IntegratorKind kind = IntegratorKind::Gauss7;
    };

    /**
     * @brief Result of integrate()
     */
    struct IntegrateResult {
        /** Approximate value of the integral.*/
        real value = std::numeric_limits<real>::quiet_NaN();
        /** Accumulated error estimate (see algorithm notes below).*/
        real error_est = std::numeric_limits<real>::quiet_NaN();
        /** Number of integrand evaluations used.*/
        int evals = 0;
        /** Maximum subdivision depth reached.*/
        int depth_used = 0;
        /** True if global goal was satisfied.*/
        bool converged = false;
        /** Termination reason. */
        IntegrateStop reason = IntegrateStop::HitMaxEvals;
    };

    // ============================================================================
    // Internal helpers (implementation detail)
    // ============================================================================

    namespace detail {
        inline bool finite(const real x) {return std::isfinite(x);}

        inline real goal(const real atol, const real rtol, const real approx) {
            return std::max(atol, rtol * std::abs(approx));
        }

        // ---------------- Simpson primitives ----------------

        /**
         * @brief One-step Simpson estimate on [a,b[ given f(a), f((a+b)/2), f(b).
         * @param h Interval length (b-a).
         * @param fa f(a)
         * @param fm f((a+b)/2)
         * @param fb f(b)
         */
        inline real simpson_est(const real h, const real fa, const real fm, const real fb) {
            return (h* (fa + 4*fm + fb))/6.0;
        }

        template<class F>
        IntegrateResult integrate_simpson(F&& f, const real a_in, const real b_in, const IntegrateOptions& opt) {
            IntegrateResult out{};

            real a = a_in, b = b_in, sign = 1.0;
            if (b < a) { std::swap(a, b); sign = -1.0; }
            if (!(b > a)) { out.value=0.0; out.error_est=0.0; out.converged=true; out.reason=IntegrateStop::Converged; return out; }

            const real h  = b - a;
            const real m  = std::midpoint(a, b);
            const real fa = f(a);   if (!finite(fa)) { out.reason=IntegrateStop::DomainError; return out; }
            const real fm = f(m);   if (!finite(fm)) { out.reason=IntegrateStop::DomainError; return out; }
            const real fb = f(b);   if (!finite(fb)) { out.reason=IntegrateStop::DomainError; return out; }
            out.evals = 3;

            struct Node { real a,b,fa,fm,fb,S,tol; int depth; };
            Node stack[64];
            int  sp = 0;
            int  maxD = std::min(opt.max_depth, static_cast<int>(std::size(stack))-2);
            stack[sp++] = Node{a,b,fa,fm,fb, simpson_est(h,fa,fm,fb), goal(opt.atol,opt.rtol,0.0), 0};

            real app_sum = 0.0, err_sum = 0.0; int depth_hit = 0;

            while (sp>0) {
                Node n = stack[--sp];
                depth_hit = std::max(depth_hit, n.depth);
                const real a1=n.a, b1=n.b, m1=std::midpoint(a1,b1), h1=b1-a1;
                const real lm = std::midpoint(a1,m1);
                const real rm = std::midpoint(m1,b1);
                const real fla=n.fa;
                const real flm=f(lm); if (!finite(flm)) { out.reason=IntegrateStop::DomainError; return out; }
                const real flm2=n.fm;
                const real frm=f(rm); if (!finite(frm)) { out.reason=IntegrateStop::DomainError; return out; }
                const real frb=n.fb;
                out.evals += 2; if (out.evals>opt.max_evals) { out.reason=IntegrateStop::HitMaxEvals; out.depth_used=depth_hit; return out; }

                const real Sleft  = simpson_est(h1*0.5, fla, flm, flm2);
                const real Sright = simpson_est(h1*0.5, flm2, frm, frb);
                const real S2 = Sleft + Sright;
                const real err = std::abs(S2 - n.S) / 15.0;

                const bool depth_ok = (n.depth >= opt.min_depth);
                if (err <= n.tol && depth_ok) { app_sum += S2 + (S2 - n.S)/15.0; err_sum += err; continue; }
                if (!depth_ok && n.depth < maxD) {
                    const real child_tol = 0.5 * n.tol;
                    stack[sp++] = Node{ m1, b1, flm2, frm, frb, Sright, child_tol, n.depth+1 };
                    stack[sp++] = Node{ a1, m1, fla, flm, flm2, Sleft, child_tol, n.depth+1 };
                    continue;
                }
                if (n.depth >= maxD) { app_sum += S2; err_sum += err; out.reason=IntegrateStop::HitMaxDepth; continue; }

                const real child_tol = 0.5 * n.tol;
                stack[sp++] = Node{ m1, b1, flm2, frm, frb, Sright, child_tol, n.depth+1 };
                stack[sp++] = Node{ a1, m1, fla,  flm, flm2, Sleft,  child_tol, n.depth+1 };
            }

            out.value = sign * app_sum;
            out.error_est = err_sum;
            out.depth_used = depth_hit;
            const real g = goal(opt.atol,opt.rtol,out.value);
            out.converged = (out.error_est <= g);
            if (out.converged && out.reason!=IntegrateStop::HitMaxDepth) out.reason=IntegrateStop::Converged;
            return out;
        }

        // --------------- Gauss–Legendre n=7 primitives ---------------

        /**
         * @brief Symmetric Gauss-Legendre 7-point rule constants.
         *
         * Only positive abscissae and weights are stored; symmetry is applied
         * around the midpoint during evaluation.
         */
        struct GL7 {
            static constexpr real x[4] = {
                0.0,
                0.405845151377397166906606412076961,
                0.741531185599394439863864773280788,
                0.949107912342758524526189684047851
            };
            static constexpr real w[4] = {
                0.417959183673469387755102040816327,
                0.381830050505118944950369775488975,
                0.279705391489276667901467771423780,
                0.129484966168869693270611432679082
            };
        };

        /**
         * @brief Apply the 7-point Gauss-Legendre rule on [a,b].
         * @return Pair (integral estimate, evaluation used).
         */
        template<class F>
        std::pair<real, int> gl7_whole(F&& f, const real a, const real b) {
            const real c = 0.5*(a+b), h = 0.5*(b-a);
            real I = GL7::w[0] * f(c);
            int evals = 1;
            for (int i=1;i<4;++i) {
                const real dx = h * GL7::x[i];
                const real fl = f(c - dx);
                const real fr = f(c + dx);
                I += GL7::w[i] * (fl + fr);
                evals += 2;
            }
            return {I*h, evals};
        }

        template<class F>
        IntegrateResult integrate_gauss7(F&& f, const real a_in, const real b_in, const IntegrateOptions& opt) {
            IntegrateResult out{};

            real a = a_in, b = b_in, sign = 1.0;
            if (b < a) { std::swap(a, b); sign = -1.0; }
            if (!(b > a)) { out.value=0.0; out.error_est=0.0; out.converged=true; out.reason=IntegrateStop::Converged; return out; }

            struct Node { real a,b,Ig,tol; int depth; };
            Node stack[64];
            int  sp=0; int depth_hit=0;
            int  maxD = std::min(opt.max_depth, static_cast<int>(std::size(stack))-2);

            auto [I0, e0] = gl7_whole(f, a, b);
            out.evals = e0; if (!finite(I0)) { out.reason=IntegrateStop::DomainError; return out; }
            stack[sp++] = Node{a,b,I0, goal(opt.atol,opt.rtol,0.0), 0};

            real app_sum=0.0, err_sum=0.0;

            while (sp>0) {
                Node n = stack[--sp];
                depth_hit = std::max(depth_hit, n.depth);
                const real m = std::midpoint(n.a, n.b);

                auto [Il, el] = gl7_whole(f, n.a, m);
                auto [Ir, er] = gl7_whole(f, m, n.b);
                const int subdivision_evals = el + er;
                out.evals += subdivision_evals;
                if (out.evals > opt.max_evals) { out.reason=IntegrateStop::HitMaxEvals; out.depth_used=depth_hit; return out; }
                if (!finite(Il) || !finite(Ir)) { out.reason=IntegrateStop::DomainError; return out; }

                const real I2 = Il + Ir;
                const real err = std::abs(I2 - n.Ig);

                const bool depth_ok = (n.depth >= opt.min_depth);
                if (err <= n.tol && depth_ok) { app_sum += I2; err_sum += err; continue; }
                if (!depth_ok && n.depth < maxD) {
                    const real child_tol = 0.5 * n.tol;
                    stack[sp++] = Node{ std::midpoint(n.a,n.b), n.b, Ir, child_tol, n.depth+1 };
                    stack[sp++] = Node{ n.a, std::midpoint(n.a,n.b), Il, child_tol, n.depth+1 };
                    continue;
                }
                if (n.depth >= maxD) { app_sum += I2; err_sum += err; out.reason=IntegrateStop::HitMaxDepth; continue; }

                const real child_tol = 0.5 * n.tol;
                stack[sp++] = Node{ std::midpoint(n.a,n.b), n.b, Ir, child_tol, n.depth+1 };
                stack[sp++] = Node{ n.a, std::midpoint(n.a,n.b), Il, child_tol, n.depth+1 };
            }

            out.value = sign * app_sum;
            out.error_est = err_sum;
            out.depth_used = depth_hit;
            const real g = goal(opt.atol,opt.rtol,out.value);
            out.converged = (out.error_est <= g);
            if (out.converged && out.reason!=IntegrateStop::HitMaxDepth) out.reason=IntegrateStop::Converged;
            return out;
        }
    }

    // ============================================================================
    // Public API: integrate (dispatch by IntegratorKind)
    // ============================================================================

    /**
     * @brief Numerically integrates f over [a,b] using the selected algorithm.
     *
     * @tparam F Callable type convertible to real(real).
     * @param f Integrand (must be defined and finite on [a,b]).
     * @param a Lower bound (integration direction inferred from a,b order).
     * @param b Upper bound.
     * @param opt Integration options; choose algorithm via IntegratorKind.
     * @return IntegrateResult with value, error estimate, evaluation count, and
     *       termination reason.
     *
     * @par Robustness
     * If @p f returns NaN/Inf at any evaluation, integration stops with
     * IntegrateStop::DomainError. Degenerate intervals (a==b) return zero with
     * Converted.
     */
    template<class F>
    IntegrateResult integrate(F&& f, const real a, const real b, IntegrateOptions opt = {}) {
        switch (opt.kind) {
            case IntegratorKind::Simpson:
                return detail::integrate_simpson(std::forward<F>(f), a, b, opt);
            case IntegratorKind::Gauss7:
            default:
                return detail::integrate_gauss7(std::forward<F>(f), a, b, opt);
        }
    }

    // ============================================================================
    // Legacy-style adapter (optional)
    // ============================================================================

    /**
     * @brief Thin adapter compatible with legacy "Info" style call sites.
     *
     * Maps a single @c tolerance to both absolute and relative tolerances.
     */
    struct AdaptiveInfo {
        // Inputs
        real lower = 0.0;          //!< Lower bound
        real upper = 1.0;          //!< Upper bound
        real tolerance = 1e-8;     //!< Maps to both atol and rtol
        int    max_iter  = 500;      //!< Roughly mapped to max_evals
        int    min_depth = 0;
        IntegratorKind kind = IntegratorKind::Gauss7; //!< Selected method

        // Outputs
        real result    = std::numeric_limits<real>::quiet_NaN(); //!< Integral value
        real error     = std::numeric_limits<real>::quiet_NaN(); //!< Error estimate
        int    evals     = 0;                                       //!< f-evaluations
        bool   converged = false;                                   //!< Convergence flag
    };

    /**
     * @brief Executes integrate() using AdaptiveInfo I/O.
     * @return IntegrateStop reason code from the run.
     */
    template <class F>
    inline IntegrateStop solve_adaptive(F&& f, AdaptiveInfo& info) {
        IntegrateOptions opt;
        opt.atol = info.tolerance;
        opt.rtol = info.tolerance;
        opt.max_evals = std::max(8, info.max_iter * 4);
        opt.min_depth = info.min_depth;
        opt.kind = info.kind;

        auto r = integrate(std::forward<F>(f), info.lower, info.upper, opt);
        info.result    = r.value;
        info.error     = r.error_est;
        info.evals     = r.evals;
        info.converged = r.converged;
        return r.reason;
    }
}
#endif //TONB_NUMERICS_INTEGRATION_HXX