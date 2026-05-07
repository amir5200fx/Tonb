#pragma once
#ifndef _Aft2d_BoundaryOfPlaneFwd_Header
#define _Aft2d_BoundaryOfPlaneFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Aft2d_RegionPlaneFwd.hxx>

namespace tnbLib
{

	//- Forward Declarations
	template<class RegionType, class SizeFun, class MetricFun>
	class Aft_BoundaryOfPlane;

	typedef Aft_BoundaryOfPlane<Aft2d_RegionPlane, Geo2d_SizeFunction, void>
		Aft2d_BoundaryOfPlane;
}

#endif // !_Aft2d_BoundaryOfPlaneFwd_Header
