#pragma once
#ifndef _Aft2d_TBndEdgeTraits_Header
#define _Aft2d_TBndEdgeTraits_Header

#include <Aft2d_BndEdgeTraits.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>
#include <Aft2d_PlnCurveFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	struct Aft2d_TBndEdgeTraits
	{

		typedef Aft2d_BndEdgeTraits bndEdgeTraits;

		typedef Aft2d_PlnCurve curveType;
		typedef void surfType;
		typedef Geo2d_MetricPrcsr metricPrcsr;
	};
}

#endif // !_Aft2d_TBndEdgeTraits_Header
