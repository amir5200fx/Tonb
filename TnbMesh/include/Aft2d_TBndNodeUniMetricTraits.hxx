#pragma once
#ifndef _Aft2d_TBndNodeUniMetricTraits_Header
#define _Aft2d_TBndNodeUniMetricTraits_Header

#include <Aft2d_BndNodeAnIsoTraits.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class CrvEntity, class SizeFun, class MetricFun>
	class Mesh_PlnCurve;

	struct Aft2d_TBndNodeUniMetricTraits
	{

		typedef Aft2d_BndNodeAnIsoTraits bndNodeTraits;

		typedef Mesh_PlnCurve<Pln_Curve, Geo2d_SizeFunction, GeoMetricFun2d_Uniform> curveType;
		typedef void surfType;
		typedef Geo2d_MetricPrcsrAnIso metricPrcsr;
	};
}

#endif // !_Aft2d_TBndNodeUniMetricTraits_Header
