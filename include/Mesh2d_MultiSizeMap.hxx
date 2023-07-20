#pragma once
#ifndef _Mesh2d_MultiSizeMap_Header
#define _Mesh2d_MultiSizeMap_Header

#include <Mesh2d_MultiSizeMapFwd.hxx>
#include <Mesh_MultiSizeMap.hxx>
#include <GeoMesh2d_Background.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_MultiSizeMap::InterpolateAt
	(const Pnt2d&) const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh2d_MultiSizeMap::InterpolateAt
	(
		const Pnt2d&,
		Standard_Boolean& theSense
	) const;

	template<>
	TnbMesh_EXPORT void Mesh2d_MultiSizeMap::ConnectTopology();
	template<>
	TnbMesh_EXPORT void Mesh2d_MultiSizeMap::ExportToPlt(OFstream& File) const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_MultiSizeMap);

#endif // !_Mesh2d_MultiSizeMap_Header
