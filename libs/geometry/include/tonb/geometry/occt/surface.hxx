//
// Created by amir on 8/26/25.
//
#pragma once
#ifndef TONB_GEOMETRY_OCCT_SURFACE_HXX
#define TONB_GEOMETRY_OCCT_SURFACE_HXX

/**
 * @file surface.hxx
 * @brief Kernel-agnostic 3D geometric surface wrapper.
 *
 * `tonb::geometry::Surface` wraps a backend surface object
 * (OCCT Geom_Surface when TONB_WITH_OCCT=ON). The header stays OCCT-free;
 * implementation details live in the .cxx files.
 *
 * Default-constructed surfaces are invalid. Query/eval methods assume
 * `is_valid()==true`.
 */

#include <memory>
#include <optional>
#include <array>
#include <complex>

#include <tonb/geometry/module.hxx>
#include <tonb/base/precision.hxx>

namespace tonb::geometry::occt {
    namespace core {
        struct occt_surface_access;
    }
    class Surface {
    public:

        // default constructor
        Surface() noexcept = default;

        // Value semantics
        Surface(const Surface&) noexcept = default;
        Surface(Surface&&) noexcept = default;
        Surface& operator=(const Surface&) noexcept = default;
        Surface& operator=(Surface&&) noexcept = default;

        /// True if this wrapper holds a valid backend surface.
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Parameter bounds (u1, u2, v1, v2). If unbounded/unknown, returns std::nulopt.
        TNBGEOM_ND_EXPORT std::optional<std::tuple<real, real, real, real>> bounds() const noexcept;

        /// Evaluate surface point at (u,v).
        TNBGEOM_ND_EXPORT std::array<real, 3> value(real u, real v) const;

        /// Evaluate point and first partial derivatives at (u,v).
        struct D1 {
            std::array<real, 3> p{}; // point
            std::array<real, 3> du{}; // ds/du
            std::array<real, 3> dv{}; // ds/dv
        };
        TNBGEOM_ND_EXPORT D1 d1(real u, real v) const;

        /// Return a rectangularly trimmed sub-surface [u1, u2]*[v1, v2].
        /// If not supported or invalid input, returns an invalid surface.
        TNBGEOM_ND_EXPORT Surface trimmed(real u1, real u2, real v1, real v2) const;

        /// Basic topological properties (best-effort from backend).
        TNBGEOM_ND_EXPORT bool is_u_closed() const noexcept;
        TNBGEOM_ND_EXPORT bool is_v_closed() const noexcept;
        TNBGEOM_ND_EXPORT bool is_u_periodic() const noexcept;
        TNBGEOM_ND_EXPORT bool is_v_periodic() const noexcept;

        /// Periods if periodic; returns 0 if not periodic/unknown.
        TNBGEOM_ND_EXPORT real u_period() const noexcept;
        TNBGEOM_ND_EXPORT real v_period() const noexcept;

    private:
        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Surface(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        /// OCCT access shim implemented in the OCCT .cxx file.
        friend struct core::occt_surface_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_SURFACE_HXX