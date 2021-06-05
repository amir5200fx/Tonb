#pragma once
#ifndef _GeoMesh2d_Background_Header
#define _GeoMesh2d_Background_Header

#include <GeoMesh_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	void GeoMesh2d_Background::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	void GeoMesh2d_Background::ExportToPlt(OFstream & File) const;
}

#endif // !_GeoMesh2d_Background_Header