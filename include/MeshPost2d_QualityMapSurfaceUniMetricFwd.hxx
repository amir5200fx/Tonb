#pragma once
#ifndef _MeshPost2d_QualityMapSurfaceUniMetricFwd_Header
#define _MeshPost2d_QualityMapSurfaceUniMetricFwd_Header

#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/18/2022 Amir]
	template<class MetricMap>
	class MeshPost_QualityMap;

	typedef MeshPost_QualityMap<Aft2d_MetricPrcsrSurfaceUniMetric>
		MeshPost2d_QualityMapSurfaceUniMetric;
}

#endif // !_MeshPost2d_QualityMapSurfaceUniMetricFwd_Header
