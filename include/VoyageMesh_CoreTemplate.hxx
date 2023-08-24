#pragma once
#ifndef _VoyageMesh_CoreTemplate_Header
#define _VoyageMesh_CoreTemplate_Header

#include <VoyageMesh_FrontInfo.hxx>
#include <VoyageMesh_FrontGlobalData.hxx>
#include <Aft_Core.hxx>

namespace tnbLib
{

	template<class OptNodeAlg, class SizeFun, class MetricFun>
	using VoyageMesh_CoreTemplate =
		Aft_Core
		<
		OptNodeAlg,
		SizeFun, VoyageMesh_FrontInfo,
		VoyageMesh_FrontGlobalData, MetricFun
		>;
}

#endif // !_VoyageMesh_CoreTemplate_Header
