#pragma once
#ifndef _GeoMesh3d_Background_Header
#define _GeoMesh3d_Background_Header

#include <GeoMesh_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <GeoMesh3d_BackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh3d_Background::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh3d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	void GeoMesh3d_Background::ExportToPlt(OFstream & File) const;
}

#endif // !_GeoMesh3d_Background_Header