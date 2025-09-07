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

#include <opencascade/TColStd_Array1OfReal.hxx>
#include <opencascade/TColStd_Array1OfInteger.hxx>
#include <opencascade/TColStd_Array2OfReal.hxx>
#include <opencascade/TColgp_Array2OfPnt.hxx>
#include <opencascade/TColgp_Array1OfPnt.hxx>
#include <opencascade/TColgp_Array1OfPnt2d.hxx>

#include <vector>

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
    TNB_NODISCARD inline Pnt3d from_gp(const gp_Pnt& p) noexcept {
        return {static_cast<real>(p.X()), static_cast<real>(p.Y()), static_cast<real>(p.Z())};
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

    TNB_NODISCARD inline TColStd_Array1OfReal to_colstd_array(const std::vector<real>& v) noexcept {
        TColStd_Array1OfReal arr(1, v.size());
        for (int i = 0; i < v.size(); ++i) {
            arr.SetValue(i + 1, v[i]);
        }
        return arr;
    }
    TNB_NODISCARD inline std::vector<real> from_colstd_array(const TColStd_Array1OfReal& arr) noexcept {
        std::vector<real> v; v.reserve(arr.Size());
        for (int i = 0; i < arr.Size(); ++i) {
            v.emplace_back(arr.Value(i + 1));
        }
        return v;
    }

    TNB_NODISCARD inline TColStd_Array1OfInteger to_colstd_array(const std::vector<int>& v) noexcept {
        TColStd_Array1OfInteger arr(1, v.size());
        for (int i = 0; i < v.size(); ++i) {
            arr.SetValue(i + 1, v[i]);
        }
        return arr;
    }
    TNB_NODISCARD inline std::vector<int> from_colstd_array(const TColStd_Array1OfInteger& arr) noexcept {
        std::vector<int> v; v.reserve(arr.Size());
        for (int i = 0; i < arr.Size(); ++i) {
            v.emplace_back(arr.Value(i + 1));
        }
        return v;
    }

    TNB_NODISCARD inline TColStd_Array2OfReal to_colstd_array2(const std::vector<std::vector<real>>& vec) {
        if (vec.empty() || vec[0].empty())
            throw std::invalid_argument("Input vector must not be empty");

        // OCC arrays allow custom bounds; we'll use 1-based indexing here
        const Standard_Integer rowLower = 1;
        const Standard_Integer rowUpper = static_cast<Standard_Integer>(vec.size());
        const Standard_Integer colLower = 1;
        const Standard_Integer colUpper = static_cast<Standard_Integer>(vec[0].size());

        // Create OCC 2D array
        TColStd_Array2OfReal occArray(rowLower, rowUpper, colLower, colUpper);

        for (Standard_Integer i = rowLower; i <= rowUpper; ++i) {
            if (vec[i - rowLower].size() != static_cast<size_t>(colUpper))
                throw std::invalid_argument("All rows must have the same number of columns");

            for (Standard_Integer j = colLower; j <= colUpper; ++j) {
                occArray(i, j) = vec[i - rowLower][j - colLower];
            }
        }
        return occArray;
    }
    TNB_NODISCARD inline std::vector<std::vector<real>> from_colstd_array2(const TColStd_Array2OfReal& arr) noexcept {
        std::vector<std::vector<double>> result;

        // Get the bounds of the OCC 2D array
        const Standard_Integer rowLower = arr.LowerRow();
        const Standard_Integer rowUpper = arr.UpperRow();
        const Standard_Integer colLower = arr.LowerCol();
        const Standard_Integer colUpper = arr.UpperCol();

        result.resize(rowUpper - rowLower + 1);

        for (Standard_Integer i = rowLower; i <= rowUpper; ++i) {
            result[i - rowLower].resize(colUpper - colLower + 1);
            for (Standard_Integer j = colLower; j <= colUpper; ++j) {
                result[i - rowLower][j - colLower] = arr(i, j);
            }
        }
        return result;
    }

    TNB_NODISCARD inline TColgp_Array2OfPnt to_colgp_array2(const std::vector<std::vector<Pnt3d>>& vec) {
        if (vec.empty() || vec[0].empty())
            throw std::invalid_argument("Input vector must not be empty");
        const Standard_Integer rowLower = 1;
        const Standard_Integer rowUpper = static_cast<Standard_Integer>(vec.size());
        const Standard_Integer colLower = 1;
        const Standard_Integer colUpper = static_cast<Standard_Integer>(vec[0].size());

        TColgp_Array2OfPnt occArray(rowLower, rowUpper, colLower, colUpper);

        for (Standard_Integer i = rowLower; i <= rowUpper; ++i) {
            if (vec[i - rowLower].size() != static_cast<size_t>(colUpper))
                throw std::invalid_argument("All rows must have the same number of columns");

            for (Standard_Integer j = colLower; j <= colUpper; ++j) {
                occArray(i, j) = to_gp(vec[i - rowLower][j - colLower]);
            }
        }
        return occArray;
    }

    TNB_NODISCARD inline std::vector<std::vector<Pnt3d>> from_colgp_array2(const TColgp_Array2OfPnt& arr) noexcept {
        std::vector<std::vector<Pnt3d>> result;

        const Standard_Integer rowLower = arr.LowerRow();
        const Standard_Integer rowUpper = arr.UpperRow();
        const Standard_Integer colLower = arr.LowerCol();
        const Standard_Integer colUpper = arr.UpperCol();

        result.resize(rowUpper - rowLower + 1);

        for (Standard_Integer i = rowLower; i <= rowUpper; ++i) {
            result[i - rowLower].resize(colUpper - colLower + 1);
            for (Standard_Integer j = colLower; j <= colUpper; ++j) {
                result[i - rowLower][j - colLower] = from_gp(arr(i, j));
            }
        }
        return result;
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