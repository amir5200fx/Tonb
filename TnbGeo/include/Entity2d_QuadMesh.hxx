#pragma once
#ifndef _Entity2d_QuadMesh_Header
#define _Entity2d_QuadMesh_Header

#include <Entity2d_QuadMeshFwd.hxx>
#include <Entity_StaticData.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{
	template <>
	TnbGeo_EXPORT void Entity2d_QuadMesh::ExportToPlt(OFstream& File) const;

}

#endif // _Entity2d_QuadMesh_Header
