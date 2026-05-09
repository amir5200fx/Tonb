#pragma once
#ifndef _Mesh2d_CurveUniMetricFwd_Header
#define _Mesh2d_CurveUniMetricFwd_Header

#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [10/26/2022 Amir]
	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	class Mesh_Curve;

	typedef Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric, false>
		Mesh2d_CurveUniMetric;
}

#endif // !_Mesh2d_CurveUniMetricFwd_Header
