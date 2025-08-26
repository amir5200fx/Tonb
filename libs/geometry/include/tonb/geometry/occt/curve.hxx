/**
* @file
 * @brief Kernel-agnostic geometric curve wrapper.
 *
 * `tonb::geometry::Curve` wraps a backend curve (OCCT Geom_Curve when
 * TONB_WITH_OCCT=ON). The header is OCCT-free; implementation lives in .cxx.
 *
 * Default-constructed curves are invalid. Methods that query geometry assume
 * `is_valid()==true`.
 */
#pragma once
#ifndef TONB_GEOMETRY_OCCT_CURVE_HXX
#define TONB_GEOMETRY_OCCT_CURVE_HXX

#include <memory>
#include <optional>
#include <array>

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

namespace tonb::geometry::occt {
    namespace core {
        struct occt_curve_access;
    }
    class Curve {
    public:

        // default constructor
        Curve() noexcept = default;

        // Value semantics
        Curve(Curve const&) noexcept = default;
        Curve(Curve&&) noexcept = default;
        Curve& operator=(Curve const&) noexcept = default;
        Curve& operator=(Curve&&) noexcept = default;

        // Public functions and operators

        /// True if this handle references a real backend curve.
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Is the curve closed (end points coincide)?
        TNBGEOM_ND_EXPORT bool is_closed() const noexcept;

        /// Is the curve periodic?
        TNBGEOM_ND_EXPORT bool is_periodic() const noexcept;

        /// Polynomial/spline degree if known; otherwise returns -1.
        TNBGEOM_ND_EXPORT int degree() const noexcept;

        /// Parameter range if the curve is bounded. std::nullopt if unbounded.
        TNBGEOM_ND_EXPORT std::optional<std::pair<real, real>> parameter_range() const;

        /// Evaluate point at parameter u
        TNBGEOM_ND_EXPORT std::array<real, 3> value(double u) const;

        /// Evaluate point and first derivative at u.
        struct D1{std::array<real, 3> p{}; std::array<real, 3> q{}; std::array<real, 3> v{};};
        TNBGEOM_ND_EXPORT D1 d1(double u) const;

        /// Returns a trimmed sub-curve [u0, u1]. If not supported, returns invalid.
        TNBGEOM_ND_EXPORT Curve trimmed(double u0, double u1) const;

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Curve(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        friend struct core::occt_curve_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_CURVE_HXX