//
// Created by amir on 8/22/25.
//

#ifndef TONB_GEOMETRY_PNT_3D_HXX
#define TONB_GEOMETRY_PNT_3D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <iosfwd>
#include <iostream>

#include "pnt_3d.hxx"

namespace tonb::geometry {

    // Forward Declarations
    class Pnt3d;

    TNBGEOM_ND_EXPORT Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2) noexcept;
    TNBGEOM_ND_EXPORT Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2, const Pnt3d& p3) noexcept;
    TNBGEOM_ND_EXPORT Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2, const Pnt3d& p3, const Pnt3d& p4) noexcept;
    TNBGEOM_ND_EXPORT real distance(const Pnt3d& p1, const Pnt3d& p2);
    TNBGEOM_ND_EXPORT real distance_sq(const Pnt3d& p1, const Pnt3d& p2);
    TNBGEOM_ND_EXPORT bool almost_equal(const Pnt3d& p1, const Pnt3d& p2);

    /**
     * @brief Calculates the volume of the bounding box
     */
    TNBGEOM_ND_EXPORT real volume(const Pnt3d& p1, const Pnt3d& p2) noexcept;

    class Pnt3d {
    public:
        using Array = std::array<real, 3>;
    private:
        /*Private Data*/

        Array components_{};
    public:

        // static members
        inline static constexpr int nb_cmpts = 3;
        static TNBGEOM_EXPORT const Pnt3d null;

        using ptType = Pnt3d;

        enum {
            dim = 3
        };

        // default constructor

        Pnt3d() noexcept = default;

        // constructors

        Pnt3d(const real x, const real y, const real z) noexcept : components_({x, y, z}) {}
        explicit Pnt3d(const Array& components) noexcept : components_(components) {}

        Pnt3d(const Pnt3d&) noexcept = default;
        Pnt3d(Pnt3d&&) noexcept = default;

        // Public functions and operators

        Pnt3d& operator=(const Pnt3d&) noexcept = default;
        Pnt3d& operator=(Pnt3d&&) noexcept = default;

        // Access
        TNB_NODISCARD const auto& components() const noexcept { return components_; }
        TNB_NODISCARD constexpr auto component(const size_t i) const noexcept { return components_[i]; }
        TNB_NODISCARD constexpr auto x() const noexcept { return components_[0]; }
        TNB_NODISCARD constexpr auto y() const noexcept { return components_[1]; }
        TNB_NODISCARD constexpr auto z() const noexcept { return components_[2]; }

        void set_x(const real x) noexcept { components_[0] = x; }
        void set_y(const real y) noexcept { components_[1] = y; }
        void set_z(const real z) noexcept { components_[2] = z; }

        TNB_NODISCARD constexpr const real* data() const noexcept { return components_.data(); }
        TNB_NODISCARD constexpr real* data() noexcept { return components_.data(); }

        // indexing
        TNB_NODISCARD constexpr real operator[](const size_t i) const noexcept { return components_[i]; }
        constexpr real& operator[](const size_t i) noexcept { return components_[i]; }

        TNBGEOM_ND_EXPORT constexpr real at(size_t i) const;
        TNBGEOM_EXPORT constexpr real& at(size_t i);

        // transform
        // Mutating versions:
        TNBGEOM_EXPORT Pnt3d& translate(real dx, real dy, real dz) noexcept;
        Pnt3d& scale(real s) noexcept;

        // Non-mutating convenience
        TNBGEOM_ND_EXPORT Pnt3d translated(real dx, real dy, real dz) const noexcept;
        TNBGEOM_ND_EXPORT Pnt3d scaled(real s) const noexcept;

        // io functions
        void print(std::ostream& os = std::cout) const noexcept;
        void write_to_plt(std::ostream& os = std::cout) const noexcept;

        friend std::ostream& operator<<(std::ostream& os, const Pnt3d& pnt);

        static Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2) noexcept {return geometry::avg(p1, p2);}
        static Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2, const Pnt3d& p3) noexcept {return geometry::avg(p1, p2, p3);}
        static Pnt3d avg(const Pnt3d& p1, const Pnt3d& p2, const Pnt3d& p3, const Pnt3d& p4) noexcept {return geometry::avg(p1, p2, p3, p4);}

        /**
         * @brief Calculates the volume of the
         */
        static real volume(const Pnt3d& p1, const Pnt3d& p2) noexcept {return geometry::volume(p1, p2);}
    };
}

#endif //TONB_GEOMETRY_PNT_3D_HXX