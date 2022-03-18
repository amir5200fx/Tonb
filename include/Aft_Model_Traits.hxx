#pragma once
#ifndef _Aft_Model_Traits_Header
#define _Aft_Model_Traits_Header

#include <Aft2d_CoreFwd.hxx>
#include <Aft2d_CoreAnIsoFwd.hxx>
#include <Aft2d_CoreSurfaceFwd.hxx>
#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_EdgeAnIsoFwd.hxx>
#include <Aft2d_EdgeSurfaceFwd.hxx>
#include <Aft2d_OptNode_CalculatorFwd.hxx>
#include <Aft2d_OptNodeAnIso_CalculatorFwd.hxx>
#include <Aft2d_OptNodeSurface_CalculatorFwd.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_CalculatorFwd.hxx>
#include <Aft2d_OptNodeUniMetric_CalculatorFwd.hxx>
#include <GeoMetricFun2d_Uniform.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class GModel_Surface;
	class TModel_Surface;
	class GModel_Plane;
	class TModel_Plane;
	class Aft2d_Model_Cache;
	class Aft3d_Model_Cache;

	template<class ModelType, class SizeFun, class MetricFun = void> struct aft_model_traits {};

	template<class SizeFun>
	struct aft_model_traits<Cad2d_Plane, SizeFun>
	{
		typedef Aft2d_Edge frontType;
		typedef Aft2d_Element elementType;
		typedef Aft2d_OptNode_Calculator nodeCalculator;
		typedef Aft2d_FrontInfo frontInfo;
		typedef Aft2d_FrontGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun, class MetricFun>
	struct aft_model_traits<Cad2d_Plane, SizeFun, MetricFun>
	{
		typedef Aft2d_EdgeAnIso frontType;
		typedef Aft2d_ElementAnIso elementType;
		typedef Aft2d_OptNodeAnIso_Calculator nodeCalculator;
		typedef Aft2d_FrontAnIsoInfo frontInfo;
		typedef Aft2d_FrontAnIsoGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun>
	struct aft_model_traits<Cad2d_Plane, SizeFun, GeoMetricFun2d_Uniform>
	{
		typedef Aft2d_EdgeAnIso frontType;
		typedef Aft2d_ElementAnIso elementType;
		typedef Aft2d_OptNodeUniMetric_Calculator nodeCalculator;
		typedef Aft2d_FrontAnIsoInfo frontInfo;
		typedef Aft2d_FrontAnIsoGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun, class MetricFun>
	struct aft_model_traits<GModel_Plane, SizeFun, MetricFun>
	{
		typedef Aft2d_EdgeSurface frontType;
		typedef Aft2d_ElementSurface elementType;
		typedef Aft2d_OptNodeSurface_Calculator nodeCalculator;
		typedef Aft2d_FrontSurfaceInfo frontInfo;
		typedef Aft2d_FrontSurfaceGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun>
	struct aft_model_traits<GModel_Plane, SizeFun, GeoMetricFun2d_Uniform>
	{
		typedef Aft2d_EdgeSurface frontType;
		typedef Aft2d_ElementSurface elementType;
		typedef Aft2d_OptNodeSurfaceUniMetric_Calculator nodeCalculator;
		typedef Aft2d_FrontSurfaceInfo frontInfo;
		typedef Aft2d_FrontSurfaceGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun, class MetricFun>
	struct aft_model_traits<TModel_Plane, SizeFun, MetricFun>
	{
		typedef Aft2d_EdgeSurface frontType;
		typedef Aft2d_ElementSurface elementType;
		typedef Aft2d_OptNodeSurface_Calculator nodeCalculator;
		typedef Aft2d_FrontSurfaceInfo frontInfo;
		typedef Aft2d_FrontSurfaceGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};

	template<class SizeFun>
	struct aft_model_traits<TModel_Plane, SizeFun, GeoMetricFun2d_Uniform>
	{
		typedef Aft2d_EdgeSurface frontType;
		typedef Aft2d_ElementSurface elementType;
		typedef Aft2d_OptNodeSurfaceUniMetric_Calculator nodeCalculator;
		typedef Aft2d_FrontSurfaceInfo frontInfo;
		typedef Aft2d_FrontSurfaceGlobalData globalData;

		typedef Aft2d_Model_Cache cacheType;
	};
}

#endif // !_Aft_Model_Traits_Header
