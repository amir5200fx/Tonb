#pragma once
#ifndef _Cad_ModifySingularPlaneTraits_Header
#define _Cad_ModifySingularPlaneTraits_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>
#include <Aft2d_tPlnWireSurfaceFwd.hxx>
#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	template<class SurfPlnType>
	struct cad_modify_singular_plane_traits {};

	// Forward Declarations [3/31/2022 Amir]

	template<>
	struct cad_modify_singular_plane_traits<Aft2d_gRegionPlaneSurface>
	{
		typedef Aft2d_gPlnWireSurface wireType;
		typedef Aft2d_gPlnCurveSurface curveType;
	};

	template<>
	struct cad_modify_singular_plane_traits<Aft2d_tRegionPlaneSurface>
	{
		typedef Aft2d_tPlnWireSurface wireType;
		typedef Aft2d_tPlnCurveSurface curveType;
	};
}

#endif // !_Cad_ModifySingularPlaneTraits_Header
