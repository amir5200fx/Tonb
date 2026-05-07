//
// Created by amir on 8/30/25.
//
#include <tonb/geometry/triangulation/delaunay_2d.hxx>

#include "delaunator.hpp"

#include <vector>
#include <array>
#include <cmath>

using namespace tonb;
using namespace tonb::geometry;

namespace {
    // --- small helpers ---------------------------------------------------------

    inline long double orient_ld(const Pnt2d& A, const Pnt2d& B, const Pnt2d& C) {
        // signed twice area; >0 => CCW
        return static_cast<long double>(B.x() - A.x()) * (C.y() - A.y())
             - static_cast<long double>(B.y() - A.y()) * (C.x() - A.x());
    }

    // Map “opposite vertex e” to delaunator’s halfedge slot (i = 0..2) for tri t
    // Delaunator stores edges as directed: i=0: v0->v1, i=1: v1->v2, i=2: v2->v0.
    // Edge opposite local vertex 0 is (v1,v2)  -> halfedge slot 1
    // Edge opposite local vertex 1 is (v2,v0)  -> halfedge slot 2
    // Edge opposite local vertex 2 is (v0,v1)  -> halfedge slot 0
    inline index_t opp_to_halfedge_slot(index_t e) {
        static const index_t map[3] = {1, 2, 0};
        return map[e];
    }
}

triangulation::Delaunay2d::TriMesh triangulation::Delaunay2d::triangulate(
    std::span<const Pnt2d> points, triangulation::Delaunay2dOptions opt) {
    TriMesh out;

    // 0) store points (0-based)
    out.points.assign(points.begin(), points.end());
    if (out.points.size() < 3) {
        out.tris.clear();
        out.neigh.clear();
        return out;
    }

    // 1) flatten coordinates for delaunator
    std::vector<real> coords;
    coords.reserve(out.points.size() * 2);
    for (const auto& p : out.points) {
        coords.push_back(p.x());
        coords.push_back(p.y());
    }

    // 2) run delaunator
    delaunator::Delaunator d(coords);

    const std::size_t ntri = d.triangles.size() / 3;
    out.tris.resize(ntri);

    // If neighbors requested, prepare the container
    if (opt.build_neighbors) {
        out.neigh.assign(ntri, TriMesh::Tri({ -1, -1, -1 }));
    } else {
        out.neigh.clear();
    }

    // 3) copy triangles (as returned by delaunator)
    for (std::size_t t = 0; t < ntri; ++t) {
        const std::size_t base = 3 * t;
        const TriMesh::Tri T({
            static_cast<index_t>(d.triangles[base + 0]),
            static_cast<index_t>(d.triangles[base + 1]),
            static_cast<index_t>(d.triangles[base + 2])
        });
        out.tris[t] = T;
    }

    // 4) neighbors from delaunator’s halfedges (if requested)
    if (opt.build_neighbors) {
        for (std::size_t t = 0; t < ntri; ++t) {
            for (int e = 0; e < 3; ++e) {
                const int slot = opp_to_halfedge_slot(e);
                const auto k = static_cast<std::ptrdiff_t>(3 * t + slot);
                const std::ptrdiff_t h = d.halfedges[k];     // opposite halfedge or -1
                const int nb = (h >= 0) ? static_cast<int>(h / 3) : -1;
                out.neigh[t][e] = nb;                        // neighbour across edge opposite vertex e
            }
        }
    }

    // 5) (optional) enforce CCW triangle winding for robustness/readability
    //     If we swap vertices [1] and [2], also swap neighbour slots [1] and [2]
    //     so that "neigh[t][e] is across the edge opposite vertex e" stays consistent.
    if (opt.robust_predicates) {
        for (std::size_t t = 0; t < ntri; ++t) {
            auto& T = out.tris[t];
            if (orient_ld(out.points[T[0]], out.points[T[1]], out.points[T[2]]) <= 0.0L) {
                std::swap(T[1], T[2]);
                if (opt.build_neighbors) {
                    std::swap(out.neigh[t][1], out.neigh[t][2]);
                }
            }
        }
    }

    return out;
}