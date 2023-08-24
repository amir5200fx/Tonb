#pragma once
#ifndef _VoyageMesh_AltrOptNodeFwd_Header
#define _VoyageMesh_AltrOptNodeFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_AltrOptNode;

	class VoyageMesh_Edge;

	typedef Aft_AltrOptNode<VoyageMesh_Edge, Geo2d_SizeFunction, Geo2d_MetricFunction>
		VoyageMesh_AltrOptNode;
}

#endif // !_VoyageMesh_AltrOptNodeFwd_Header
