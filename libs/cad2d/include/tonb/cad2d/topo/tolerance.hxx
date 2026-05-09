//
// Created by amir on 11/9/25.
//
/**
 * @file tolerance.hxx
 * @brief Defines the Tolerance class for managing geometric tolerances
 *        within the cad2d topology layer.
 *
 * The Tolerance class provides a compact, consistent representation for
 * tolerance policies used in proximity checks, vertex merging, or
 * topological validation. It centralizes default values and comparison
 * helpers used throughout the library.
 *
 * Design goals:
 * - Represent tolerance values explicitly.
 * - Provide clear semantics and safety for geometric comparisons.
 * - Avoid magic numbers scattered across the codebase.
 *
 * Typical usage:
 * @code
 * Tolerance tol;
 * if (tol.equal(p1, p2)) {...} // equality within tolerance
 * @endcode
 */
#ifndef TONB_TOLERANCE_HXX
#define TONB_TOLERANCE_HXX
#include <tonb/base/precision.hxx>
#include <cmath>
#include <string>
#include <sstream>
namespace tonb::cad2d::topo {
    class Tolerance {
    public:
        /// @name Construction
        /// @{

        /**
         * @brief Construct a tolerance object with default values.
         *
         * Defaults:
         * - Linear tolerance = 1e-7
         * - Angular tolerance = 1e-7 radians
         */
        constexpr Tolerance() noexcept = default;

        /**
         * @brief Construct a tolerance object with custom values.
         * @param linear Linear tolerance (>=0)
         * @param angular Angular tolerance in radians (>=0).
         */
        constexpr Tolerance(const real linear, const real angular) noexcept
            : linear_(linear >= 0.0 ? linear : 1.e-7)
            , angular_(angular >= 0.0 ? angular : 1.e-9) {}

        /// @}

        /// @name Accessors
        /// @{

        /// Get the linear tolerance value.
        TNB_NODISCARD constexpr real linear() const noexcept {return linear_;}

        /// Get the angular tolerance value (in radians).
        TNB_NODISCARD constexpr real angular() const noexcept {return angular_;}

        /// @}

        /// @name Comparison helpers
        /// @{

        /**
         * @brief Compare two scalar values for equality within linear tolerance.
         */
        TNB_NODISCARD constexpr bool equal(const real a, const real b) const noexcept {
            return std::fabs(a - b) <= linear_;
        }

        /**
         * @brief Compare two 2D points for equality within linear tolerance.
         * @param x1, y1 First point.
         * @param x2, y2 Second point.
         * @reaturn True if both coordinates are within the linear tolerance.
         */
        TNB_NODISCARD constexpr bool equal(const real x1, const real y1, const real x2, const real y2) const noexcept {
            return (std::fabs(x1 - x2) <= linear_) && (std::fabs(y1 - y2) <= linear_);
        }

        /**
         * @brief Compare two angles for near-equality within angular tolerance.
         * @param a First angle in radians.
         * @param b Second angle in radians.
         */
        TNB_NODISCARD constexpr bool equal_angle(const real a, const real b) const noexcept {
            return std::fabs(a - b) <= angular_;
        }

        /// @}

        /// @name Modifiers
        /// @{

        /// Set a new linear tolerance (ignored if negative).
        constexpr void set_linear(const real v) noexcept { if (v >= 0.0) linear_= v;}

        /// Set a new angular tolerance (ignored if negative).
        constexpr void set_angular(const real v) noexcept { if (v >= 0.0) angular_ = v;}
        /// @}

        /// @name String conversion
        /// @{

        /// Convert to human-readable string for logging or debugging.
        TNB_NODISCARD std::string to_string() const {
            std::ostringstream oss;
            oss << "Tolerance(linear=" << linear_ << ", angular=" << angular_ <<")";
            return oss.str();
        }

        /// @}

    private:
        real linear_{1.e-7};        ///< Positional tolerance for distance comparison
        real angular_{1.e-9};       ///< Angular tolerance in radians
    };
}
#endif //TONB_TOLERANCE_HXX