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
#include <vector>
#include <complex>

#include <tonb/geometry/pnt_3d.hxx>
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

        /**
         * @brief Construct a rational or non-rational B-spline surface from explicit pole and knot data.
         *
         * This constructor creates a B-spline surface by directly specifying its control points (poles),
         * weights (for rational surfaces), knot vectors, multiplicities, and polynomial degrees in both
         * the U and V parametric directions.
         *
         * The surface is defined by the NURBS formulation:
         * \f[
         *    S(u,v) = \frac{\sum_{i=0}^{n_u} \sum_{j=0}^{n_v} N_{i,p}(u) \, M_{j,q}(v) \, w_{ij} \, P_{ij}}
         *              {\sum_{i=0}^{n_u} \sum_{j=0}^{n_v} N_{i,p}(u) \, M_{j,q}(v) \, w_{ij}}
         * \f]
         * where:
         * - \( P_{ij} \) are the control points (poles)
         * - \( w_{ij} \) are the associated weights
         * - \( N_{i,p}(u) \) and \( M_{j,q}(v) \) are B-spline basis functions of degree \( p \) and \( q \)
         *   defined over the respective knot vectors.
         *
         * @param poles      2D array of control points, organised as [U index][V index].
         *                   Dimensions must match the number of poles implied by knot vectors and degrees.
         *                   Each point is specified in 3D space.
         * @param weights    2D array of control point weights (same dimensions as `poles`).
         *                   For non-rational surfaces, all values can be set to 1.0.
         * @param u_knots    Knot vector in the U direction (non-decreasing sequence).
         *                   Length must be `#poles_U + u_deg + 1 - sum(u_mults) + 1` according to OCC rules.
         * @param v_knots    Knot vector in the V direction (non-decreasing sequence).
         * @param u_mults    Multiplicity values for each knot in the U direction.
         *                   Length must match `u_knots.size()`.
         * @param v_mults    Multiplicity values for each knot in the V direction.
         * @param u_deg      Degree of the B-spline basis functions in the U direction (p in N_{i,p}).
         * @param v_deg      Degree of the B-spline basis functions in the V direction (q in M_{j,q}).
         *
         * @note This constructor does not perform full shape validation; the caller must ensure that
         *       the pole array, weights, knot vectors, and multiplicities are consistent with each other
         *       and with the specified degrees. If the weights are not all equal to 1.0, the surface
         *       will be treated as a NURBS surface.
         * @throws std::invalid_argument if array dimensions are inconsistent or empty.
         *
         */
        TNBGEOM_EXPORT Surface(const std::vector<std::vector<Pnt3d> > &poles,
                              const std::vector<std::vector<real> > &weights, const std::vector<real> &u_knots,
                              const std::vector<real> &v_knots, const std::vector<int> &u_mults,
                              const std::vector<int> &v_mults, int u_deg, int v_deg);

        // Value semantics
        Surface(const Surface&) noexcept = default;
        Surface(Surface&&) noexcept = default;
        Surface& operator=(const Surface&) noexcept = default;
        Surface& operator=(Surface&&) noexcept = default;

        /// True if this wrapper holds a valid backend surface.
        TNBGEOM_ND_EXPORT bool is_valid() const noexcept;

        /// Parameter bounds (u1, u2, v1, v2). If unbounded/unknown, returns std::nullopt.
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

        struct QuadMesh {
            std::vector<Pnt3d> points;                     // vertex positions (row-major: v changes slowest)
            std::vector<std::array<int, 4>> quads;         // each quad as {i0, i1, i2, i3}
            std::vector<std::array<real, 2>> uv;           // optional (u,v) for each vertex, same order as points
        };

        /**
         * @brief Uniformly sample the parametric domain and build a quad mesh.
         *
         * @param nu  number of quads along U (>=1). Produces nu+1 vertices along U (or nu if closed).
         * @param nv  number of quads along V (>=1). Produces nv+1 vertices along V (or nv if closed).
         * @param closePeriodic  if true and the surface is periodic in U/V, do not duplicate the seam vertices.
         * @throws std::logic_error if the surface is invalid or bounds are unavailable.
         */
        TNBGEOM_ND_EXPORT QuadMesh make_uniform_quad_mesh(int nu, int nv, bool closePeriodic = true) const;

        /// Return an opaque pointer to the backend-native handle object.
        /// For OCCT builds, this is a pointer to `opencascade::handle<Geom_Surface>`.
        /// Lifetime: only valid while *this* Surface object (and its pimpl) remain alive.
        /// Returns nullptr if invalid.
        TNBGEOM_EXPORT void* native_backend_handle() noexcept;

        /// Const variant of native_backend_handle().
        TNBGEOM_ND_EXPORT const void* native_backend_handle() const noexcept;

        /// Construct a Surface from an opaque pointer obtained via native_backend_handle().
        /// For OCCT builds, `ptr` must point to a valid `opencascade::handle<Geom_Surface>`.
        /// If ptr is null, returns an invalid Surface.
        static TNBGEOM_EXPORT Surface from_native_backend_handle(const void* ptr);

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