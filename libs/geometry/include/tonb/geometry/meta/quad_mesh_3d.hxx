//
// Created by amir on 8/27/25.
//
#pragma once
#ifndef TONB_GEOMETRY_META_QUAD_MESH_3D_HXX
#define TONB_GEOMETRY_META_QUAD_MESH_3D_HXX
#include <tonb/geometry/meta/quad_mesh_3d_fwd.hxx>
#include <tonb/geometry/meta/geometry_set.hxx>
#include <tonb/geometry/meta/connectivity.hxx>
#include <tonb/geometry/pnt_3d.hxx>

namespace tonb::geometry::meta {
    template<>
    void TNBGEOM_EXPORT QuadMesh3d::export_to_vtk(const std::string& path, bool binary) const;
}
#endif //TONB_GEOMETRY_META_QUAD_MESH_3D_HXX