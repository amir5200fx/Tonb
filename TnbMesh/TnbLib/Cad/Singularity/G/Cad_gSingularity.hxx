#pragma once
#ifndef _Cad_gSingularity_Header
#define _Cad_gSingularity_Header

#include <Cad_Singularity.hxx>
#include <Cad_gSingularityBase.hxx>
#include <Cad_gSingularityFwd.hxx>
#include <Cad_gSingularZoneFwd.hxx>

namespace tnbLib
{
	template<>
	TnbMesh_EXPORT std::shared_ptr<Cad_gSingularZone>
		Cad_gSingularity::TypeDetection
		(
			const std::shared_ptr<Entity2d_Polygon>& thePoly,
			const GeoMesh2d_Data& theBMesh,
			const std::vector<std::shared_ptr<Pln_Curve>>& theSides,
			const Geom_Surface&,
			const Standard_Real theDim
		) const;

	template<>
	TnbMesh_EXPORT std::shared_ptr<Cad_gSingularZone>
		Cad_gSingularity::TypeDetection
		(
			const std::shared_ptr<Entity2d_Polygon>& thePoly0,
			const std::shared_ptr<Entity2d_Polygon>& thePoly1,
			const GeoMesh2d_Data& theBMesh,
			const std::vector<std::shared_ptr<Pln_Curve>>& theSides,
			const Geom_Surface&,
			const Standard_Real theDim
		) const;

#ifdef _DEBUG
	template<>
	TnbMesh_EXPORT void Cad_gSingularity::Perform();
#endif // _DEBUG

}

#endif // !_Cad_gSingularity_Header
