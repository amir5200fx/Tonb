#pragma once
#ifndef _GeoMetricFun2d_BackgroundFwd_Header
#define _GeoMetricFun2d_BackgroundFwd_Header

#include <GeoMesh2d_MetricBackgroundFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/20/2022 Amir]

	template<class BackMeshData>
	class GeoMetricFun_Background;

	typedef GeoMetricFun_Background<GeoMesh2d_MetricBackground> 
		GeoMetricFun2d_Background;
}

#endif // !_GeoMetricFun2d_BackgroundFwd_Header
