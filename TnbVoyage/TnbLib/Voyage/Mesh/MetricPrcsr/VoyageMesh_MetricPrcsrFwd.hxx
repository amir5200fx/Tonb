#pragma once
#ifndef _VoyageMesh_MetricPrcsrFwd_Header
#define _VoyageMesh_MetricPrcsrFwd_Header

#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/12/2023 aamir]
	class VoyageMesh_Edge;

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	typedef Aft_MetricPrcsr<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		VoyageMesh_MetricPrcsr;

}

#endif // !_VoyageMesh_MetricPrcsrFwd_Header
