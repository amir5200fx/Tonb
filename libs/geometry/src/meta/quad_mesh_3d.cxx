//
// Created by amir on 8/28/25.
//
#include <tonb/geometry/meta/quad_mesh_3d.hxx>

#include <tonb/io/vtk/mesh_writer.hxx>

namespace tonb::geometry::meta {
    template<>
    void QuadMesh3d::export_to_vtk(const std::string& path, const bool binary) const {
        std::vector<std::array<real, 3>> xyz; xyz.reserve(this->point_count());
        for (const auto& p : this->points()) xyz.emplace_back(p.components());
        std::vector<std::array<index_t, 4>> indices; indices.reserve(this->id_count());
        for (const auto& i: this->ids()) indices.emplace_back(i.components());

        io::vtk::MeshWriter::write_quad_surface_vtp(xyz, indices, path, binary);
    }
}