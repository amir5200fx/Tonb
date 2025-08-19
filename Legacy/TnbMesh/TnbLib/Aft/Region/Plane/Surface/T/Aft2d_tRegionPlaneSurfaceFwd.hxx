#pragma once
#ifndef _Aft2d_tRegionPlaneSurfaceFwd_Header
#define _Aft2d_tRegionPlaneSurfaceFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class TModel_ParaCurve;

	typedef Mesh_RegionPlane<TModel_ParaCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_tRegionPlaneSurface;
}

#endif // !_Aft2d_tRegionPlaneSurfaceFwd_Header
