#pragma once
#ifndef _Aft2d_tModelSurfaceFwd_Header
#define _Aft2d_tModelSurfaceFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/24/2021 Amir]
	template<class ModelType, class SizeFun, class MetricFun>
	class Aft_Model;

	class TModel_Plane;

	typedef Aft_Model<TModel_Plane, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_tModelSurface;
}

#endif // !_Aft2d_tModelSurfaceFwd_Header
