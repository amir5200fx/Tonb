#pragma once
#ifndef _MeshPost_LaplacianSmoothing_Traits_Header
#define _MeshPost_LaplacianSmoothing_Traits_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>

namespace tnbLib
{

	namespace meshPostLib
	{

		template<class ElemType>
		struct laplacian_smoothing_traits{};

		template<>
		struct laplacian_smoothing_traits<Aft2d_MetricPrcsrSurface> 
		{
			typedef Aft2d_ElementSurface elemType;
			typedef Aft2d_NodeSurface nodeType;
		};

		template<>
		struct laplacian_smoothing_traits<Aft2d_MetricPrcsrSurfaceUniMetric>
		{
			typedef Aft2d_ElementSurface elemType;
			typedef Aft2d_NodeSurface nodeType;
		};
	}
}

#endif // !_MeshPost_LaplacianSmoothing_Traits_Header
