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


}