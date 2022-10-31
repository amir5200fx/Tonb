#pragma once
#ifndef _Mesh2d_CurveEntityUniMetricFwd_Header
#define _Mesh2d_CurveEntityUniMetricFwd_Header

#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [10/26/2022 Amir]
	template<class gCurveType, class MetricPrcsrType = void>
	class Mesh_CurveEntity;

	typedef Mesh_CurveEntity<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Mesh2d_CurveEntityAnIso;
}

#endif // !_Mesh2d_CurveEntityUniMetricFwd_Header
