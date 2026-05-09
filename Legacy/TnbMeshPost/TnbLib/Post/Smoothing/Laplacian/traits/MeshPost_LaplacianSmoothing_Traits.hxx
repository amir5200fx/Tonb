#pragma once
#ifndef _MeshPost_LaplacianSmoothing_Traits_Header
#define _MeshPost_LaplacianSmoothing_Traits_Header

#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Aft2d_MetricPrcsrFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>
#include <Aft2d_ElementFwd.hxx>
#include <Aft2d_NodeFwd.hxx>

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
		struct laplacian_smoothing_traits<Aft2d_MetricPrcsr>
		{
			typedef Aft2d_Element elemType;
			typedef Aft2d_Node nodeType;
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
