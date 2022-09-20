#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingSurfaceUniMetricFwd_Header
#define _MeshPost2d_LaplacianSmoothingSurfaceUniMetricFwd_Header

#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/19/2022 Amir]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing;

	typedef MeshPost_LaplacianSmoothing<Aft2d_MetricPrcsrSurfaceUniMetric>
		MeshPost2d_LaplacianSmoothingSurfaceUniMetric;
}

#endif // !_MeshPost2d_LaplacianSmoothingSurfaceUniMetricFwd_Header
