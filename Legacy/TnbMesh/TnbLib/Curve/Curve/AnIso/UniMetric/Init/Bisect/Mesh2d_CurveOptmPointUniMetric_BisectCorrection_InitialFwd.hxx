#ifdef MeshCurveAnIso_Debug
#pragma once
#ifndef _Mesh2d_CurveOptmPointUniMetric_BisectCorrection_InitialFwd_Header
#define _Mesh2d_CurveOptmPointUniMetric_BisectCorrection_InitialFwd_Header

#include <Geo2d_MetricPrcsrUniMetricFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [10/26/2022 Amir]
	template<class gCurveType, class MetricPrcsrType>
	class Mesh_CurveOptmPoint_BisectCorrection_Initial;

	typedef Mesh_CurveOptmPoint_BisectCorrection_Initial<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Mesh2d_CurveOptmPointUniMetric_BisectCorrection_Initial;
}

#endif // !_Mesh2d_CurveOptmPointUniMetric_BisectCorrection_InitialFwd_Header
#endif // MeshCurveAnIso_Debug
