#pragma once
#include <Mesh_Module.hxx>
#ifdef _DEBUG
#include <Cad_gSingularZoneFwd.hxx>
#endif // _DEBUG

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_gPlnCurveSurface>,
		std::shared_ptr<Aft2d_gPlnCurveSurface>
		>
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::Split
		(
			const Standard_Real x,
			const std::shared_ptr<Aft2d_gPlnCurveSurface>&
		);

	template<>
	TnbMesh_EXPORT std::shared_ptr<Entity2d_Polygon>
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::GetPolygon
		(
			const std::shared_ptr<Aft2d_gPlnWireSurface>&,
			const std::shared_ptr<Geo_ApprxCurve_Info>& theInfo
		);

#ifdef _DEBUG
	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>> 
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::SubCurves
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve, 
			const std::list<Standard_Real>& thePars, 
			const Standard_Real theTol
		);

	template<>
	TnbMesh_EXPORT std::list<std::shared_ptr<Cad_gSubdivideHorizon>> 
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::CalcParts
		(
			const std::vector<std::shared_ptr<Cad_gSingularZone>>& theZones, 
			const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves
		);

	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>
		Cad_ModifySingularPlaneTools<Aft2d_gRegionPlaneSurface>::ModifyHorizons
		(
			const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves, 
			const std::map<std::shared_ptr<Aft2d_gPlnCurveSurface>, std::shared_ptr<std::list<Standard_Real>>>& theSubMap,
			const Standard_Real theTol
		);
#endif // _DEBUG

}