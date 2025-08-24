//
// Created by amir on 8/24/25.
//

#ifndef TONB_GEOMETRY_OCCT_VECTOR_HXX
#define TONB_GEOMETRY_OCCT_VECTOR_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>
#include <cmath>

/**
 * @file
 * @brief Kernel-agnostic 3D vector (u, v, w), wrapper over gp_Vec when available.
 *
 * - Default vector is (0,0,0).
 * - Public header is OCCT-free; OCCT is only used in .cxx.
 */

namespace tonb::geometry::occt {

    // Forward Declarations
    class Point;
    class Transform;
    namespace core {
        struct occt_vector_access;
    }

    class Vector {
    public:

        TNBGEOM_EXPORT Vector() noexcept;
        TNBGEOM_EXPORT Vector(real u, real v, real w) noexcept;
        explicit Vector(const std::array<real, 3>& v) noexcept: Vector(v[0], v[1], v[2]) {}

        // Value semantics
        Vector(const Vector&) noexcept = default;
        Vector(Vector&&) noexcept = default;
        Vector& operator=(const Vector&) noexcept = default;
        Vector& operator=(Vector&&) noexcept = default;

        // Construction helpers
        static TNBGEOM_EXPORT Vector from_points(const Point& a, const Point& b) noexcept;

        // Accessors
        TNBGEOM_ND_EXPORT real u() const noexcept;
        TNBGEOM_ND_EXPORT real v() const noexcept;
        TNBGEOM_ND_EXPORT real w() const noexcept;

        Vector& set_u(real v) noexcept;
        Vector& set_v(real v) noexcept;
        Vector& set_w(real v) noexcept;

        TNBGEOM_ND_EXPORT std::array<real, 3> uvw() const noexcept {return {u(), v(), w()};}

        // Norms
        TNBGEOM_ND_EXPORT real squared_norm() const noexcept;
        TNBGEOM_ND_EXPORT real norm() const noexcept;
        TNBGEOM_ND_EXPORT bool is_zero(real eps = 1.e-15) const noexcept;

        // Arithmetic (return new vectors; original unchanged)
        TNBGEOM_ND_EXPORT Vector normalized(real eps = 1.e-15) const noexcept;
        TNBGEOM_ND_EXPORT Vector scaled(real scale) const noexcept;
        TNBGEOM_ND_EXPORT Vector negated() const noexcept;
        TNBGEOM_ND_EXPORT Vector added(const Vector& v) const noexcept;
        TNBGEOM_ND_EXPORT Vector subtracted(const Vector& v) const noexcept;

        // Products
        TNBGEOM_ND_EXPORT real dot(const Vector& v) const noexcept;
        TNBGEOM_ND_EXPORT Vector cross(const Vector& v) const noexcept;

        // Transform by an affine transform (ignores translation)
        TNBGEOM_ND_EXPORT Vector transformed(const Transform& t) const noexcept;

    private:

        /*Private Data*/

        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Vector(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_vector_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_VECTOR_HXX