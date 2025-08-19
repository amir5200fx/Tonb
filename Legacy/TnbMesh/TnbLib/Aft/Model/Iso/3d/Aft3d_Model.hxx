#pragma once
#ifndef _Aft3d_Model_Header
#define _Aft3d_Model_Header

#include <Aft_Model.hxx>
#include <Geo3d_SizeFunction.hxx>
#include <Aft3d_MetricPrcsr.hxx>
#include <Aft3d_OptNode_Calculator.hxx>
#include <Aft3d_FrontGlobalData.hxx>
#include <Aft3d_FrontInfo.hxx>
#include <Aft3d_ModelFwd.hxx>
#include <Aft3d_Core.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_Model::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_Model::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#include <Aft3d_ModelI.hxx>

#endif // !_Aft3d_Model_Header
