//
// Created by amir on 30/09/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_CIRCLE_2D_HXX
#define TONB_GEOMETRY_OCCT_CIRCLE_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/geometry/occt/point_2d.hxx>
#include <tonb/base/precision.hxx>

#include <memory>
#include <optional>
#include <array>

namespace tonb::geometry::occt {
    // Forward Declarations
    class Axis22d;
    class Axis2d;
    namespace core {
        struct occt_circle_2d_access;
    }
    class Circle2D {
    public:
        Circle2D() noexcept = default;

        TNBGEOM_EXPORT Circle2D(const Point2d& centre, real radius);
        TNBGEOM_EXPORT Circle2D(const Axis22d& axis, real radius);
        TNBGEOM_EXPORT Circle2D(const Axis2d& axis, real radius, bool sense = true);

        // value semantics
        Circle2D(const Circle2D&) noexcept = default;
        Circle2D(Circle2D&&) noexcept = default;
        Circle2D& operator=(const Circle2D&) noexcept = default;
        Circle2D& operator=(Circle2D&&) noexcept = default;

        // queries
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;
        TNBGEOM_ND_EXPORT Point2d centre() const noexcept;
        TNBGEOM_ND_EXPORT Axis22d axis() const noexcept;
        TNBGEOM_ND_EXPORT real radius() const noexcept;
        TNBGEOM_ND_EXPORT real area() const noexcept;
        TNBGEOM_ND_EXPORT real length() const noexcept;

        TNBGEOM_ND_EXPORT Circle2D with_centre(const Point2d& centre) const;
        TNBGEOM_ND_EXPORT Circle2D with_radius(real radius) const;

        TNBGEOM_ND_EXPORT Circle2D mirrored(const Point2d&) const;
        TNBGEOM_ND_EXPORT Circle2D mirrored(const Axis2d&) const;
        TNBGEOM_ND_EXPORT Circle2D rotated(const Point2d& about, real angle) const;
        TNBGEOM_ND_EXPORT Circle2D scaled(const Point2d& about, real) const;
        TNBGEOM_ND_EXPORT Circle2D translated(real dx, real dy) const;

        TNBGEOM_EXPORT void mirror(const Point2d& p);
        TNBGEOM_EXPORT void mirror(const Axis2d& axis);
        TNBGEOM_EXPORT void rotate(const Point2d& about, real angle);
        TNBGEOM_EXPORT void scale(const Point2d& about, real s);
        TNBGEOM_EXPORT void translate(real dx, real dy);

    private:
        struct Impl;
        std::shared_ptr<Impl> pimpl_;
        static bool s_valid(const std::shared_ptr<Impl>&) noexcept;
        explicit Circle2D(std::shared_ptr<Impl> p) noexcept : pimpl_(std::move(p)) {}

        friend struct core::occt_circle_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_CIRCLE_2D_HXX