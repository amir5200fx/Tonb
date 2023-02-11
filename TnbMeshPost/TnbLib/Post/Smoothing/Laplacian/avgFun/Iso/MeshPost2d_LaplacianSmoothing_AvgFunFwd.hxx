#pragma once
#ifndef _MeshPost2d_LaplacianSmoothing_AvgFunFwd_Header
#define _MeshPost2d_LaplacianSmoothing_AvgFunFwd_Header

#include <Aft2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{
	// Forward Declarations [1/24/2023 Payvand]

	template<class MetricMap>
	class MeshPost_LaplacianSmoothing_AvgFun;

	typedef MeshPost_LaplacianSmoothing_AvgFun<Aft2d_MetricPrcsr>
		MeshPost2d_LaplacianSmoothing_AvgFun;
}

#endif // !_MeshPost2d_LaplacianSmoothing_AvgFunFwd_Header
