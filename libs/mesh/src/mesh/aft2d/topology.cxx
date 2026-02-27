//
// Created by amir on 1/28/26.
//
#include <tonb/mesh/aft2d/topology.hxx>

namespace tonb::mesh::aft2d {
    void Mesh2D::reverse(const std::size_t n_vertices, const std::size_t n_edges, const std::size_t n_faces) {
        vertices_.reserve(n_vertices);
        edges_.reserve(n_edges);
        halfedges_.reserve(n_edges * 2);
        faces_.reserve(n_faces);
        edge_lut_.reserve(n_edges);
    }
}
