#pragma once
#ifndef _Aft2d_Model_Header
#define _Aft2d_Model_Header

#include <Aft_Model.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Aft2d_MetricPrcsr.hxx>
#include <Aft2d_OptNode_Calculator.hxx>
#include <Aft2d_FrontGlobalData.hxx>
#include <Aft2d_FrontInfo.hxx>
#include <Aft2d_ModelFwd.hxx>
#include <Aft2d_Core.hxx>

#include <Aft2d_ModelI.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_Model::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_Model::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_Model_Header
