/* -*- C++ -*- */
/**
 * \file
 * \brief 2D Cartesian point type used across Tonb geometry.
 *
 * \details Lightweight value type wrapping two \c real components \c (x,y).
 * Provides const/mutable accessors, indexing, translations, scaling and rotation.
 * Designed for header-only use of trivial operations; larger algorithms live out-of-line.
 *
 * \author  Amir Amir-Solaymani
 * \since   0.19.0
 * \ingroup tonb_geometry
 *
 * \copyright
 * Copyright (c) 2025 Tonb.
 * SPDX-License-Identifier: MIT
 */
#ifndef TONB_GEOMETRY_PNT_2D_HXX
#define TONB_GEOMETRY_PNT_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <iosfwd>

namespace tonb::geometry {

    // Forward Declarations
    class Pnt2d;

    TNBGEOM_ND_EXPORT Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2) noexcept;
    TNBGEOM_ND_EXPORT Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2, const Pnt2d& p3) noexcept;
    TNBGEOM_ND_EXPORT real distance(const Pnt2d& p1, const Pnt2d& p2);
    TNBGEOM_ND_EXPORT real distance_sq(const Pnt2d& p1, const Pnt2d& p2);
    TNBGEOM_ND_EXPORT bool almost_equal(const Pnt2d& p1, const Pnt2d& p2);

    /**
     * @brief Calculates the volume of the bounding box
     */
    TNBGEOM_ND_EXPORT real volume(const Pnt2d& p1, const Pnt2d& p2) noexcept;

    class Pnt2d {
    public:
        using Array = std::array<real, 2>;
    private:
        /*Private Data*/

        Array components_{};
    public:

        // static members
        inline static constexpr int nb_cmpts = 2;
        static TNBGEOM_EXPORT const Pnt2d null;

        using ptType = Pnt2d;

        enum {
            dim = 2
        };

        // default constructor
        Pnt2d() noexcept = default;

        // constructors

        Pnt2d(const real x, const real y) noexcept : components_({x, y}) {}
        explicit Pnt2d(const Array& components) noexcept : components_(components) {}

        Pnt2d(const Pnt2d&) noexcept = default;
        Pnt2d(Pnt2d&&) noexcept = default;

        // Public functions and operators

        Pnt2d& operator=(const Pnt2d&) noexcept = default;
        Pnt2d& operator=(Pnt2d&&) noexcept = default;

        // Access
        TNB_NODISCARD const auto& components() const noexcept { return components_; }
        TNB_NODISCARD constexpr auto x() const noexcept { return components_[0]; }
        TNB_NODISCARD constexpr auto y() const noexcept { return components_[1]; }

        void set_x(const real x) noexcept { components_[0] = x; }
        void set_y(const real y) noexcept { components_[1] = y; }

        TNB_NODISCARD constexpr const real* data() const noexcept { return components_.data(); }
        TNB_NODISCARD constexpr  real* data() noexcept { return components_.data(); }

        // indexing
        TNB_NODISCARD constexpr real operator[](const size_t i) const noexcept {return components_[i];}
        constexpr real& operator[](const size_t i) noexcept { return components_[i]; }

        // transform
        // Mutating versions:
        TNBGEOM_EXPORT Pnt2d& translate(real dx, real dy) noexcept;
        Pnt2d& scale(real s) noexcept;
        /** \brief Rotate point around the origin by \p angle (radians, CCW). */
        Pnt2d& rotate(real angle);

        // Non-mutating convenience
        TNBGEOM_ND_EXPORT Pnt2d translated(real dx, real dy) const noexcept;
        TNBGEOM_ND_EXPORT Pnt2d scaled(real s) const noexcept;
        TNBGEOM_ND_EXPORT Pnt2d rotated(real angle) const noexcept;

        // io functions
        void print(std::ostream& os) const noexcept;
        void write_to_plt(std::fstream& os) const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Pnt2d& p);

        static Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2) noexcept {return geometry::avg(p1, p2);}
        static Pnt2d avg(const Pnt2d& p1, const Pnt2d& p2, const Pnt2d& p3) {return geometry::avg(p1, p2, p3);}

        /**
         * @brief Calculates the volume of the
         */
        static real volume(const Pnt2d& p1, const Pnt2d& p2) noexcept {return geometry::volume(p1, p2);}
    };

}
#endif //TONB_GEOMETRY_PNT_2D_HXX