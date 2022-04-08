#pragma once
#ifndef _Cad_SingularityTraits_Header
#define _Cad_SingularityTraits_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

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
		typedef GModel_Plane plnType;
		typedef Aft2d_gPlnCurveSurface parCurveType;
		typedef GModel_ParaWire parWireType;
	};

	template<>
	struct cad_singularity_traits<TModel_Surface>
	{
		typedef TModel_Plane plnType;
		typedef Aft2d_tPlnCurveSurface parCurveType;
		typedef TModel_ParaWire parWireType;
	};
}

#endif // _Cad_SingularityTraits_Header
