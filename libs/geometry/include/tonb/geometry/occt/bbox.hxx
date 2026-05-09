#pragma once
#ifndef TONB_GEOMETRY_OCCT_BBOX_HXX
#define TONB_GEOMETRY_OCCT_BBOX_HXX

#include <tonb/geometry/module.hxx>
#include <tonb/geometry/meta/box_3d_fwd.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>
#include <utility>

/**
 * @file
 * @brief Axis-aligned bounding box wrapper.
 *
 * `tonb::geometry::BBox` is a small value-type wrapper around a backend
 * bounding box. When built with TONB_WITH_OCCT=ON, it owns an OpenCascade
 * `Bnd_Box` internally. When TONB_WITH_OCCT=OFF, it falls back to a minimal
 * numeric representation. The public API is stable across both modes.
 *
 * - Default-constructed boxes are **void/empty**.
 * - Adding points or other boxes expands the bounds.
 * - `min()` and `max()` return finite values only if the box is not empty.
 *
 * No OpenCascade headers are included by this file.
 */

namespace tonb::geometry::occt {

    class BBox {
    public:

        /// Construct an empy (void) box.
        TNBGEOM_EXPORT BBox() noexcept;

        /// Factory from min/max corners (marks box as non-empty).
        static TNBGEOM_EXPORT BBox from_min_max(const std::array<real, 3>& mn, const std::array<real, 3>& mx) noexcept;

        /// True if the box contains no volume and no finite bounds.
        TNBGEOM_ND_EXPORT bool empty() const noexcept;

        /// Reset to empty state
        TNBGEOM_EXPORT void clear() noexcept;

        /// Expand by a point.
        TNBGEOM_EXPORT void add(real x, real y, real z) noexcept;
        TNBGEOM_EXPORT void add(const std::array<real, 3>& p) noexcept;

        /// Expand by another box.
        TNBGEOM_EXPORT void add(const BBox& other) noexcept;

        /// Get (min, max). For empty boxed the values are unspecified.
        TNBGEOM_ND_EXPORT std::array<real, 3> min() const noexcept;
        TNBGEOM_ND_EXPORT std::array<real, 3> max() const noexcept;

        /// Optional convenience: expand uniformly by a non-negative margin.
        TNBGEOM_EXPORT void expand(double delta) const noexcept;

        /// Optional: set OCCT gat if available; otherwise no-op.
        TNBGEOM_EXPORT void set_gap(double gap) const noexcept;

        /// Snapshot conversion: constructs and returns tonb custom box
        TNBGEOM_ND_EXPORT meta::Box3d to_box() const noexcept;

    private:
        struct Impl;
        std::shared_ptr<Impl> p_;

        explicit BBox(std::shared_ptr<Impl> p) : p_(std::move(p)) {}

        // Allow internal helpers to access Impl when needed (same TU).
        friend struct bbox_access;
    };
}
#endif //TONB_GEOMETRY_OCCT_BBOX_HXX