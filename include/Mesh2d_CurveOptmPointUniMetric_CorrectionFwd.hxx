#ifdef MeshCurveAnIso_Debug
#pragma once
#ifndef _Mesh2d_CurveOptmPointUniMetric_CorrectionFwd_Header
#define _Mesh2d_CurveOptmPointUniMetric_CorrectionFwd_Header

#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [10/26/2022 Amir]
	template<class gCurveType, class MetricPrcsrType>
	class Mesh_CurveOptmPoint_Correction;

	typedef Mesh_CurveOptmPoint_Correction<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Mesh2d_CurveOptmPointUniMetric_Correction;
}

#endif // !_Mesh2d_CurveOptmPointUniMetric_CorrectionFwd_Header
#endif // MeshCurveAnIso_Debug
