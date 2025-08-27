//
// Created by amir on 8/26/25.
//
#pragma once
#ifndef TONB_CAD_OCCT_FACE_HXX
#define TONB_CAD_OCCT_FACE_HXX

/**
 * @file face.hxx
 * @brief Kernel-agnostic topological face wrapper.
 *
 * `tonb::geometry::Face` wraps a backend topological face
 * (OCCT TopoDS_Face when TONB_WITH_OCCT=ON). The header is OCCT-free;
 * implementations live in the .cxx files.
 *
 * Default-constructed faces are invalid. Query/eval methods assume
 * `is_valid()==true`.
 */

#include <tonb/cad/module.hxx>
#include <tonb/base/precision.hxx>

#include <array>
#include <memory>
#include <optional>
#include <tuple>
#include <utility>

#include "tonb/geometry/module.hxx"

// Forward Declarations
namespace tonb::geometry::occt {
    class Surface;
}
namespace tonb::cad::occt {
    // Forward Declarations
    class Location;
    namespace core {
        struct occt_face_access;
    }
    class Face {
    public:

        using Surface = geometry::occt::Surface;

        // default constructor
        Face() noexcept = default;

        // Value semantics
        Face(Face const&) noexcept = default;
        Face(Face&&) noexcept = default;
        Face& operator=(Face const&) noexcept = default;
        Face& operator=(Face&&) noexcept = default;

        // Public functions and operators

        /// True if this wrapper holds a valid backend object.
        TNBCAD_ND_EXPORT bool is_valid() const noexcept;

        /// UV parameter bounds (uMin, uMax, vMin, vMax) in the face's param space.
        /// If unknown/unbounded, returns std::nullopt.
        TNBCAD_ND_EXPORT std::optional<std::tuple<real, real, real, real>> uv_bounds() const;


        TNBCAD_ND_EXPORT std::array<real, 3> value(real u, real v) const;
        /// Evaluate 3D point at given UV on the underlying surface (with face location applied).
        TNBCAD_ND_EXPORT std::array<real, 3> world_value(real u, real v) const;

        /// Unit normal at UV (with face location/orientation applied).
        TNBCAD_ND_EXPORT std::array<real, 3> normal(real u, real v) const;

        /// Orientation flags (best-effort if backend is available).
        TNBCAD_ND_EXPORT bool is_forward() const noexcept;
        TNBCAD_ND_EXPORT bool is_reversed() const noexcept;

        /**
         * @brief Produce a *new* surface whose geometry has the face location baked in.
         *
         * @param face A topological face.
         * @return Handle(Geom_Surface) transformed into world space, or null if input invalid.
         *
         * @warning This **duplicates** the geometric object (copy-on-write semantics in OCCT).
         * Consider using the pair (surface, location) instead if you’ll evaluate many faces
         * or want to keep geometry sharing.
         */
        TNBCAD_ND_EXPORT Surface world_surface() const;
        /**
         * @brief Retrieve the underlying geometric surface of a face and its accumulated location.
         *
         * @param face A topological face. May be Null.
         * @return (Handle(Geom_Surface), TopLoc_Location)
         *
         * @note
         * - The returned `Geom_Surface` is the **unlocated** geometry.
         * - The returned `TopLoc_Location` is the **accumulated placement** for this face
         *   (including any instance/assembly transforms). You must apply it when you want
         *   world-space evaluation.
         * - Face orientation (`TopAbs_FORWARD` / `TopAbs_REVERSED`) is **not** encoded in
         *   the location; if you compute normals, handle orientation separately.
         * - The returned surface can be a basis surface of a trimmed face; use
         *   `BRepTools::UVBounds(face, ...)` for the face’s param bounds.
         *
         *   Always check s.IsNull() before use.
         */
        TNBCAD_ND_EXPORT std::pair<Surface, Location> surface() const;

    private:
        /*Private Data*/
        struct Impl;
        std::shared_ptr<Impl> pimpl_;

        explicit Face(std::shared_ptr<Impl> pimpl) noexcept : pimpl_(std::move(pimpl)) {}

        // OCCT access shim implemented in the OCCT helper file
        friend struct core::occt_face_access;
    };
}
#endif //TONB_CAD_OCCT_FACE_HXX