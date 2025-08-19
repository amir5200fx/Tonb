#pragma once
#ifndef _MeshPost2d_QualityMapSurfaceFwd_Header
#define _MeshPost2d_QualityMapSurfaceFwd_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [9/18/2022 Amir]
	template<class MetricMap>
	class MeshPost_QualityMap;

	typedef MeshPost_QualityMap<Aft2d_MetricPrcsrSurface>
		MeshPost2d_QualityMapSurface;
}

#endif // !_MeshPost2d_QualityMapSurfaceFwd_Header
