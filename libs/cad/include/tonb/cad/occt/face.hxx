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
#include <string>

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

        // Constructors
        explicit TNBCAD_EXPORT Face(const Surface&, real tol = 1.e-6);

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

        /**
         * @brief Export this face to an IGES file in B-Rep mode.
         *
         * Writes the current face as IGES using OCCT's writer in B-Rep mode.
         * Units are tagged in teh file header according to @param unit . The function
         * is non-throwing; OCCT and standard exceptions are caught internally and a
         * boolean status is returned.
         *
         * @param file_name Output file path (e.g. "part.iges" or "part.igs").
         * @param unit      Units string for the IGES header, for example "MM", "M" or "IN".
         *                  Defaults to "MM".
         *
         * @return  true on successful transfer and write, false otherwise.
         *
         * @note
         * - The export operates on the topological face, so any location stored on the
         *   shape is taken into account by the writer.
         * - This function focuses on geometry and topology. Per-face colour, layers,
         *   and names requires an XDE route and are not included here.
         * - The implementation uses try-catch around OCCT calls and will not throw.
         */
        TNBCAD_ND_EXPORT bool export_iges(const std::string& file_name, const std::string& unit = "MM") const;
        /**
         * @brief Export this face to a STEP file using the AP242 schema.
         *
         * Writes the current face to STEP (AP242). Diagnostic information and any error
         * description are returned via @p msg. The function is non-throwing;
         * OCCT and standard exceptions are caught internally and a boolean status is
         * required.
         *
         * @param file_name Output file path (e.g. "part.step" or "part.stp").
         * @param msg       Output string that receives a short status or error message.
         *                  It is cleared and then written by the function.
         *
         * @return true on successful transfer and write, false otherwise. On failure,
         *         @p msg contains a brief reason if available.
         *
         * @note
         * - Geometry and topology of the face are exported. If colour, layers, names,
         *   or other product-structure metadata are required, prefer an XDE-based
         *   writer.
         * - Shape location is respected by the writer, so the exported placement
         *   matches the face's current location in the model.
         * - The implementation uses try-catch around OCCT calls and will not throw.
         */
        TNBCAD_ND_EXPORT bool export_step_AP242(const std::string& file_name, std::string& msg) const;

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