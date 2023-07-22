#pragma once
#ifndef _VoyageGeo_VelocityBackground_Header
#define _VoyageGeo_VelocityBackground_Header

#include <VoyageGeo_SingleVelocityBackgroundFwd.hxx>
#include <VoyageGeo_VelocityBackgroundFwd.hxx>
#include <Voyage_Module.hxx>
#include <GeoMesh_Background.hxx>
#include <GeoMesh2d_Data.hxx>
#include <Vec2d.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT void VoyageGeo_SingleVelocityBackground::ConnectTopology();

	template<>
	TnbVoyage_EXPORT Vec2d 
		VoyageGeo_SingleVelocityBackground::InterpolateAt
		(const Pnt2d& theCoord, Standard_Boolean& Sense) const;

	template<>
	void VoyageGeo_SingleVelocityBackground::HvCorrection
	(
		const std::vector<std::shared_ptr<Mesh2d_Node>>& nodes, 
		const Standard_Real Factor,
		const Standard_Integer MaxInnerIteration
	);

	template<>
	TnbVoyage_EXPORT void VoyageGeo_SingleVelocityBackground::ExportToPlt(OFstream& File) const;
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::VoyageGeo_VelocityBackground);
BOOST_CLASS_EXPORT_KEY(tnbLib::VoyageGeo_SingleVelocityBackground);

#endif // !_VoyageGeo_VelocityBackground_Header
