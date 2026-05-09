#pragma once
#ifndef _Mesh_PatchTemplate_Traits_Header
#define _Mesh_PatchTemplate_Traits_Header

#include <Geo2d_MetricFunctionFwd.hxx>
#include <GeoMetricFun2d_UniformFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo3d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class GModel_Surface;
	class TModel_Surface;
	class GModel_ParaCurve;
	class TModel_ParaCurve;

	class GeoMetricFun3d_Plane;

	template<class SurfType, class SizeFun, class MetricFun>
	struct Mesh_PatchTemplate_Traits {};

	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	template<>
	struct Mesh_PatchTemplate_Traits<GModel_Surface, Geo2d_SizeFunction, Geo2d_MetricFunction> 
	{ 
		typedef GModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, Geo2d_MetricFunction>
			plnRegion;
	};

	template<>
	struct Mesh_PatchTemplate_Traits<GModel_Surface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
	{
		typedef GModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
			plnRegion;
	};

	template<>
	struct Mesh_PatchTemplate_Traits<TModel_Surface, Geo2d_SizeFunction, Geo2d_MetricFunction>
	{ 
		typedef TModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, Geo2d_MetricFunction>
			plnRegion;
	};

	template<>
	struct Mesh_PatchTemplate_Traits<TModel_Surface, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
	{
		typedef TModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, GeoMetricFun2d_Uniform>
			plnRegion;
	};

	template<>
	struct Mesh_PatchTemplate_Traits<GModel_Surface, Geo3d_SizeFunction, void>
	{
		typedef GModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, Geo2d_MetricFunction>
			plnRegion;
	};

	template<>
	struct Mesh_PatchTemplate_Traits<TModel_Surface, Geo3d_SizeFunction, void>
	{
		typedef TModel_ParaCurve parCurveType;
		typedef Mesh_RegionPlane<parCurveType, Geo2d_SizeFunction, Geo2d_MetricFunction>
			plnRegion;
	};
}

#endif // !_Mesh_PatchTemplate_Traits_Header
