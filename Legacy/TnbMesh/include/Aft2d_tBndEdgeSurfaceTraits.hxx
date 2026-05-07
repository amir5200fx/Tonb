#pragma once
#ifndef _Aft2d_tBndEdgeSurfaceTraits_Header
#define _Aft2d_tBndEdgeSurfaceTraits_Header

#include <Aft2d_BndEdgeSurfaceTraits.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/20/2021 Amir]

	class TModel_ParaCurve;

	struct Aft2d_tBndEdgeSurfaceTraits
	{
		typedef Aft2d_BndEdgeSurfaceTraits bndEdgeTraits;

		typedef typename Aft2d_tPlnCurveSurface curveType;
		typedef void surfType;
		typedef typename Geo2d_MetricPrcsrAnIso metricPrcsr;
	};
}

#endif // !_Aft2d_tBndEdgeSurfaceTraits_Header
