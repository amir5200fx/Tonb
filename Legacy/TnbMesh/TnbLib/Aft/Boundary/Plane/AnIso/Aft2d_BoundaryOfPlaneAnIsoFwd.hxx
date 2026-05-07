#pragma once
#ifndef _Aft2d_BoundaryOfPlaneAnIsoFwd_Header
#define _Aft2d_BoundaryOfPlaneAnIsoFwd_Header

#include <Aft2d_RegionPlaneAnIsoFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_RegionPlaneAnIso, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_BoundaryOfPlaneAnIso;
}

#endif // !_Aft2d_BoundaryOfPlaneAnIsoFwd_Header
