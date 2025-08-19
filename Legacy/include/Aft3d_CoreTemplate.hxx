#pragma once
#ifndef _Aft3d_CoreTemplate_Header
#define _Aft3d_CoreTemplate_Header

#include <Aft_Core.hxx>
#include <Aft3d_FrontInfo.hxx>
#include <Aft3d_FrontGlobalData.hxx>

namespace tnbLib
{

	template<class OptNodeAlg, class SizeFun>
	using Aft3d_CoreTemplate =
		Aft_Core
		<
		OptNodeAlg,
		SizeFun, Aft3d_FrontInfo,
		Aft3d_FrontGlobalData, void
		>;
}

#endif // !_Aft3d_CoreTemplate_Header
