#pragma once
#ifndef _Cad_SingularCurveTraits_Header
#define _Cad_SingularCurveTraits_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gPlnCurveSurfaceUniMetricFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	template<class CurveType>
	struct cad_singular_curve_traits {};

	// Forward Declarations [4/5/2022 Amir]
	class GModel_ParaCurve;
	class TModel_ParaCurve;
	class GModel_Surface;
	class TModel_Surface;

	template<>
	struct cad_singular_curve_traits<Aft2d_gPlnCurveSurface> 
	{ 
		typedef GModel_Surface surfType;
		typedef GModel_ParaCurve baseCurveType;
	};

	template<>
	struct cad_singular_curve_traits<Aft2d_gPlnCurveSurfaceUniMetric>
	{
		typedef GModel_Surface surfType;
		typedef GModel_ParaCurve baseCurveType;
	};

	template<>
	struct cad_singular_curve_traits<Aft2d_tPlnCurveSurface>
	{
		typedef TModel_Surface surfType;
		typedef TModel_ParaCurve baseCurveType;
	};

	template<>
	struct cad_singular_curve_traits<Aft2d_tPlnCurveSurfaceUniMetric>
	{
		typedef TModel_Surface surfType;
		typedef TModel_ParaCurve baseCurveType;
	};
}

#endif // !_Cad_SingularCurveTraits_Header
