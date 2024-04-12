#pragma once
#ifndef _Mesh3d_MultiSizeMap_Header
#define _Mesh3d_MultiSizeMap_Header

#include <Mesh3d_MultiSizeMapFwd.hxx>
#include <Mesh_MultiSizeMap.hxx>
#include <GeoMesh3d_Background.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Standard_Real Mesh3d_MultiSizeMap::InterpolateAt(const Pnt3d& theCoord) const;

	template<>
	TnbMesh_EXPORT Standard_Real Mesh3d_MultiSizeMap::InterpolateAt(const Pnt3d& theCoord, Standard_Boolean& theSense) const;

	template<>
	TnbMesh_EXPORT void Mesh3d_MultiSizeMap::ConnectTopology();

	template<>
	TnbMesh_EXPORT void Mesh3d_MultiSizeMap::ExportToPlt(OFstream&) const;

	template <>
	TnbMesh_EXPORT void Mesh3d_MultiSizeMap::ExportToVtk(OFstream& File) const;

}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_MultiSizeMap);

#endif // !_Mesh3d_MultiSizeMap_Header
