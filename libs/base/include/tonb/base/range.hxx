//
// Created by amir on 8/22/25.
//
#pragma once
#ifndef TONB_BASE_RANGE_HXX
#define TONB_BASE_RANGE_HXX
/** @file
 * @brief Generic closed numeric range [lower, upper] for geometry and meshing.
 *
 * \par Overview
 * \li Templated wrapper around a pair of values representing a 1D bound.
 * \li Lightweight value type intended for geometric and meshing workflows.
 *
 * \par Semantics
 * \li Closed range: both endpoints are included.
 * \li Expected invariant: \c lower <= \c upper (caller responsibility unless stated).
 * \li Trivially copyable and movable when \c T is; no dynamic allocation.
 *
 * \par Type requirements
 * \li \c T must be totally ordered and copyable (for example integral or floating types).
 *
 * \par Serialization
 * \li Integrates with facilities in \c Global_Serialization.hxx (streams and archives).
 *
 * \par Notes
 * \li In this codebase, \c Standard_Real == \c double; keep computations in \c double.
 * \li Prefer the provided typedefs or aliases for clarity in client code.
 *
 * \par Thread safety
 * \li Acts as a plain value type. Concurrent reads are safe. Synchronise if mutating
 *     from multiple threads.
 *
 * \par Usage tips
 * \li Use scale-aware tolerances for floating-point comparisons around bounds.
 * \li If you need half-open semantics \c [lower, upper) document that at call sites
 *     or provide dedicated helpers to avoid ambiguity.
 *
 * \par Example
 * \code
 * // Construct a closed range and test membership
 * mylib::range<double> r{0.0, 1.0};
 * const double x = 0.25;
 * const bool inside = (x >= r.lower) && (x <= r.upper);
 * \endcode
 */

#include <utility>
#include <tonb/base/module.hxx>

namespace tonb::base {
    template<class T>
    class Range {
        /*Private Data*/
        std::pair<T, T> data_;

        // Private functions and operators

        static void check(T lower, T upper);

    public:

        // default constructor
        Range() noexcept : data_{0, 0} {}

        // Constructors
        Range(T lower, T upper) : data_{lower, upper} {
            check(data_.first, data_.second);
        }

        // Public functions and operators
        constexpr T lower() const noexcept { return data_.first; }
        constexpr T upper() const noexcept { return data_.second; }

        TNB_NODISCARD bool empty() const noexcept;
        TNB_NODISCARD bool inside(T x) const noexcept;
        TNB_NODISCARD T mid() const noexcept;

        void set(T lower, T upper);
    };
}

#include <tonb/base/range_i.hxx>
#endif  // TONB_BASE_RANGE_HXX
