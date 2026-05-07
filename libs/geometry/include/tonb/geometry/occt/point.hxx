//
// Created by amir on 8/24/25.
//

#ifndef TONB_GEOMETRY_OCCT_POINT_HXX
#define TONB_GEOMETRY_OCCT_POINT_HXX

/**
 * @file
 * @brief Kernel-agnostic 3D point (x, y, z).
 *
 * tonb::geometry::occt::Point wraps a backend point (OCCT gp_Pnt when
 * TONB_WITH_OCCT=ON). Default is (0,0,0).
 */

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>

namespace tonb::geometry::occt {

    // Forward Declarations
    namespace core {
        struct occt_point_access;
    }
    class Point {
    public:

        /// Construct (0,0,0).
        TNBGEOM_EXPORT Point() noexcept;

        /// Construct from coordinates.
        TNBGEOM_EXPORT Point(real x, real y, real z) noexcept;

        /// Construct from array.
        explicit Point(const std::array<real, 3>& p) noexcept : Point(p[0], p[1], p[2]) {}

        // Value semantics
        Point(const Point&) noexcept = default;
        Point(Point&&) noexcept = default;
        Point& operator=(const Point&) noexcept = default;
        Point& operator=(Point&&) noexcept = default;

        // Accessors
        TNBGEOM_ND_EXPORT real x() const noexcept;
        TNBGEOM_ND_EXPORT real y() const noexcept;
        TNBGEOM_ND_EXPORT real z() const noexcept;

        TNBGEOM_EXPORT Point& set_x(real v) noexcept;
        TNBGEOM_EXPORT Point& set_y(real v) noexcept;
        TNBGEOM_EXPORT Point& set_z(real v) noexcept;

        TNBGEOM_ND_EXPORT std::array<real, 3> xyz() const noexcept;

        // Basic ops
        TNBGEOM_ND_EXPORT Point moved(const std::array<real, 3>& d) const noexcept;
        TNBGEOM_ND_EXPORT real distance(const Point& p) const noexcept;
        TNBGEOM_ND_EXPORT real distance_sq(const Point& p) const noexcept;

        /// True if all coordinated are finite numbers
        TNBGEOM_ND_EXPORT bool is_finite() const noexcept;

        /// Nearly equal within absolute tolerance.
        TNBGEOM_ND_EXPORT bool almost_equal(const Point& p, real tol) const noexcept;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Point(std::shared_ptr<Impl> pimpl) noexcept: pimpl_(std::move(pimpl)) {}

        friend struct core::occt_point_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_POINT_HXX