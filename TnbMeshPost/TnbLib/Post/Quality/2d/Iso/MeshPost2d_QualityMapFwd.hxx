#pragma once
#ifndef _MeshPost2d_QualityMapFwd_Header
#define _MeshPost2d_QualityMapFwd_Header

#include <Aft2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/18/2022 Amir]
	template<class MetricMap>
	class MeshPost_QualityMap;

	typedef MeshPost_QualityMap<Aft2d_MetricPrcsr>
		MeshPost2d_QualityMap;
}

#endif // !_MeshPost2d_QualityMapFwd_Header
