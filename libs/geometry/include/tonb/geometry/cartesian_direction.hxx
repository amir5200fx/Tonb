//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_CARTESIAN_DIRECTION_HXX
#define TONB_GEOMETRY_CARTESIAN_DIRECTION_HXX
/*!
 * \file cartesian_direction.hxx
 * \brief Defines the CartesianDirection enum and utilities to work with X, Y, Z axes.
 * \ingroup tonb-geometry
 *
 * This header provides a small, constexpr-friendly API for addressing elements by
 * Cartesian axis. Typical use cases include selecting components of 3D tuples,
 * addressing rows/columns in matrices, or logging axis tags in diagnostics.
 *
 * ### Example
 * \code{.cpp}
 * using namespace tonb::geometry;
 * std::array<double,3> v{{1.0, 2.0, 3.0}};
 * auto y = select(v, CartesianDirection::Y); // 2.0
 * std::size_t i = to_index(CartesianDirection::Z); // 2
 * std::cout << CartesianDirection::X; // prints "X"
 * \endcode
 *
 * The API is `noexcept` and usable in constant-evaluated contexts where possible.
 */
#include <cstdint>
#include <cstddef>
#include <array>
#include <ostream>
#include <string_view>

#include <tonb/geometry/module.hxx>

namespace tonb::geometry {
    /** \brief Cartesian direction tag: X, Y, Z. */
    enum class CartesianDirection : std::uint8_t { X = 0, Y = 1, Z = 2 };

    inline constexpr std::size_t cartesian_direction_count = 3;

    TNB_NODISCARD inline constexpr std::size_t to_index(CartesianDirection d) noexcept {
        return static_cast<std::size_t>(d);
    }

    TNB_NODISCARD inline constexpr std::string_view to_string(const CartesianDirection d) noexcept {
        switch (d) { case CartesianDirection::X: return "X";
            case CartesianDirection::Y: return "Y";
            case CartesianDirection::Z: return "Z"; }
        return "X";
    }

    /** \brief Select a mutable component from a 3-element array by axis. */
    template<class T>
    TNB_NODISCARD inline constexpr T& select(std::array<T,3>& a, const CartesianDirection d) noexcept {
        return a[to_index(d)];
    }
    /** \brief Select a const component from a 3-element array by axis. */
    template<class T>
    TNB_NODISCARD inline constexpr const T& select(const std::array<T,3>& a, const CartesianDirection d) noexcept {
        return a[to_index(d)];
    }

    /** \brief Stream the axis tag ("X", "Y", or "Z"). */
    inline std::ostream& operator<<(std::ostream& os, const CartesianDirection d) {
        return os << to_string(d);
    }

    /** \\brief Short alias for \\c CartesianDirection. */
    using Direction = CartesianDirection;
}
#endif //TONB_GEOMETRY_CARTESIAN_DIRECTION_HXX