//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_IO_VTK_MESH_WRITER_HXX
#define TONB_IO_VTK_MESH_WRITER_HXX
#include <tonb/io/module.hxx>
#include <tonb/base/precision.hxx>
#include <tonb/base/index_types.hxx>

#include <vector>
#include <array>
#include <string>
namespace tonb::io::vtk {
    using namespace tonb::base;
    class MeshWriter {
    public:
        static TNBIO_EXPORT bool write_quad_surface_vtp(const std::vector<std::array<real, 3> > &points,
                                                        const std::vector<std::array<index_t, 4> > &quads,
                                                        const std::string &file_path, bool binary = true);
    };
}
#endif //TONB_IO_VTK_MESH_WRITER_HXX