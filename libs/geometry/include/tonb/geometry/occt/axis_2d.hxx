//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_AXIS_2D_HXX
#define TONB_GEOMETRY_OCCT_AXIS_2D_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <memory>

/**
 * @file
 * @brief Kernel-agnostic 3D axis (origin + unit direction).
 *
 * `tonb::geometry::occt::Axis2d` wraps a backend axis (OCCT gp_Ax1 when
 * TONB_WITH_OCCT=ON). Default axis is Z+ at the origin.
 *
 * - Public header is OCCT-free.
 * - Value semantics; copies share an internal Impl.
 * - If constructed with a near-zero direction, the axis becomes invalid.
 */

namespace tonb::geometry::occt {

    // Forward Declarations
    class Vector2d;
    class Point2d;
    class Transform2d;
    namespace core {
        struct occt_axis_2d_access;
    }

    class Axis2d {
    public:

        /// Default: origin=(0,0), dir(1,0), valid = true;
        TNBGEOM_EXPORT Axis2d() noexcept;

        /// Factory from point and direction; direction will be normalized
        /// if |dir| ~ 0 returns an invalid axis;
        static Axis2d from_point_dir(const Point2d& origin, const Vector2d& dir) noexcept;

        /// True if the direction is non-zero (i.e, axis is meaningful).
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Origin (point)
        TNBGEOM_ND_EXPORT Point2d origin() const noexcept;

        /// Unit direction (vector). Undefined if !is_valid() (returns {0,0})
        TNBGEOM_ND_EXPORT Vector2d direction() const noexcept;

        /// Returns a copy with a new origin.
        TNBGEOM_ND_EXPORT Axis2d with_origin(const Point2d& origin) const noexcept;

        /// Returns a copy with a new direction (re-normalized).
        /// If |dir| ~ 0, result is invalid
        TNBGEOM_ND_EXPORT Axis2d with_direction(const Vector2d& dir) const noexcept;

        /// Translate by delta.
        TNBGEOM_ND_EXPORT Axis2d moved(const Vector2d& delta) const;

        /// Reverse direction (origin unchanged).
        TNBGEOM_ND_EXPORT Axis2d reversed() const;

        /// Transformed
        TNBGEOM_ND_EXPORT Axis2d transformed(const Transform2d& t) const;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Axis2d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        // Interop friend will construct/extract Impl safely.
        friend struct core::occt_axis_2d_access;
    };
}

#endif //TONB_GEOMETRY_OCCT_AXIS_2D_HXX