#pragma once
#ifndef _Aft2d_ModelAnIso_Header
#define _Aft2d_ModelAnIso_Header

#include <Aft_Model.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_MetricPrcsrAnIso.hxx>
#include <Aft2d_OptNodeAnIso_Calculator.hxx>
#include <Aft2d_FrontAnIsoGlobalData.hxx>
#include <Aft2d_FrontAnIsoInfo.hxx>
#include <Aft2d_ModelAnIsoFwd.hxx>
#include <Aft2d_CoreAnIso.hxx>

#include <Aft2d_ModelAnIsoI.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_ModelAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_ModelAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_ModelAnIso_Header
