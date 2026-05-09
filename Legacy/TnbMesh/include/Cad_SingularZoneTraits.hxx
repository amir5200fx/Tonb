#pragma once
#ifndef _Cad_SingularZoneTraits_Header
#define _Cad_SingularZoneTraits_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	template<class Surfpln>
	struct cad_singular_zone_traits
	{};

	// Forward Declarations [3/30/2022 Amir]
	class GModel_Surface;
	class TModel_Surface;

	template<>
	struct cad_singular_zone_traits<Aft2d_gRegionPlaneSurface>
	{
		typedef Aft2d_gPlnCurveSurface curveType;
		typedef GModel_Surface surfType;
	};

	template<>
	struct cad_singular_zone_traits<Aft2d_tRegionPlaneSurface>
	{
		typedef Aft2d_tPlnCurveSurface curveType;
		typedef TModel_Surface surfType;
	};
}

#endif // !_Cad_SingularZoneTraits_Header
