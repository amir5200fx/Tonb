//
// Created by amir on 8/29/25.
//
#pragma once
#ifndef TONB_GEOMETRY_TRIANGULATION_DELAUNAY_2D_HXX
#define TONB_GEOMETRY_TRIANGULATION_DELAUNAY_2D_HXX
#include <span>
#include <tonb/geometry/pnt_2d.hxx>
#include <tonb/geometry/meta/connectivity.hxx>

#include <vector>
#include <span>
namespace tonb::geometry::triangulation {

    struct Delaunay2dOptions {
        bool build_neighbors = true;
        bool robust_predicates = true;
    };

    class Delaunay2d {
    public:
        struct TriMesh {
            using Tri = meta::detail::Tri;
            std::vector<Pnt2d> points;      // 0-based
            std::vector<Tri> tris;          // vertex indices
            std::vector<Tri> neigh;       // -1 means boundary
        };

        static TNBGEOM_EXPORT TriMesh triangulate(std::span<const Pnt2d> points, Delaunay2dOptions opt = {});
    };
}
#endif //TONB_GEOMETRY_TRIANGULATION_DELAUNAY_2D_HXX