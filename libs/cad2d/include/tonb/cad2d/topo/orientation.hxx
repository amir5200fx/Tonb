//
// Created by amir on 11/9/25.
//
/**
 * @file orientation.hxx
 * @brief Defines the Orientation enumeration for the cad2d topology layer.
 *
 * The Orientation enum represents the traversal direction of a topological
 * entity such as a half-edge or wire relative to its underlying geometric curve.
 *
 * ### Design notes
 * - This type belongs to the **pure topology** layer: it has no dependency on
 *   geometry kernels or orientation flags from OCCT.
 * - Used consistently throughout the library to indicate cure direction in
 *   relation to parameterization or boundary orientation.
 * - Provides small inline utilities for conversion and readability.
 *
 * Typical usage:
 * @code
 * Orientation o = Orientation::forward;
 * if (o == Orientation::reversed) {...}
 * std::string name = to_string(o);  // "Forward" or "Reversed"
 * @endcode
 */
#pragma once
#ifndef TONB_CAD2D_TOPO_ORIENTATION_HXX
#define TONB_CAD2D_TOPO_ORIENTATION_HXX
#include <string_view>
#include <string>
#include <cstdint>
#include <optional>

namespace tonb::cad2d::topo {

    /**
     * @enum Orientation
     * @brief Specifies the direction of traversal along a curve or boundary.
     *
     * Orientation describes whether a topological entity (such as a half-edge)
     * follows the natural parameter direction of its associated cure
     * (forward) or the opposite (reversed).
     *
     * - `forward` -> traversal increases the curve parameter (u0 -> u1)
     * - `reversed` -> traversal decreases the curve parameter (u1 -> u0)
     */
    enum class Orientation : std::uint8_t {
        forward = 0,        ///< Curve parameter increases from start to end.
        reversed = 1        ///< Curve parameter decreases from start to end.
    };

    /**
     * @brief Return the opposite of a given orientation
     * @param o The input orientation.
     * @return The flipped orientation.
     */
    constexpr Orientation opposite(const Orientation o) noexcept {
        return (o == Orientation::forward) ? Orientation::reversed : Orientation::forward;
    }

    /**
     * @brief Convert an Orientation to a human-readable string view.
     * @param o Orientation value.
     * @return "Forward" or "Reversed".
     */
    constexpr std::string_view to_string_view(const Orientation o) noexcept {
        return (o == Orientation::forward) ? "Forward" : "Reversed";
    }

    /**
     * @brief Parse a string view into an Orientation
     *
     * Case-insensitive for common spellings; returns std::nullopt if parsing fails.
     *
     * @param s Input string view ("forward", "reversed", "f", "r").
     * @return Parsed Orientation if recognized.
     */
    inline std::optional<Orientation> from_string(const std::string_view s) noexcept {
        if (s.empty()) return std::nullopt;
        auto lower = [](const char c){ return static_cast<char>((c >= 'A' && c <= 'Z') ? c + 32 : c); };
        if (s.size() == 1) {
            const char c = lower(s.front());
            if (c == 'f') return Orientation::forward;
            if (c == 'r') return Orientation::reversed;
            return std::nullopt;
        }
        std::string tmp;
        tmp.reserve(s.size());
        for (const char c : s) tmp.push_back(lower(c));
        if (tmp == "forward") return Orientation::forward;
        if (tmp == "reversed") return Orientation::reversed;
        return std::nullopt;
    }
}
#endif //TONB_CAD2D_TOPO_ORIENTATION_HXX