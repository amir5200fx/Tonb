#pragma once
#ifndef _Aft2d_RegionPlaneFwd_Header
#define _Aft2d_RegionPlaneFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Aft2d_PlnCurveFwd.hxx>
#include <Aft2d_PlnWireFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class Pln_Curve;

	typedef Mesh_RegionPlane<Pln_Curve, Geo2d_SizeFunction, void>
		Aft2d_RegionPlane;
}

#endif // !_Aft2d_RegionPlaneFwd_Header
