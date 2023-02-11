#pragma once
#ifndef _MeshPost_LaplacianSmoothing_AvgFunTraits_Header
#define _MeshPost_LaplacianSmoothing_AvgFunTraits_Header

#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Aft2d_MetricPrcsrAnIsoFwd.hxx>
#include <Aft2d_MetricPrcsrFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceFwd.hxx>
#include <Aft2d_MetricPrcsrSurfaceUniMetricFwd.hxx>
#include <Aft2d_ElementAnIsoFwd.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>
#include <Aft2d_ElementFwd.hxx>
#include <Aft2d_NodeAnIsoFwd.hxx>
#include <Aft2d_NodeSurfaceFwd.hxx>
#include <Aft2d_NodeFwd.hxx>

class Geom_Surface;

namespace tnbLib
{ 

	// Forward Declarations [9/17/2022 Amir]
	class Pnt2d;

	namespace meshPostLib
	{

		template<class ElemType>
		struct laplacian_smoothing_avgFun_traits
		{};

		template<>
		struct laplacian_smoothing_avgFun_traits<Aft2d_MetricPrcsr>
		{
			typedef Aft2d_Node nodeType;
			typedef Pnt2d ptType;
		};

		template<>
		struct laplacian_smoothing_avgFun_traits<Aft2d_MetricPrcsrAnIso>
		{
			typedef Aft2d_NodeAnIso nodeType;
			typedef Pnt2d ptType;
		};

		template<>
		struct laplacian_smoothing_avgFun_traits<Aft2d_MetricPrcsrUniMetric>
		{
			typedef Aft2d_NodeAnIso nodeType;
			typedef Pnt2d ptType;
		};

		template<>
		struct laplacian_smoothing_avgFun_traits<Aft2d_MetricPrcsrSurface> 
		{ 
			typedef Aft2d_NodeSurface nodeType;
			typedef Pnt2d ptType;
		};

		template<>
		struct laplacian_smoothing_avgFun_traits<Aft2d_MetricPrcsrSurfaceUniMetric>
		{
			typedef Aft2d_NodeSurface nodeType;
			typedef Pnt2d ptType;
		};
	}
}

#endif // !_MeshPost_LaplacianSmoothing_AvgFunTraits_Header
