//
// Created by amir on 8/29/25.
//
#pragma once
#include <cmath>
namespace tonb::geometry {
    inline real Tools::orient(const Pnt2d &p0, const Pnt2d &p1, const Pnt2d &p2) {
        return (p1.x()-p0.x())*(p2.y()-p0.y()) - (p1.y()-p0.y())*(p2.x()-p0.x());
    }

    inline bool Tools::in_circle_robust(const Pnt2d &p0, const Pnt2d &p1, const Pnt2d &p2, const Pnt2d &p) {
        const double ax = p0.x() - p.x(), ay = p0.y() - p.y();
        const double bx = p1.x() - p.x(), by = p1.y() - p.y();
        const double cx = p2.x() - p.x(), cy = p2.y() - p.y();

        const double aa = ax*ax + ay*ay;
        const double bb = bx*bx + by*by;
        const double cc = cx*cx + cy*cy;

        double det = aa * (bx*cy - by*cx)
                   - bb * (ax*cy - ay*cx)
                   + cc * (ax*by - ay*bx);

        if (std::isfinite(det) && std::fabs(det) > 1e-27) return det > 0.0;

        // fallback in long double for near-degenerate cases
        const long double lax=ax, lay=ay, lbx=bx, lby=by, lcx=cx, lcy=cy;
        const long double laa=lax*lax+lay*lay, lbb=lbx*lbx+lby*lby, lcc=lcx*lcx+lcy*lcy;
        const long double ldet = laa*(lbx*lcy - lby*lcx) - lbb*(lax*lcy - lay*lcx) + lcc*(lax*lby - lay*lbx);
        return ldet > 0;
    }

    inline bool Tools::in_circle_fast(const Pnt2d &p0, const Pnt2d &p1, const Pnt2d &p2, const Pnt2d &p) {
        return in_circle_robust(p0, p1, p2, p);  // keep one path for now
    }

    template<std::size_t N>
    index_t Tools::local_index_of(const std::array<index_t, N> &cell, index_t v) {
        for (index_t iter=0; iter < static_cast<index_t>(N); ++iter) {
            if (cell[iter] == v) return iter;
        }
        return -1;
    }

    inline bool Tools::have_intersection(const real a0, const real a1, const real b0, const real b1) {
        if (a1 < b0) return false;
        if (b1 < a0) return false;
        return true;
    }

    inline real Tools::orient2d(const real ax, const real ay, const real bx, const real by, const real cx,
                                const real cy) noexcept {
        return (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    }

    inline std::array<real, 3> Tools::barycentric(const real px, const real py, const real ax, const real ay,
                                                  const real bx, const real by, const real cx, const real cy) noexcept {
        const real A2 = orient2d(ax, ay, bx, by, cx, cy);
        if (std::abs(A2) < 1e-20) return { static_cast<real>(1.0 / 3.0), static_cast<real>(1.0 / 3.0), static_cast<real>(1.0 / 3.0) };
        const real w0 = orient2d(bx, by, cx, cy, px, py) / A2;
        const real w1 = orient2d(cx, cy, ax, ay, px, py) / A2;
        const real w2 = static_cast<real>(1) - w0 - w1;
        return { w0, w1, w2 };
    }

    inline bool Tools::inside_bary(const std::array<real, 3> &w, const real tol) noexcept {
        return (w[0] >= -tol) && (w[1] >= -tol) && (w[2] >= -tol);
    }

    inline std::array<real, 3> Tools::clamp_bary(const std::array<real, 3> &w) noexcept {
        if (w[0] >= 0 && w[1] >= 0 && w[2] >= 0) return w;

        const auto x = w;
        auto proj_edge = [&](int zero) {
            const int i = (zero + 1) % 3, j = (zero + 2) % 3;
            const real sum = x[i] + x[j];
            if (sum <= 0) {
                std::array<real,3> r{0,0,0};
                r[(x[i] >= x[j]) ? i : j] = 1.0;
                return r;
            }
            const real ti = std::max<real>(0.0, std::min<real>(1.0, x[i]/sum));
            std::array<real,3> r{0,0,0}; r[i] = ti; r[j] = 1.0 - ti; return r;
        };

        const std::array<std::array<real,3>,3> cands = { proj_edge(0), proj_edge(1), proj_edge(2) };
        auto d2 = [&](const std::array<real,3>& a, const std::array<real,3>& b){
            const real d0 = a[0]-b[0], d1 = a[1]-b[1], dd2 = a[2]-b[2];
            return d0*d0 + d1*d1 + dd2*dd2;
        };
        int best = 0; real bd = d2(cands[0], x);
        for (int k = 1; k < 3; ++k) { const real dd = d2(cands[k], x); if (dd < bd) { bd = dd; best = k; } }
        return cands[best];
    }


}