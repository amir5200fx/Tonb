#pragma once
#ifndef _Cad_SingularityTraits_Header
#define _Cad_SingularityTraits_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>
#include <Aft2d_tPlnWireSurfaceFwd.hxx>
#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]

	template<class SurfType>
	struct cad_singularity_traits {};

	class GModel_Surface;
	class GModel_Plane;
	class GModel_ParaCurve;
	class GModel_ParaWire;

	class TModel_Surface;
	class TModel_Plane;
	class TModel_ParaCurve;
	class TModel_ParaWire;

	template<> 
	struct cad_singularity_traits<GModel_Surface>
	{
		typedef Aft2d_gRegionPlaneSurface plnType;
		typedef Aft2d_gPlnCurveSurface parCurveType;
		typedef Aft2d_gPlnWireSurface parWireType;
	};

	template<>
	struct cad_singularity_traits<TModel_Surface>
	{
		typedef Aft2d_tRegionPlaneSurface plnType;
		typedef Aft2d_tPlnCurveSurface parCurveType;
		typedef Aft2d_tPlnWireSurface parWireType;
	};
}

#endif // _Cad_SingularityTraits_Header
