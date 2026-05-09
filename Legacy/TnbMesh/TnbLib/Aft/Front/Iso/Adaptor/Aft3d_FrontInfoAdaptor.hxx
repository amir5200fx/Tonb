#pragma once
#ifndef _Aft3d_FrontInfoAdaptor_Header
#define _Aft3d_FrontInfoAdaptor_Header

#include <Aft3d_FrontInfoAdaptorTemplate.hxx>
#include <Aft_FrontTraits.hxx>
#include <Aft3d_FrontInfoAdaptorFwd.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FrontInfoAdaptor::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft3d_FrontInfoAdaptor::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft3d_FrontInfoAdaptor_Header
