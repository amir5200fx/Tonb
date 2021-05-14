#pragma once
#ifndef _Aft2d_RegionPlaneAnIsoFwd_Header
#define _Aft2d_RegionPlaneAnIsoFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>
#include <Aft2d_PlnCurveFwd.hxx>
#include <Aft2d_PlnWireFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class CurveType, class SizeFun, class MetricFun>
	class Mesh_RegionPlane;

	class Pln_Curve;

	typedef Mesh_RegionPlane<Pln_Curve, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_RegionPlaneAnIso;
}

#endif // !_Aft2d_RegionPlaneAnIsoFwd_Header
