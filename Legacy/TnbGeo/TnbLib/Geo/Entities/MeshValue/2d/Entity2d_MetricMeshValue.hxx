#pragma once
#ifndef _Entity2d_MetricMeshValue_Header
#define _Entity2d_MetricMeshValue_Header

#include <Entity_MeshValue.hxx>
#include <Entity2d_MetricMeshValueFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbGeo_EXPORT void Entity2d_MetricMeshValue::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbGeo_EXPORT void Entity2d_MetricMeshValue::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Entity2d_MetricMeshValue_Header
