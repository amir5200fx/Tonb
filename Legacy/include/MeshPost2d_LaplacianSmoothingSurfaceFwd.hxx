#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingSurfaceFwd_Header
#define _MeshPost2d_LaplacianSmoothingSurfaceFwd_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/19/2022 Amir]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing;

	typedef MeshPost_LaplacianSmoothing<Aft2d_MetricPrcsrSurface>
		MeshPost2d_LaplacianSmoothingSurface;
}

#endif // !_MeshPost2d_LaplacianSmoothingSurfaceFwd_Header
