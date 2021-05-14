#pragma once
#ifndef _Aft2d_gRegionPlaneSurfaceFwd_Header
#define _Aft2d_gRegionPlaneSurfaceFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class GModel_ParaCurve;

	typedef Mesh_RegionPlane<GModel_ParaCurve, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_gRegionPlaneSurface;
}

#endif // !_Aft2d_gRegionPlaneSurfaceFwd_Header
