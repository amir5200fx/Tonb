//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_TRANSFORM_2D_HXX
#define TONB_GEOMETRY_OCCT_TRANSFORM_2D_HXX

/**
 * @file
 * @brief Kernel-agnostic rigid/affine transform (translation, rotation, uniform scale).
 *
 * Wraps OCCT gp_Trsf2d when TONB_WITH_OCCT=ON. Default is identity.
 * Public header is OCCT-free.
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <memory>

namespace tonb::geometry::occt {

    // Forward Declarations
    class Point2d;
    class Axis2d;
    namespace core {
        struct occt_trsf_2d_access;
    }

    class Transform2d {
    public:

        TNBGEOM_EXPORT Transform2d() noexcept;

        // factories
        static TNBGEOM_EXPORT Transform2d identity() noexcept;
        static TNBGEOM_EXPORT Transform2d from_translation(real dx, real dy) noexcept;
        static TNBGEOM_EXPORT Transform2d from_rotation(const Axis2d&, real radians) noexcept;
        static TNBGEOM_EXPORT Transform2d from_uniform_scale(const Point2d& center, real scale) noexcept;

        // queries
        TNBGEOM_ND_EXPORT bool is_identity() const noexcept;

        // algebra
        TNBGEOM_ND_EXPORT Transform2d multiplied(const Transform2d& other) const noexcept;
        TNBGEOM_ND_EXPORT Transform2d inverse() const noexcept;

        // application
        TNBGEOM_ND_EXPORT Point2d transform_point(const Point2d& p) const noexcept;
        TNBGEOM_ND_EXPORT Axis2d transform_axis(const Axis2d&) const noexcept;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Transform2d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_trsf_2d_access;
    };
}

#endif //TONB_GEOMETRY_OCCT_TRANSFORM_2D_HXX