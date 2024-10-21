#pragma once
#ifndef _Entity3d_QuadMesh_Header
#define _Entity3d_QuadMesh_Header

#include <Entity3d_QuadMeshFwd.hxx>
#include <Entity_StaticData.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{
	template <>
	TnbGeo_EXPORT void Entity3d_QuadMesh::ExportToPlt(OFstream& File) const;
	template <>
	TnbGeo_EXPORT void Entity3d_QuadMesh::ExportToVtk(std::fstream&) const;


}

#endif