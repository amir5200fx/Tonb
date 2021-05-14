#pragma once
#ifndef _Aft2d_TBndEdgeAnIsoTraits_Header
#define _Aft2d_TBndEdgeAnIsoTraits_Header

#include <Aft2d_BndEdgeAnIsoTraits.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_PlnCurveAnIsoFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	struct Aft2d_TBndEdgeAnIsoTraits
	{

		typedef Aft2d_BndEdgeAnIsoTraits bndEdgeTraits;

		typedef Aft2d_PlnCurveAnIso curveType;
		typedef void surfType;
		typedef Geo2d_MetricPrcsrAnIso metricPrcsr;
	};
}

#endif // !_Aft2d_TBndEdgeAnIsoTraits_Header
