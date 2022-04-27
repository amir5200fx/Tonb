#pragma once
#ifndef _Aft2d_TBndNodeTraits_Header
#define _Aft2d_TBndNodeTraits_Header

#include <Aft2d_BndNodeTraits.hxx>
#include <Aft2d_PlnCurveFwd.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;

	struct Aft2d_TBndNodeTraits
	{

		typedef Aft2d_BndNodeTraits bndNodeTraits;

		typedef Aft2d_PlnCurve curveType;
		typedef void surfType;
		typedef Geo2d_MetricPrcsr metricPrcsr;
	};
}

#endif // !_Aft2d_TBndNodeTraits_Header