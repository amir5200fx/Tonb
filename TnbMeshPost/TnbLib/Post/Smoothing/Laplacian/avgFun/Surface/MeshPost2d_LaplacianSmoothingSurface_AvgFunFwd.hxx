#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingSurface_AvgFunFwd_Header
#define _MeshPost2d_LaplacianSmoothingSurface_AvgFunFwd_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/19/2022 Amir]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing_AvgFun;

	typedef MeshPost_LaplacianSmoothing_AvgFun<Aft2d_MetricPrcsrSurface>
		MeshPost2d_LaplacianSmoothingSurface_AvgFun;
}

#endif // !_MeshPost2d_LaplacianSmoothingSurface_AvgFunFwd_Header
