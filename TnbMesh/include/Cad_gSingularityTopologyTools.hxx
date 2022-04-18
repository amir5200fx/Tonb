#pragma once
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>
namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>> 
		Cad_SingularityTopologyTools::RetrieveCurves<Aft2d_gPlnCurveSurface, Aft2d_gPlnWireSurface>
		(
			const std::shared_ptr<Aft2d_gPlnWireSurface>&
			);
}