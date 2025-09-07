//
// Created by amir on 8/29/25.
//
#pragma once
#ifndef TONB_GEOMETRY_TOOLS_HXX
#define TONB_GEOMETRY_TOOLS_HXX
#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/base/index_types.hxx>

#include <vector>

namespace tonb::geometry {
    class Tools {
    public:
        /**
         * @brief 2D orientation (signed area * 2) of triangle (p0, p1, p2)
         *
         * Computes the cross product of edge (p0->p1) and (p0->p2):
         * \f[
         *      \mathrm{orient}(p0,p1,p2) =
         *      (p0_x - p1_x)(p2_y - p0_y) - (p1_y - p0_y)(p2_x - p0_x)
         * \f]
         *
         * @par Semantics
         * - Returns a positive value if the points are counter-clockwise (CCW),
         *   negative if clockwise (CW), and ~0 if collinear (within FP precision).
         * - In standard Cartesian coordinates (x right, y up), positive means CCW.
         *   If you work in screen coords (y down), the sign is interted.
         *
         * @param p0 First point of the triangle.
         * @param p1 Second point of the triangle.
         * @param p2 third point of the triangle.
         * @return The signed "twice area" value in the same units as the coordinates squared.
         */
        static inline real orient(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2);

        /**
        * @brief Robust in-circle test for 2D Delaunay edge legality.
        *
        * Tests whether point @p p lies strictly inside the circumcircle of triangle
        * (a, b, c). Assumes (a, b, c) are oriented CCW.
        *
        * Implementation detail (translated so p is at the origin):
        * det | ax ay ax²+ay² |
        *     | bx by bx²+by² |  > 0  => p is inside the circumcircle of (a,b,c)
        *     | cx cy cx²+cy² |
        *
        * The function computes the determinant in double precision and falls back
        * to long double when the value is near zero to improve robustness.
        *
        * @param[in] a Triangle vertex A (CCW).
        * @param[in] b Triangle vertex B (CCW).
        * @param[in] c Triangle vertex C (CCW).
        * @param[in] p Query point.
        * @return true if @p p is strictly inside the circumcircle of (a, b, c);
        *         false if on or outside (within tolerance).
        *
        * @warning If (a, b, c) are CW, the sign convention flips. Reorder to CCW or
        *          negate the decision logic.
        *
        * @see orient()
        *
        * @code{.cpp}
        * // Example: flip edge (a,b) shared by triangles (a,b,c) and (a,b,d)
        * if (orient(a, b, c) > 0.0 && inCircle(a, b, c, d)) {
        *   // Edge is illegal for Delaunay; perform an edge flip.
        * }
        * @endcode
        */
        static inline bool in_circle_fast(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2, const Pnt2d& p);
        static inline bool in_circle_robust(const Pnt2d& p0, const Pnt2d& p1, const Pnt2d& p2, const Pnt2d& p);

        struct WalkTriMesh2dContext {
            const std::vector<Pnt2d>* P{};
            const std::vector<std::array<index_t, 3>>* V{};
            const std::vector<std::array<index_t, 3>>* N{};
        };
        /**
         * @brief find a triangle that contains point p_idx using a walking strategy.
         *
         * @param ctx
         * @param seed_tri is a hint; if invalid, start at 0.
         * @param p_idx
         */
        static TNBGEOM_EXPORT index_t locate_triangle(const WalkTriMesh2dContext& ctx, index_t seed_tri, index_t p_idx);

        template<std::size_t N>
        static index_t local_index_of(const std::array<index_t, N>& cell, index_t v);

        static bool have_intersection(real a0, real a1, real b0, real b1);

        /** @brief 2D signed area * 2 of triangle (ax,ay)-(bx,by)-(cx,cy). */
        static real orient2d(real ax, real ay, real bx, real by, real cx, real cy) noexcept;
        /** @brief Barycentric coords of p w.r.t. triangle (a,b,c). Returns (1/3,1/3,1/3) if degenerate. */
        static std::array<real, 3> barycentric(real px, real py, real ax, real ay, real bx, real by, real cx, real cy) noexcept;

        /** @brief Inside test with tolerance. */
        static bool inside_bary(const std::array<real, 3>& w, real tol = 1.e-14) noexcept;

        /** @brief Clamp barycentrics to the nearest point on the triangle (edge/vertex if outside). */
        static std::array<real, 3> clamp_bary(const std::array<real, 3>& w) noexcept;
    };
}
#include <tonb/geometry/tools_i.hxx>
#endif //TONB_GEOMETRY_TOOLS_HXX