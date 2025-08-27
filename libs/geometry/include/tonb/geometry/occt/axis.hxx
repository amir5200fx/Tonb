//
// Created by amir on 8/24/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_AXIS_HXX
#define TONB_GEOMETRY_OCCT_AXIS_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <memory>

/**
 * @file
 * @brief Kernel-agnostic 3D axis (origin + unit direction).
 *
 * `tonb::geometry::occt::Axis` wraps a backend axis (OCCT gp_Ax1 when
 * TONB_WITH_OCCT=ON). Default axis is Z+ at the origin.
 *
 * - Public header is OCCT-free.
 * - Value semantics; copies share an internal Impl.
 * - If constructed with a near-zero direction, the axis becomes invalid.
 */

namespace tonb::geometry::occt {

    // Forward Declarations
    class Vector;
    class Point;
    class Transform;
    namespace core {
        struct occt_axis_access;
    }

    class Axis {
    public:

        /// Default: origin=(0,0,0), dir(0,0,1), valid = true.
        TNBGEOM_EXPORT Axis() noexcept;

        /// Factory from point and direction; direction will be normalized
        /// if |dir| ~ 0, returns an invalid axis.
        static Axis from_point_dir(const Point& origin, const Vector& dir) noexcept;

        /// True if the direction is non-zero (i.e., axis is meaningful).
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Origin (point).
        TNBGEOM_ND_EXPORT Point origin() const noexcept;

        /// Unit direction (vector). Undefined if !is_valid() (returns {0,0,0}).
        TNBGEOM_ND_EXPORT Vector direction() const noexcept;

        /// Returns a copy with a new origin.
        TNBGEOM_ND_EXPORT Axis with_origin(const Point& origin) const noexcept;

        /// Returns a copy with a new direction (re-normalized).
        /// If |dir| ~ 0, result is invalid
        TNBGEOM_ND_EXPORT Axis with_direction(const Vector& dir) const noexcept;

        /// Translate by delta.
        TNBGEOM_ND_EXPORT Axis moved(const Vector& delta) const;

        /// Reverse direction (origin unchanged).
        TNBGEOM_ND_EXPORT Axis reversed() const;

        /// Transformed
        TNBGEOM_ND_EXPORT Axis transformed(const Transform& t) const;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Axis(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        // Interop friend will construct/extract Impl safely.
        friend struct core::occt_axis_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_AXIS_HXX