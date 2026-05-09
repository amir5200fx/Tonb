//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_VECTOR_2D_HXX
#define TONB_GEOMETRY_OCCT_VECTOR_2D_HXX
/**
 * @file
 * @brief Kernel-agnostic 2D vector (u, v), wrapper over gp_Vec2D when available.
 *
 * - Default vector is (0,0).
 * - Public header is OCCT-free; OCCT is only used in .cxx.
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>

namespace tonb::geometry::occt {

    // Forward Declarations
    class Point2d;
    class Transform2d;
    namespace core {
        struct occt_vector_2d_access;
    }

    class Vector2d {
    public:

        TNBGEOM_EXPORT Vector2d() noexcept;
        TNBGEOM_EXPORT Vector2d(real u, real v) noexcept;
        explicit Vector2d(const std::array<real, 2>& v) noexcept : Vector2d(v[0], v[1]) {}

        // Value semantics
        Vector2d(const Vector2d&) noexcept = default;
        Vector2d(Vector2d&&) noexcept = default;
        Vector2d& operator=(const Vector2d&) noexcept = default;
        Vector2d& operator=(Vector2d&&) noexcept = default;

        // Construction helpers
        static TNBGEOM_EXPORT Vector2d from_points(const Point2d& p0, const Point2d& p1) noexcept;

        // Accessors
        TNBGEOM_ND_EXPORT real u() const noexcept;
        TNBGEOM_ND_EXPORT real v() const noexcept;

        TNBGEOM_EXPORT Vector2d& set_u(real v) noexcept;
        TNBGEOM_EXPORT Vector2d& set_v(real v) noexcept;

        TNB_NODISCARD std::array<real, 2> uv() const noexcept {return {u(), v()};}

        // Norms
        TNBGEOM_ND_EXPORT real squared_norm() const noexcept;
        TNBGEOM_ND_EXPORT real norm() const noexcept;
        TNBGEOM_ND_EXPORT bool is_zero(real eps = 1.e-15) const noexcept;

        // Arithmetic (return new vectors; original unchanged)
        TNBGEOM_ND_EXPORT Vector2d normalized(real eps = 1.e-15) const noexcept;
        TNBGEOM_ND_EXPORT Vector2d scaled(real scale) const noexcept;
        TNBGEOM_ND_EXPORT Vector2d negated() const noexcept;
        TNBGEOM_ND_EXPORT Vector2d added(const Vector2d& other) const noexcept;
        TNBGEOM_ND_EXPORT Vector2d subtracted(const Vector2d& other) const noexcept;

        // Products
        TNBGEOM_ND_EXPORT real dot(const Vector2d& other) const noexcept;
        TNBGEOM_ND_EXPORT real cross(const Vector2d& other) const noexcept;

        // Transform by an affine transform (ignores translation)
        TNBGEOM_ND_EXPORT Vector2d transformed(const Transform2d& t) const noexcept;

    private:

        /*Private Data*/

        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Vector2d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_vector_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_VECTOR_2D_HXX