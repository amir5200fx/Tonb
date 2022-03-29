#pragma once
#ifndef _Cad_SingularityTraits_Header
#define _Cad_SingularityTraits_Header

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]

	template<class SurfType>
	struct cad_singularity_traits {};

	class GModel_Surface;
	class GModel_Plane;
	class GModel_ParaCurve;

	class TModel_Surface;
	class TModel_Plane;
	class TModel_ParaCurve;

	template<> 
	struct cad_singularity_traits<GModel_Surface>
	{
		typedef GModel_Plane plnType;
		typedef GModel_ParaCurve parCurveType;
	};

	template<>
	struct cad_singularity_traits<TModel_Surface>
	{
		typedef TModel_Plane plnType;
		typedef TModel_ParaCurve parCurveType;
	};
}

#endif // _Cad_SingularityTraits_Header
