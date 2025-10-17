//
// Created by amir on 8/26/25.
//

#ifndef TONB_GEOMETRY_OCCT_CURVE_2D_HXX
#define TONB_GEOMETRY_OCCT_CURVE_2D_HXX

#include <memory>
#include <optional>
#include <array>
#include <vector>

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/geometry/occt/point_2d.hxx>

namespace tonb::geometry::occt {
    // Forward Declarations
    class Axis2d;
    class Point2d;
    namespace core {
        struct occt_curve_2d_access;
    }

    class Curve2d {
    public:

        // default constructor
        Curve2d() noexcept = default;

        // Value semantics
        Curve2d(const Curve2d&) noexcept = default;
        Curve2d(Curve2d&&) noexcept = default;
        Curve2d& operator=(const Curve2d&) noexcept = default;
        Curve2d& operator=(Curve2d&&) noexcept = default;

        // Public functions and operators

        /// True if this handle references a real backend curve.
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Is the curve closed (end points coincide)?
        TNBGEOM_ND_EXPORT bool is_closed() const noexcept;

        /// Is the curve periodic?
        TNBGEOM_ND_EXPORT bool is_periodic() const noexcept;

        TNBGEOM_ND_EXPORT bool is_bspline() const noexcept;
        TNBGEOM_ND_EXPORT int nb_poles() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<Point2d> poles() const noexcept;
        TNBGEOM_ND_EXPORT Point2d pole(int index) const noexcept;

        TNBGEOM_ND_EXPORT bool is_nurbs() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<real> weights() const noexcept;
        TNBGEOM_ND_EXPORT real weight(int index) const;

        TNBGEOM_ND_EXPORT std::vector<real> knots() const noexcept;
        TNBGEOM_ND_EXPORT std::vector<int> multiplicities() const noexcept;

        /// Polynomial/spline degree if known; otherwise returns -1.
        TNBGEOM_ND_EXPORT int degree() const noexcept;

        /// Parameter range if the curve is bounded. std::nullopt if unbounded.
        TNBGEOM_ND_EXPORT std::optional<std::pair<real, real>> parameter_range() const noexcept;
        TNBGEOM_ND_EXPORT real first_parameter() const noexcept;
        TNBGEOM_ND_EXPORT real last_parameter() const noexcept;

        /// Evaluate point at parameter u
        TNBGEOM_ND_EXPORT std::array<real, 2> value(real u) const;

        /// Evaluate point and first derivative at u.
        struct D1{std::array<real, 2> p{}; std::array<real, 2> v{};};
        TNBGEOM_ND_EXPORT D1 d1(real u) const;

        /// Returns a trimmed sub-curve [u0, u1]. If not supported, returns invalid.
        TNBGEOM_ND_EXPORT Curve2d trimmed(real u0, real u1) const;
        TNBGEOM_ND_EXPORT Curve2d bspline() const;

        TNBGEOM_ND_EXPORT Curve2d mirrored(const Axis2d&) const;
        TNBGEOM_ND_EXPORT Curve2d mirrored(const Point2d&) const;

        TNBGEOM_ND_EXPORT Curve2d reversed() const;
        TNBGEOM_EXPORT void reverse() const;

        struct MinDistanceProjected {Point2d point; real parameter;};
        TNBGEOM_ND_EXPORT MinDistanceProjected project(const Point2d&) const;

        TNBGEOM_ND_EXPORT double calc_length() const;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Curve2d(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_curve_2d_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_CURVE_2D_HXX