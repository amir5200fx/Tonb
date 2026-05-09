#pragma once
#ifndef _Aft2d_MetricPrcsr_Header
#define _Aft2d_MetricPrcsr_Header

#include <Aft_MetricPrcsr.hxx>
#include <Aft2d_Edge.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Aft2d_MetricPrcsrFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsr::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_MetricPrcsr::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

}

#endif // !_Aft2d_MetricPrcsr_Header