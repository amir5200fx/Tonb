//
// Created by amir on 8/26/25.
//
#pragma once
#ifndef TONB_CAD_OCCT_LOCATION_HXX
#define TONB_CAD_OCCT_LOCATION_HXX
/**
 * @file location.hxx
 * @brief Kernel-agnostic wrapper for placement transforms (OCCT TopLoc_Location).
 *
 * `tonb::geometry::Location` represents a rigid (or similarity) transform that can be
 * composed, inverted, and applied to points/vectors. When TONB_WITH_OCCT=ON, it stores
 * an OCCT TopLoc_Location internally; otherwise it degrades to identity behaviour so
 * code can still compile/run without OCCT.
 *
 * Notes:
 *  - Default-constructed Location is the identity.
 *  - Applying to a point includes translation; applying to a vector does not.
 */

#include <tonb/cad/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>
#include <utility>

namespace tonb::cad::occt {
    namespace core {
        struct occt_location_access;
    }

    class Location {
    public:

        // default constructor

        Location() = default;

        // Value semantics
        Location(const Location&) = default;
        Location& operator=(const Location&) = default;
        Location(Location&&) = default;
        Location& operator=(Location&&) = default;

        // Public functions and operators

        /// True if this location is the identity transform.
        TNBCAD_ND_EXPORT bool is_identity() const noexcept;

        /// Return the 4x4 row-major homogeneous matric [R|t; 0 0 0 1].
        /// If the backend cannot provide a matric (null backend), returns identity.
        TNBCAD_ND_EXPORT std::array<real, 16> matrix() const noexcept;

        /// Apply the transform to a point (translation included).
        TNBCAD_ND_EXPORT std::array<real, 3> apply_point(const std::array<real, 3>& p) const;

        /// Apply the transform to a vector (no translation).
        TNBCAD_ND_EXPORT std::array<real, 3> apply_vector(const std::array<real, 3>& v) const;

        /// Return the inverse transform.
        TNBCAD_ND_EXPORT Location inverted() const;

        /// Composition (this . rhs): first apply rhs, then this.
        TNBCAD_ND_EXPORT Location operator*(const Location& rhs) const;

        /// Compound assignment composition.
        TNBCAD_ND_EXPORT Location& operator*=(const Location& rhs);

        /// Factory: identity location.
        static Location identity() {return {};}

    private:

        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_{};  // may be null => identity in all builds

        explicit Location(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        // OCCT interop shim implemented in the OCCT helper file
        friend struct core::occt_location_access;
    };
}
#endif //TONB_CAD_OCCT_LOCATION_HXX