/* -*- C++ -*- */
/**
 * \file
 * \brief Adapters between Tonb 2D points and OpenCASCADE \c gp_Pnt2d.
 *
 * \details Provides explicit, noexcept free functions to convert
 * \c tonb::Pnt2d ⟷ \c gp_Pnt2d, plus optional scaled variants for unit handling.
 * Keep OCCT dependency confined to this header; core geometry types remain decoupled.
 *
 * \section example Example
 * \code{.cpp}
 * tonb::geometry::Pnt2d a{1.0, 2.0};
 * gp_Pnt2d   ga = tonb::occt::to_gp(a);
 *
 * gp_Pnt2d   gb(10.0, 20.0);
 * tonb::geometry::Pnt2d b = tonb::occt::from_gp(gb);
 * \endcode
 *
 * \section contracts Contracts
 * \par Thread safety
 * - Value conversions; no shared state. Concurrent calls are safe.
 * \par Exception safety
 * - All adapters are \c noexcept and perform only casts/constructors.
 *
 * \author  Tonb Project
 * \since   0.19.0
 * \ingroup tonb_geometry
 *
 * \copyright
 * Copyright (c) 2025 Tonb.
 * SPDX-License-Identifier: MIT
 */

#pragma once
#ifndef TONB_GEOMETRY_OCCT_ADAPTERS_HXX
#define TONB_GEOMETRY_OCCT_ADAPTERS_HXX

#include <tonb/config.hxx>

#if defined(TONB_HAS_OCCT_ADAPTERS)

#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/geometry/pnt_3d.hxx>
#include <opencascade/gp_Pnt2d.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/gp_Vec.hxx>
#include <opencascade/gp_Vec2d.hxx>

namespace tonb::geometry::occt::core {

    TNB_NODISCARD inline gp_Pnt2d to_gp(const Pnt2d& p) noexcept {
        return {static_cast<Standard_Real>(p[0]), static_cast<Standard_Real>(p[1])};
    }
    TNB_NODISCARD inline Pnt2d from_gp(const gp_Pnt2d& p) noexcept {
        return {static_cast<real>(p.X()), static_cast<real>(p.Y())};
    }
    TNB_NODISCARD inline std::array<real, 2> from_gp_to_array(const gp_Pnt2d& p) noexcept {
        return {static_cast<real>(p.X()), static_cast<real>(p.Y())};
    }
    TNB_NODISCARD inline std::array<real, 2> from_gp_to_array(const gp_Vec2d& v) noexcept {
        return {static_cast<real>(v.X()), static_cast<real>(v.Y())};
    }

    TNB_NODISCARD inline gp_Pnt2d make_gp_pnt2d(const std::array<real, 2>& p) noexcept {
        return {static_cast<Standard_Real>(p[0]), static_cast<Standard_Real>(p[1])};
    }

    /// Apply a unit scale (e.g. metres - millimetres)
    TNB_NODISCARD inline gp_Pnt2d to_gp_scaled(const Pnt2d& p, const Standard_Real s) noexcept {
        return {static_cast<Standard_Real>(p[0] * s), static_cast<Standard_Real>(p[1] * s)};
    }
    /// Apply a unit scale (e.g. metres - millimetres)
    TNB_NODISCARD inline Pnt2d from_gp_scaled(const gp_Pnt2d& p, const real s) noexcept {
        return {static_cast<real>(p.X() * s), static_cast<real>(p.Y() * s)};
    }

    TNB_NODISCARD inline gp_Pnt to_gp(const Pnt3d& p) noexcept {
        return {static_cast<Standard_Real>(p[0]), static_cast<Standard_Real>(p[1]), static_cast<Standard_Real>(p[2])};
    }
    TNB_NODISCARD inline gp_Pnt make_gp_pnt(const std::array<real, 3>& p) noexcept {
        return {static_cast<Standard_Real>(p[0]), static_cast<Standard_Real>(p[1]), static_cast<Standard_Real>(p[2])};
    }

    TNB_NODISCARD inline std::array<real, 3> from_gp_to_array(const gp_Pnt& p) noexcept {
        return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
    }
    TNB_NODISCARD inline std::array<real, 3> from_gp_to_array(const gp_Vec& v) noexcept {
        return {static_cast<real>(v.X()), static_cast<real>(v.Y()), static_cast<real>(v.Z())};
    }
}

#else

// No OCCT: provide declarations that are unusable (deleted)
// so including the header is harmless until you try to call them.
class gp_Pnt2d;               // forward declaration; no OCCT header needed
namespace tonb::geometry { class Pnt2d; }

namespace tonb::geometry::occt {
    gp_Pnt2d to_gp(const Pnt2d&) = delete;
    Pnt2d    from_gp(const ::gp_Pnt2d&) = delete;
}
#  pragma message("Tonb built without OCCT adapters; calls to tonb::occt::* are deleted")

#endif

#endif //TONB_GEOMETRY_OCCT_ADAPTERS_HXX