//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_BASE_PRECISION_HXX
#define TONB_BASE_PRECISION_HXX
/** @file
 * @brief Single point of control for numeric precision.
 *
 * \par Overview
 * This header centralises the definition of the library-wide real number type
 * and performs a compile-time check for IEEE 754 compliance.
 *
 * \par Contents
 * \li Includes \c <limits> for \c std::numeric_limits.
 * \li Defines the alias \c mylib::real as \c double.
 * \li Performs a compile-time check:
 * \code
 * static_assert(std::numeric_limits<double>::is_iec559, "Need IEEE-754 double");
 * \endcode
 *
 * \par Rationale
 * Using a single alias allows the precision to be changed in one location.
 * The IEEE 754 check ensures predictable behaviour for NaNs, infinities,
 * rounding and comparisons, which is important for robust geometric algorithms.
 */

#include <tonb/base/module.hxx>

#include <limits>
#include <optional>
#include <algorithm>
#include <cassert>

namespace tonb::base {
    using real = double;

    static_assert(std::numeric_limits<double>::is_iec559, "Need IEEE-754 floating point type");
    // ---- Safety checks (catch misconfigurations early)
    static_assert(!std::numeric_limits<real>::is_integer, "real must be a floating type");

    // One place to set tolerances (can make these runtime-configurable later)
    // Reasonable defaults derived from the type:
    inline constexpr real EPS_REL = static_cast<real>(100) * std::numeric_limits<real>::epsilon();
    inline constexpr real EPS_ABS =
        std::is_same_v<real, float>      ? static_cast<real>(1e-6f)  :
        std::is_same_v<real, double>     ? static_cast<real>(1e-12)  :
                                           static_cast<real>(1e-15L);

    static_assert(EPS_ABS > static_cast<real>(0), "EPS_ABS ended up as 0 — check 'real' typedef");
    static_assert(EPS_REL > static_cast<real>(0), "EPS_REL ended up as 0 — check 'real' typedef");

    TNB_NODISCARD inline bool near_zero(const real x,
                                               const real eps_abs = EPS_ABS,
                                               const real eps_rel = EPS_REL,
                                               const real scale   = 1.0) noexcept
    {
        // relative criterion scaled by a problem magnitude (default = 1)
        const real tol = eps_abs + eps_rel * std::max(static_cast<real>(1), std::abs(scale));
        return std::abs(x) <= tol;
    }

    // 1) Debug helper: assert in Debug, no cost in Release
    TNB_NODISCARD inline real div_dbg(const real num, const real den, const real scale = 1.0) {
        assert(!near_zero(den, EPS_ABS, EPS_REL, scale) && "division by (near) zero");
        return num / den;
    }

    // 2) Optional-returning helper (no exceptions)
    TNB_NODISCARD inline std::optional<real> try_div(const real num, const real den, const real scale = 1.0) {
        if (near_zero(den, EPS_ABS, EPS_REL, scale)) return std::nullopt;
        return num / den;
    }

    // 3) “Safe” division with a chosen fallback (Inf by default)
    TNB_NODISCARD inline real div_or(const real num, const real den,
                                     const real fallback = std::numeric_limits<real>::infinity(),
                                     const real scale = 1.0) {
        return near_zero(den, EPS_ABS, EPS_REL, scale) ? fallback : num / den;
    }

    /// tweak factor (8) to suit numeric stability needs/project scale
    TNB_NODISCARD inline bool nearly_equal(const real a, const real b, const int factor = 8) noexcept {
        // scale-aware tolerance: tighter than 1 ULP but robust for larger magnitudes
        using std::abs;
        const real diff  = abs(a - b);
        const real scale = std::max<real>(static_cast<real>(1), std::max(abs(a), abs(b)));

        const real tol   = std::numeric_limits<real>::epsilon() * factor * scale;
        return diff <= tol;
    }
}
namespace tonb { using real = base::real; }
#endif  // TONB_BASE_PRECISION_HXX
