#pragma once
#ifndef _Entity3d_MeshValue_Header
#define _Entity3d_MeshValue_Header

#include <Entity_MeshValue.hxx>
#include <Entity3d_MeshValueFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbGeo_EXPORT void Entity3d_MeshValue::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbGeo_EXPORT void Entity3d_MeshValue::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Entity3d_MeshValue_Header
