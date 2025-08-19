#pragma once
#ifndef _GeoMesh2d_Background_Header
#define _GeoMesh2d_Background_Header

#include <GeoMesh_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <GeoMesh2d_SingleBackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleBackground::ConnectTopology();

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleBackground::ExportToPlt(OFstream & File) const;

	template <>
	TnbMesh_EXPORT void GeoMesh2d_SingleBackground::ExportToVtk(OFstream& File) const;
	template<>
	TnbMesh_EXPORT void GeoMesh2d_SingleBackground::ExportToVtk(std::ostream& stream) const;

}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoMesh2d_Background);
BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMesh2d_SingleBackground);

#endif // !_GeoMesh2d_Background_Header