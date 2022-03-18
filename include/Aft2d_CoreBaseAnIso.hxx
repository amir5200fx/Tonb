#pragma once
#ifndef _Aft2d_CoreBaseAnIso_Header
#define _Aft2d_CoreBaseAnIso_Header

#include <Mesh_Module.hxx>
#include <Aft_Core_Base.hxx>
#include <Aft2d_OptNodeAnIso_CalculatorFwd.hxx>
#include <Aft2d_FrontAnIsoInfo.hxx>
#include <Aft2d_FrontAnIsoGlobalData.hxx>
#include <Aft2d_GlobalDataAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_CoreBaseAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBaseAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBaseAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_CoreBaseAnIso_Header
