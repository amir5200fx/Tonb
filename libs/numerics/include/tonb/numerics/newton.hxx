// tonb_numerics_newton.hxx
// -----------------------------------------------------------------------------
// Header-only scalar Newton (and safeguarded Newton) root finding for Tonb
//
// Features
// • Callable-based API (lambdas, functors, or a single functor returning {f,df})
// • Convergence by |f(x)|, step size |dx|, or small derivative |f'(x)|
// • Optional safeguarding with an input bracket [a,b] (projects steps + bisection)
// • Optional backtracking (Armijo-like) to ensure residual decrease
// • Doxygen-documented, no external dependencies, no fatal aborts
//
// SPDX-License-Identifier: MPL-2.0
// -----------------------------------------------------------------------------
#ifndef TONB_NUMERICS_NEWTON_HXX
#define TONB_NUMERICS_NEWTON_HXX
#include <tonb/base/precision.hxx>
#include <cmath>
#include <cstdint>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>

namespace tonb::numerics {
    // ============================================================================
    // Public API types
    // ============================================================================

    enum class NewtonStop : std::uint8_t {
        ConvergedFtol,      //!< |f(x)| <= ftol
        ConvergedXtol,      //!< |dx| <= Xton * (|x| + 1)
        ConvergedGtol,      //!< |f'(x)| <= gtol
        HitMaxIter,         //!< iteration budget exhausted
        NotBracketed,       //!< require_bracket was true but f(a)*f(b) > 0
        DomainError,        //!< non-finite f or f' value
        ZeroDerivative      //!< |f'(x)| numerically zero and no safeguard available
    };

    /** @brief User controls for Newton solver */
    struct NewtonOptions {
        int max_iter = 100; //!< iteration cap
        int min_iter = 0; //!< minimum number of iterations before convergence check
        real ftol = 1e-10; //!< function tolerance
        real xtol = 1e-12; //!< step tolerance (relative to |x|+1)
        real gtol = 1e-14; //!< derivative tolerance for stagnation
        real damping = 1.0; //!< multiplicative damping on dx (0,1]
        bool backtrack = true; //!< enable backtracking when residual increases
        int max_btstep = 10; //!< max backtracking halvings


        // Safeguard options
        bool require_bracket = false; //!< if true, need sign change on [a,b]
        std::optional<std::pair<real,real>> bracket{}; //!< optional [a,b]
    };

    /** @brief Result returned by newton() */
    struct NewtonResult {
        real x = std::numeric_limits<real>::quiet_NaN(); //!< root estimate
        real f = std::numeric_limits<real>::quiet_NaN(); //!< f(x)
        real g = std::numeric_limits<real>::quiet_NaN(); //!< f'(x)
        int iters = 0; //!< iterations used
        bool converged = false; //!< met any criterion
        NewtonStop reason = NewtonStop::HitMaxIter; //!< termination
        // If a bracket was used, the final bracket captured here
        real a = std::numeric_limits<real>::quiet_NaN();
        real b = std::numeric_limits<real>::quiet_NaN();
    };

    // ============================================================================
    // Utility detail
    // ============================================================================

    namespace detail {
        inline bool finite(const real v) {return std::isfinite(v);}

        inline void normalise(real& a, real& b) { if (b < a) std::swap(a,b);}

        inline bool sign_change(const real fa, const real fb) {return (fa==0.0) || (fb==0.0) || (fa*fb < 0.0);}

        inline real clamp(const real x, const real a, const real b) {return x < a ? a : (x > b ? b : x);}
    }

    // ============================================================================
    // Core solvers
    // ============================================================================

    /**
     * @brief Newton with separate value and derivative callables.
     *
     * @tparam F callable: real(real) for f(x)
     * @tparam DF callable: real(real) for f'(x)
     * @param f function
     * @param df derivative
     * @param x0 initial guess
     * @param opt options (safeguards, tolerances, damping)
     * @reaturn NewtonResult
     *
     * @par Safeguarding
     * If @c opt.bracket is provided, steps are projected into the bracket.
     * If a proposed step leaves [a,b] or increases |f| and @c backtrack is enabled,
     * we halve the step up to @c max_btstep times. If still not acceptable and a valid
     * bracket exists, we fall back to bisection to shrink [a,b].
     *
     * @par min_iter behaviour
     * Convergence criteria (ftol / xtol / gtol) are only evaluated after at least
     * @c min_iter iterations have been performed. This helps avoid premature
     * acceptance on noisy or stiff problems and can be useful for diagnostics.
     */
    template<class F, class DF>
    NewtonResult newton(F&& f, DF&& df, const real x0, NewtonOptions opt = {}) {
        NewtonResult R{};

        real a = std::numeric_limits<real>::quiet_NaN();
        real b = std::numeric_limits<real>::quiet_NaN();

        if (opt.bracket) {a = opt.bracket->first; b = opt.bracket->second; detail::normalise(a,b);}

        // Check bracket precondition
        real fa0 = std::numeric_limits<real>::quiet_NaN();
        real fb0 = std::numeric_limits<real>::quiet_NaN();
        if (opt.bracket) {
            fa0 = f(a);
            fb0 = f(b);
            if (!detail::finite(fa0) || !detail::finite(fb0)) {
                R.reason = NewtonStop::DomainError;
                return R;
            }
            if (opt.require_bracket && !detail::sign_change(fa0, fb0)) {
                R.a = a;
                R.b = b;
                R.reason = NewtonStop::NotBracketed;
                return R;
            }
        }

        real x = x0;
        real fx = f(x); if(!detail::finite(fx)){ R.reason=NewtonStop::DomainError; return R; }

        // If bracket is provided, keep it updated
        if (opt.bracket) {
            if (!std::isnan(fa0) && !std::isnan(fb0)) {
                if (fa0==0.0){ x=a; fx=0.0; }
                else if (fb0==0.0){ x=b; fx=0.0; }
                else if (fx==0.0){ /* ok */ }
                else if (fa0*fx < 0.0){ b = x; fb0 = fx; }
                else if (fb0*fx < 0.0){ a = x; fa0 = fx; }
            }
        }

        for (int k = 1; k <= opt.max_iter; ++k) {
            R.iters = k;
            real dfx = df(x); if(!detail::finite(dfx)){ R.reason=NewtonStop::DomainError; return R; }
            R.g = dfx;

            // Convergence checks
            if (k >= opt.max_iter) {
                if (std::abs(fx) <= opt.ftol) {
                    R.x = x;
                    R.f = fx;
                    R.converged = true;
                    R.reason = NewtonStop::ConvergedFtol;
                    R.a = a;
                    R.b = b;
                    return R;
                }
                if (std::abs(dfx) <= opt.gtol) {
                    R.x = x;
                    R.f = fx;
                    R.converged = true;
                    R.reason = NewtonStop::ConvergedGtol;
                    R.a = a;
                    R.b = b;
                    return R;
                }
            }

            // Newton step
            if (dfx == 0.0) {
                R.x = x;
                R.f = fx;
                R.converged = false;
                R.reason = NewtonStop::ZeroDerivative;
                R.a = a;
                R.b = b;
                return R;
            }
            real dx = - opt.damping * (fx / dfx);
            real xn = x + dx;

            // If bracketed, project inside and/or backtrack on residual increase
            auto accept = [&](real trial){
                if (opt.bracket) trial = detail::clamp(trial, a, b);
                real ft = f(trial);
                return std::pair{trial, ft};
            };

            auto [xt, ft] = accept(xn);
            if (opt.backtrack) {
                int bt = 0;
                while (std::abs(ft) > std::abs(fx) && bt < opt.max_btstep){
                    dx *= 0.5; xt = x + dx; if (opt.bracket) xt = detail::clamp(xt, a, b);
                    ft = f(xt); ++bt;
                    if(!detail::finite(ft)){ R.reason=NewtonStop::DomainError; return R; }
                }
            }

            // If bracket is present and step still not helpful, do bisection shrink
            if (opt.bracket && std::abs(ft) > std::abs(fx)){
                // fall back to midpoint
                xt = 0.5 * (a + b);
                ft = f(xt); if(!detail::finite(ft)){ R.reason=NewtonStop::DomainError; return R; }
            }

            // Relative step convergence
            double rel = std::abs(xt - x) / (std::abs(xt) + 1.0);
            if (k >= opt.min_iter) {
                if (rel <= opt.xtol) {
                    R.x = xt;
                    R.f = ft;
                    R.converged = true;
                    R.reason = NewtonStop::ConvergedXtol;
                    R.a = a;
                    R.b = b;
                    return R;
                }
            }

            // Update state
            x = xt; fx = ft;
            if (opt.bracket){ if (fa0*fx < 0.0){ b = x; fb0 = fx; } else { a = x; fa0 = fx; } }
        }

        R.x = x; R.f = fx; R.converged = false; R.reason = NewtonStop::HitMaxIter; R.a=a; R.b=b; return R;
    }

    /**
     * @brief Newton with a single callable providing both value and derivative.
     *
     * The callable must return `std::pair<real, real>{f(x), f'(x)}`.
     */
    template<class F>
    NewtonResult newton(F&& f_and_df,const real x0, NewtonOptions opt = {}) {
        auto f = [&](real x){ return f_and_df(x).first; };
        auto df = [&](real x){ return f_and_df(x).second; };
        return newton(f, df, x0, opt);
    }
}
#endif //TONB_NUMERICS_NEWTON_HXX