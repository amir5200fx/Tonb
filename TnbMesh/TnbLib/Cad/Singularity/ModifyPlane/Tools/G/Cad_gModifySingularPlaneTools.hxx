#pragma once
#include <Mesh_Module.hxx>
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
}