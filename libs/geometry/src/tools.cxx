//
// Created by amir on 8/29/25.
//
#include <tonb/geometry/tools.hxx>

namespace tonb::geometry {
    index_t Tools::locate_triangle(const WalkTriMesh2dContext &ctx, index_t seed_tri, index_t p_idx) {
        assert(p_idx >= 0 && p_idx < static_cast<index_t>(ctx.P->size()));
        if (ctx.V->empty()) return -1;

        index_t t = (seed_tri >= 0 && seed_tri < static_cast<index_t>(ctx.V->size())) ? seed_tri : 0;
        const Pnt2d& p = (*ctx.P)[p_idx];

        // walk until p is inside triangle t, or we fail
        for (index_t iter=0; iter < static_cast<index_t>(ctx.V->size())*2; ++iter) {
            const auto& tri = (*ctx.V)[t];
            const Pnt2d& a = (*ctx.P)[tri[0]];
            const Pnt2d& b = (*ctx.P)[tri[1]];
            const Pnt2d& c = (*ctx.P)[tri[2]];

            const real o0 = orient(a,b,p);
            const real o1 = orient(b,c,p);
            const real o2 = orient(c,a,p);

            if (o0 >= 0 && o1 >= 0 && o2 >= 0) return t; // inside or on edges for CCW

            // choose an edge to cross. If outside across ab, go to neighbour opposite ab, etc.
            const auto& neigh = (*ctx.N)[t];
            if (o0 < 0 && neigh[2] != -1) { t = neigh[2]; continue; } // opposite ab is index 2
            if (o1 < 0 && neigh[0] != -1) { t = neigh[0]; continue; } // opposite bc is index 0
            if (o2 < 0 && neigh[1] != -1) { t = neigh[1]; continue; } // opposite ca is index 1

            // no neighbour to cross. give up
            return -1;
        }
        return -1;
    }

}