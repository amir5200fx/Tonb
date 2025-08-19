#pragma once
#ifndef _Aft2d_gModelSurfaceFwd_Header
#define _Aft2d_gModelSurfaceFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/24/2021 Amir]
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class GModel_Plane;

	typedef Aft_Model<GModel_Plane, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_gModelSurface;
}

#endif // !_Aft2d_gModelSurfaceFwd_Header
