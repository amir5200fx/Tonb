#pragma once
#ifndef _Aft2d_gPatchFwd_Header
#define _Aft2d_gPatchFwd_Header

#include <Geo2d_SizeFunctionFwd.hxx>
#include <Geo2d_MetricFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [12/19/2021 Amir]

	template<class SurfType, class SizeFun, class MetricFun>
	class Mesh_PatchTemplate;

	class GModel_Surface;

	typedef Mesh_PatchTemplate<GModel_Surface, Geo2d_SizeFunction, Geo2d_MetricFunction>
		Aft2d_gPatch;
}

#endif // !_Aft2d_gPatchFwd_Header
