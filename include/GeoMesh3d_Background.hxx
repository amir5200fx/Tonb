#pragma once
#ifndef _GeoMesh3d_Background_Header
#define _GeoMesh3d_Background_Header

#include <GeoMesh_Background.hxx>
#include <GeoMesh3d_Data.hxx>
#include <GeoMesh3d_BackgroundFwd.hxx>
#include <GeoMesh3d_SingleBackgroundFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void GeoMesh3d_SingleBackground::ConnectTopology();

	template<>
	TnbMesh_EXPORT void GeoMesh3d_SingleBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh3d_Node>>& nodes,
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	TnbMesh_EXPORT void GeoMesh3d_SingleBackground::ExportToPlt(OFstream & File) const;
	template <>
	TnbMesh_EXPORT void GeoMesh3d_SingleBackground::ExportToVtk(OFstream& File) const;
	template<>
	TnbMesh_EXPORT void GeoMesh3d_SingleBackground::ExportToVtk(std::ostream&) const;
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::GeoMesh3d_Background);
BOOST_CLASS_EXPORT_KEY(tnbLib::GeoMesh3d_SingleBackground);

#endif // !_GeoMesh3d_Background_Header