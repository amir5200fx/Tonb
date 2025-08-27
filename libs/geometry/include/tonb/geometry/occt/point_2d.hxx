//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_POINT_2D_HXX
#define TONB_GEOMETRY_OCCT_POINT_2D_HXX
/**
 * @file
 * @brief Kernel-agnostic 2D point (x, y).
 *
 * tonb::geometry::occt::Point wraps a backend point (OCCT gp_Pnt2d when
 * TONB_WITH_OCCT=ON). Default is (0,0).
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>

namespace tonb::geometry::occt {

    // Forward Declarations
    namespace core {
        struct occt_point_2d_access;
    }

    class Point2d {
    public:

        /// Construct (0,0)
        TNBGEOM_EXPORT Point2d() noexcept;

        /// Construct from coordinates.
        TNBGEOM_EXPORT Point2d(real x, real y) noexcept;

        /// Construct from array
        explicit Point2d(const std::array<real, 2>& p) noexcept : Point2d(p[0], p[1]) {}

        // Value semantics
        Point2d(const Point2d&) noexcept = default;
        Point2d(Point2d&&) noexcept = default;
        Point2d& operator=(const Point2d&) noexcept = default;
        Point2d& operator=(Point2d&&) noexcept = default;

        // Accessors
        TNBGEOM_ND_EXPORT real x() const noexcept;
        TNBGEOM_ND_EXPORT real y() const noexcept;

        TNBGEOM_ND_EXPORT Point2d& set_x(real x) noexcept;
        TNBGEOM_ND_EXPORT Point2d& set_y(real y) noexcept;

        TNBGEOM_ND_EXPORT std::array<real, 2> xy() const noexcept;

        // Basic ops
        TNBGEOM_ND_EXPORT Point2d moved(const std::array<real, 2>& d) const noexcept;
        TNBGEOM_ND_EXPORT real distance(const Point2d& p) const noexcept;
        TNBGEOM_ND_EXPORT real distance_sq(const Point2d& p) const noexcept;

        /// True if all coordinated are finite numbers
        TNBGEOM_ND_EXPORT bool is_finite() const noexcept;

        /// Nearly equal within absolute tolerance.
        TNBGEOM_ND_EXPORT bool almost_equal(const Point2d& p, real tol) const noexcept;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Point2d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_point_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_POINT_2D_HXX