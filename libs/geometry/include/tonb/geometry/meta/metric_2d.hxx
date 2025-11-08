//
// Created by amir on 11/8/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_METRIC_2D_HXX
#define TONB_GEOMETRY_META_METRIC_2D_HXX
/**
 * @file metric_2d.hxx
 * @brief 2D symmetric metric tensor utilities for anisotropic sizing in Tonb.
 *
 * Provides a lightweight 2x2 SPD metric representation with construction from
 * isotropic/aniso sized, rotation, eigen decomposition, inverse, and core
 * quadratic from operations. Intended for meshing, distance measures, and
 * curvature/sizing driven geometry processing.
 *
 * Conventions:
 *  - G is SPD when used as a metric.
 *  - For sizing fields, λi = 1 / hi^2 with principal sizes h1 ≥ h2.
 */
#include <tonb/base/precision.hxx>
#include <tonb/system/module.hxx>

#include <cmath>
namespace tonb::geometry::meta {
    /**
     * @brief 2D symmetric metric tensor G = [[a, b], [b, c]].
     *
     * A positive-definite metric encodes anisotropic sizing/measure in 2D.
     * Commonly for meshing:
     *  G = R(θ)^T * diag(λ1, λ2) * R(θ),  with  λi = 1 / hi^2  (hi: target lengths).
     *
     * Key utilities:
     *  - determinant/trace, SPD tests
     *  - inverse metric
     *  - metric length of a vector
     *  - eigenvalues/axes and rotation helpers
     *  - canonical constructors from sizes (isotropic, anisotropic)
     */
    class Metric2d {
    public:
        Metric2d(const real a, const real b, const real c) : a_(a), b_(b), c_(c) {}

        /// Identity metric (unit circle).
        static constexpr Metric2d identity() noexcept {return {1, 0, 1};}

        /// Isotropic size: h -> l = 1/h^2 (return diag(l, l)).
        static constexpr Metric2d from_isotropic(const real h) noexcept {
            return {inv_sq(h), 0, inv_sq(h)};
        }

        /// From principal sizes (h1, h2) and orientation θ (radians).
        /// λi = 1/hi^2; G = R^T diag(λ1, λ2) R.
        static Metric2d from_axes(const real h1, const real h2, const real theta) noexcept {
            const real l1 = inv_sq(h1);
            const real l2 = inv_sq(h2);
            const real c = std::cos(theta), s = std::sin(theta);
            // R = [c -s; s c]; G = R^T diag(l1,l2) R
            const real a = l1*c*c + l2*s*s;
            const real b = (l1 - l2)*s*c;
            const real c22 = l1*s*s + l2*c*c;
            return {a, b, c22};
        }

        /// From eigenvalues (λ1, λ2) and orientation θ (radians).
        static Metric2d from_eigs(const real lambda1, const real lambda2, const real theta) noexcept {
            const real c = std::cos(theta), s = std::sin(theta);
            const real a = lambda1*c*c + lambda2*s*s;
            const real b = (lambda1 - lambda2)*s*c;
            const real c22 = lambda1*s*s + lambda2*c*c;
            return {a, b, c22};
        }

        // -------- accessors --------
        TNB_NODISCARD real a() const {return a_;}
        TNB_NODISCARD real b() const {return b_;}
        TNB_NODISCARD real c() const {return c_;}

        void set_a(const real a) {a_ = a;}
        void set_b(const real b) {b_ = b;}
        void set_c(const real c) {c_ = c;}
        void set(const real a, const real b, const real c) {a_ = a; b_ = b; c_ = c;}

        // -------- basic invariants --------
        TNB_NODISCARD constexpr real determinant() const noexcept {return a_*c_ - b_*b_;}
        TNB_NODISCARD constexpr real trace() const noexcept {return a_ + c_;}

        /// Singular if |det| < eps.
        TNB_NODISCARD bool is_spd(const real eps = static_cast<real>(1e-12)) const noexcept {
            return (a_ > eps) && (determinant() > eps);
        }

        // -------- inverse --------
        /// Inverse metric (no check). Caller should ensure !is_singular().
        TNB_NODISCARD Metric2d inverse() const noexcept {
            const real det = determinant();
            const real inv = static_cast<real>(1) / det;
            return {c_ * inv, -b_ * inv, a_ * inv};
        }

        // -------- metric operations --------
        /// Quadratic form v^T G v for v=(x,y).
        TNB_NODISCARD constexpr real quad(const real x, const real y) const noexcept {
            return a_*x*x + 2*b_*x*y + c_*y*y;
        }

        /// Metric length ||v||_G = sqrt(v^T G v). Returns 0 for (0,0).
        TNB_NODISCARD real norm(const real x, const real y) const noexcept {
            const real q = quad(x,y);
            return (q <= 0) ? static_cast<real>(0) : std::sqrt(q);
        }

        /// Apply rotation R(θ): returns R^T G R (i.e., re-express metric in rotated frame).
        TNB_NODISCARD Metric2d rotate(const real theta) const noexcept {
            const real ct = std::cos(theta), st = std::sin(theta);
            // Compute R^T G R
            // R = [ct -st; st ct], R^T G R yields:
            const real a2 = a_*ct*ct + 2*b_*ct*st + c_*st*st;
            const real b2 = (c_ - a_)*st*ct + b_*(ct*ct - st*st);
            const real c2 = a_*st*st - 2*b_*st*ct + c_*ct*ct;
            return {a2, b2, c2};
        }

        // -------- spectral helpers --------
        /// Eigenvalues (λmax, λmin) — numerically stable 2×2 formula.
        TNB_NODISCARD std::pair<real, real> eigenvalues() const noexcept {
            const real tr = trace();
            const real disc = std::sqrt(std::max<real>(0, tr*tr - 4*determinant()));
            const real lmax = static_cast<real>(0.5)*(tr + disc);
            const real lmin = static_cast<real>(0.5)*(tr - disc);
            return {lmax, lmin};
        }

        /// Principal axis angle θ in radians (0.5*atan2(2b, a-c)).
        TNB_NODISCARD real principal_angle() const noexcept {
            return static_cast<real>(0.5) * std::atan2(2*b_, a_ - c_);
        }

        /// Condition number κ = λmax/λmin (∞ if λmin ~ 0).
        TNB_NODISCARD real cond(const real eps = static_cast<real>(1e-15)) const noexcept {
            auto [lmax, lmin] = eigenvalues();
            return (lmin <= eps) ? std::numeric_limits<real>::infinity() : (lmax / lmin);
        }

        // -------- conversions to "sizes" (ellipse axes) --------
        /// Unit ball axes h1,h2 with λi = 1/h_i^2. Returns (h_major, h_minor) ordered by size.
        TNB_NODISCARD std::pair<real, real> axes_from_metric() const noexcept {
            auto [lmax, lmin] = eigenvalues();
            const real h_minor = (lmax > 0) ? static_cast<real>(1) / std::sqrt(lmax) : std::numeric_limits<real>::infinity();
            const real h_major = (lmin > 0) ? static_cast<real>(1) / std::sqrt(lmin) : std::numeric_limits<real>::infinity();
            return {h_major, h_minor};
        }

        // -------- clamping --------
        /// Clamp eigenvalues to [λmin, λmax] and rebuild metric.
        TNB_NODISCARD Metric2d clamp_eigs(const real lam_min, const real lam_max) const noexcept {
            auto [lmax, lmin] = eigenvalues();
            const real th  = principal_angle();
            const real L1c = std::clamp(lmax, lam_min, lam_max);
            const real L2c = std::clamp(lmin, lam_min, lam_max);
            return from_eigs(L1c, L2c, th);
        }


    private:

        static constexpr real inv_sq(const real h) noexcept {
            return (h > 0) ? static_cast<real>(1) / (h*h) : std::numeric_limits<real>::infinity();
        }
        real a_;
        real b_;
        real c_;
    };
}
#endif //TONB_GEOMETRY_META_METRIC_2D_HXX