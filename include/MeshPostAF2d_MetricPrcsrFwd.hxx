#pragma once
#ifndef _MeshPostAF2d_MetricPrcsrFwd_Header
#define _MeshPostAF2d_MetricPrcsrFwd_Header

#include <Geo2d_MetricFunctionFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>
#include <Entity2d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]
	class MeshPostAF2d_Edge;

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	typedef Aft_MetricPrcsr<MeshPostAF2d_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		MeshPostAF2d_MetricPrcsr;
}

#endif // !_MeshPostAF2d_MetricPrcsrFwd_Header
