//
// Created by amir on 30/09/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_AXIS2_2D_HXX
#define TONB_GEOMETRY_OCCT_AXIS2_2D_HXX
#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/geometry/occt/point_2d.hxx>

namespace tonb::geometry::occt {
    class Axis2d;
    class Direction2d;

    namespace core {
        struct occt_axis2_2d_access;
    }

    class Axis22d {
    public:
        Axis22d() noexcept = default;

        TNBGEOM_EXPORT Axis22d(const Point2d& origin, const Direction2d& xdir, const Direction2d& ydir);
        TNBGEOM_EXPORT Axis22d(const Point2d& origin, const Direction2d& xdir, bool sense_direct = true);

        // value semantics
        Axis22d(const Axis22d&) noexcept = default;
        Axis22d(Axis22d&&) noexcept = default;
        Axis22d& operator=(const Axis22d&) noexcept = default;
        Axis22d& operator=(Axis22d&&) noexcept = default;

        // queries
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;
        TNBGEOM_ND_EXPORT Point2d origin() const noexcept;
        TNBGEOM_ND_EXPORT Axis2d x_direction() const noexcept;
        TNBGEOM_ND_EXPORT Axis2d y_direction() const noexcept;

        //bool is_direct() const noexcept;

        TNBGEOM_ND_EXPORT Axis22d with_origin(const Point2d& p) const;
        TNBGEOM_ND_EXPORT Axis22d with_x_direction(const Axis2d& x) const;
        TNBGEOM_ND_EXPORT Axis22d with_y_direction(const Axis2d& y) const;

        TNBGEOM_ND_EXPORT Axis22d mirrored(const Point2d& p) const;
        TNBGEOM_ND_EXPORT Axis22d mirrored(const Axis2d& x) const;
        TNBGEOM_ND_EXPORT Axis22d rotated(const Point2d& about, real ang_rad) const;
        TNBGEOM_ND_EXPORT Axis22d scaled(const Point2d& about, real s) const;
        TNBGEOM_ND_EXPORT Axis22d translated(real dx, real dy) const;

        TNBGEOM_EXPORT void mirror(const Point2d& p);
        TNBGEOM_EXPORT void mirror(const Axis2d& a);
        TNBGEOM_EXPORT void rotate(const Point2d& about, real ang_rad);
        TNBGEOM_EXPORT void scale(const Point2d& about, real s);
        TNBGEOM_EXPORT void translate(real dx, real dy);

    private:
        struct Impl;
        std::shared_ptr<Impl> pimpl_;
        static bool s_valid(const std::shared_ptr<Impl>& p) noexcept;

        explicit Axis22d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_axis2_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_AXIS2_2D_HXX