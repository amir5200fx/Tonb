//
// Created by amir on 30/09/2025.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_DIRECTION_2D_HXX
#define TONB_GEOMETRY_OCCT_DIRECTION_2D_HXX
#include <memory>
#include <array>

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

namespace tonb::geometry::occt {
    class Axis2d;

    namespace core {
        struct occt_dir_2d_access;
    }
    class Direction2d {
    public:
        Direction2d() noexcept = default;

        TNBGEOM_EXPORT Direction2d(real u, real v);
        explicit TNBGEOM_EXPORT Direction2d(const std::array<real, 2>& cmpts);

        // Value semantics
        Direction2d(const Direction2d&) noexcept = default;
        Direction2d(Direction2d&&) noexcept = default;
        Direction2d& operator=(const Direction2d&) noexcept = default;
        Direction2d& operator=(Direction2d&&) noexcept = default;

        // queries
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        TNBGEOM_ND_EXPORT std::array<real, 2> components() const noexcept;
        TNBGEOM_ND_EXPORT real u() const noexcept;
        TNBGEOM_ND_EXPORT real v() const noexcept;

        TNBGEOM_ND_EXPORT real angle(const Direction2d& other) const;

        TNBGEOM_ND_EXPORT bool is_equal(const Direction2d& other, real angular_tol) const;

        TNBGEOM_ND_EXPORT Direction2d mirrored(const Axis2d& ax) const;
        TNBGEOM_ND_EXPORT Direction2d rotated(real ang_rad) const;

        TNBGEOM_EXPORT void mirror(const Axis2d& ax);
        TNBGEOM_EXPORT void rotate(real ang_rad);
        TNBGEOM_EXPORT void reverse();

    private:
        struct Impl;
        std::shared_ptr<Impl> pimpl_;
        static bool s_valid(const std::shared_ptr<Impl>&) noexcept;

        explicit Direction2d(std::shared_ptr<Impl> p) noexcept : pimpl_(std::move(p)) {}

        friend struct core::occt_dir_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_DIRECTION_2D_HXX