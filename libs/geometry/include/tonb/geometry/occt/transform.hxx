//
// Created by amir on 8/24/25.
//

#ifndef TONB_GEOMETRY_OCCT_TRANSFORM_HXX
#define TONB_GEOMETRY_OCCT_TRANSFORM_HXX


/**
 * @file
 * @brief Kernel-agnostic rigid/affine transform (translation, rotation, uniform scale).
 *
 * Wraps OCCT gp_Trsf when TONB_WITH_OCCT=ON. Default is identity.
 * Public header is OCCT-free.
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>

namespace tonb::geometry::occt {

    // Forward Declarations
    class Point;
    class Axis;
    namespace core {
        struct occt_trsf_access;
    }

    class Transform {
    public:
        using Mat4 = real[4][4];

        TNBGEOM_EXPORT Transform() noexcept;

        // factories
        static TNBGEOM_EXPORT Transform identity() noexcept;
        static TNBGEOM_EXPORT Transform from_translation(real dx, real dy, real dz) noexcept;
        static TNBGEOM_EXPORT Transform from_rotation(const Axis& axis, real radians) noexcept;
        static TNBGEOM_EXPORT Transform from_uniform_scale(const Point& center, real scale) noexcept;


        // queries
        TNBGEOM_ND_EXPORT bool is_identity() const noexcept;
        TNBGEOM_EXPORT void to_matrix(Mat4 out) const noexcept;

        // algebra
        TNBGEOM_ND_EXPORT Transform multiplied(const Transform& other) const noexcept;
        TNBGEOM_ND_EXPORT Transform inverse() const noexcept;

        // application
        TNBGEOM_ND_EXPORT Point transform_point(const Point& point) const noexcept;
        TNBGEOM_ND_EXPORT Axis transform_axis(const Axis& axis) const noexcept;

    private:
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Transform(std::shared_ptr<Impl> pimpl) noexcept: pimpl_(std::move(pimpl)) {}

        friend struct core::occt_trsf_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_TRANSFORM_HXX