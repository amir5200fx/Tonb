#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AvgFunFwd_Header
#define _MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AvgFunFwd_Header

#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/19/2022 Amir]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing_AvgFun;

	typedef MeshPost_LaplacianSmoothing_AvgFun<Aft2d_MetricPrcsrSurfaceUniMetric>
		MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AvgFun;
}

#endif // !_MeshPost2d_LaplacianSmoothingSurfaceUniMetric_AvgFunFwd_Header
