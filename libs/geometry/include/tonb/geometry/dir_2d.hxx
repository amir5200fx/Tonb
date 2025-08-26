//
// Created by amir on 8/23/25.
//
#pragma once
#ifndef TONB_GEOMETRY_DIR_2D_HXX
#define TONB_GEOMETRY_DIR_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>

namespace tonb::geometry {
    class Dir2D {
    public:
        using Array = std::array<real, 2>;

        /*Private Data*/

        Array components_ {1,0};

        // Public functions and operators

        void normalize();
    public:

        // default constructor

        Dir2D() noexcept = delete;

        // constructors

        Dir2D(const real u, const real v) : components_{u, v} {normalize();}
        explicit Dir2D(const Array& component) noexcept : components_{component} {}

        Dir2D(const Dir2D&) noexcept = default;
        Dir2D(Dir2D&&) noexcept = default;

        // Public functions and operators

        const auto& components() const noexcept { return components_; }
        constexpr real u() const noexcept { return components_[0]; }
        constexpr real v() const noexcept { return components_[1]; }

        // indexing
        TNB_NODISCARD constexpr real operator[](const size_t i) const noexcept { return components_[i]; }
        TNB_NODISCARD constexpr real at(const size_t i) const noexcept { return components_[i]; }

        void set_component(const size_t i, const real v) noexcept { components_[i] = v; }
        void set_component(const real u, const real v) noexcept {components_[0] = u; components_[1] = v;}
    };
}
#endif //TONB_GEOMETRY_DIR_2D_HXX