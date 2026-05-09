#pragma once
#ifndef _Aft2d_FrontInfoAdaptor_Header
#define _Aft2d_FrontInfoAdaptor_Header

#include <Mesh_Module.hxx>
#include <Aft2d_FrontInfoAdaptorTemplate.hxx>
#include <Aft_FrontTraits.hxx>
#include <Aft2d_FrontInfoAdaptorFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_FrontInfoAdaptor::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_FrontInfoAdaptor::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

#endif // !_Aft2d_FrontInfoAdaptor_Header