//
// Created by amir on 8/28/25.
//
#pragma once
#ifndef TONB_IO_VTK_MESH_READER_HXX
#define TONB_IO_VTK_MESH_READER_HXX
#include <tonb/io/module.hxx>
#include <tonb/base/index_types.hxx>
#include <tonb/base/precision.hxx>

#include <vector>
#include <array>
#include <string>

namespace tonb::io::vtk {
    class MeshReader {
    public:

        /**
         * @brief Read a quad surface mesh from a .vtp file into point and quad lists.
         *
         * @param file_path Path to the .vtp file
         * @param points    Output: list of vertex coordinates (x,y,z)
         * @param quads     Output: list of quad vertex indices (0-based)
         * @return true on success, false otherwise
         */
        static TNBIO_EXPORT bool read_quad_surface_vtp(const std::string& file_path, std::vector<std::array<real, 3>> &points, std::vector<std::array<index_t, 4>>& quads);

    };
}
#endif //TONB_IO_VTK_MESH_READER_HXX