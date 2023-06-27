#pragma once
#ifndef _MeshPost2d_LaplacianSmoothingFwd_Header
#define _MeshPost2d_LaplacianSmoothingFwd_Header

#include <Aft2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/27/2023 Payvand]
	template<class MetricMap>
	class MeshPost_LaplacianSmoothing;

	typedef MeshPost_LaplacianSmoothing<Aft2d_MetricPrcsr>
		MeshPost2d_LaplacianSmoothing;
}

#endif // !_MeshPost2d_LaplacianSmoothingFwd_Header
