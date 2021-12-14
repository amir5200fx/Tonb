#pragma once
#ifndef _Aft2d_CoreBase_Header
#define _Aft2d_CoreBase_Header

#include <Mesh_Module.hxx>
#include <Aft_Core_Base.hxx>
#include <Aft2d_OptNode_CalculatorFwd.hxx>
#include <Aft2d_FrontInfo.hxx>
#include <Aft2d_FrontGlobalData.hxx>
#include <Aft2d_GlobalData.hxx>
#include <Geo2d_SizeFunction.hxx>

namespace tnbLib
{

	typedef Aft_Core_Base
		<
		Aft2d_OptNode_Calculator,
		Aft2d_FrontInfo,
		Aft2d_FrontGlobalData,
		Geo2d_SizeFunction, 
		void
		>
		Aft2d_CoreBase;


	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBase::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBase::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

#endif // !_Aft2d_CoreBase_Header
