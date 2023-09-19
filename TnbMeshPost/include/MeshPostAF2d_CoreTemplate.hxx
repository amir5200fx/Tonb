#pragma once
#ifndef _MeshPostAF2d_CoreTemplate_Header
#define _MeshPostAF2d_CoreTemplate_Header

#include <MeshPostAF2d_FrontInfo.hxx>
#include <MeshPostAF2d_FrontGlobalData.hxx>
#include <Aft_Core.hxx>

namespace tnbLib
{

	template<class OptNodeAlg, class SizeFun, class MetricFun>
	using MeshPostAF2d_CoreTemplate =
		Aft_Core
		<
		OptNodeAlg,
		SizeFun, MeshPostAF2d_FrontInfo,
		MeshPostAF2d_FrontGlobalData, MetricFun
		>;
}

#endif // !_MeshPostAF2d_CoreTemplate_Header
