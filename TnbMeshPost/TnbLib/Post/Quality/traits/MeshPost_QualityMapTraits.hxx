#pragma once
#ifndef _MeshPost_QualityMapTraits_Header
#define _MeshPost_QualityMapTraits_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>

namespace tnbLib
{

	namespace meshPostLib
	{

		template<class MetricMap>
		struct quality_map_traits{};

		template<>
		struct quality_map_traits<Aft2d_MetricPrcsrSurface> { typedef Aft2d_ElementSurface elemType; };

		template<>
		struct quality_map_traits<Aft2d_MetricPrcsrSurfaceUniMetric> { typedef Aft2d_ElementSurface elemType; };
	}
}

#endif // !_MeshPost_QualityMapTraits_Header
