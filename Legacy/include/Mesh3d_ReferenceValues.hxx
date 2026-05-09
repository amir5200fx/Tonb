#pragma once
#ifndef _Mesh3d_ReferenceValues_Header
#define _Mesh3d_ReferenceValues_Header

#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_ReferenceValuesFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_ReferenceValues::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_ReferenceValues::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Mesh3d_ReferenceValues_Header
