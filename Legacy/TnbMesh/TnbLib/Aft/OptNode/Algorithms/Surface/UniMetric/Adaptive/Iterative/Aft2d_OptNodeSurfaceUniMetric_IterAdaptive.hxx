#pragma once
#ifndef _Aft2d_OptNodeSurfaceUniMetric_IterAdaptive_Header
#define _Aft2d_OptNodeSurfaceUniMetric_IterAdaptive_Header

#include <Aft2d_OptNodeSurfaceUniMetric_IterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeSurfaceUniMetric_Calculator.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurfaceUniMetric_IterAdaptive::Perform();

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurfaceUniMetric_IterAdaptive::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurfaceUniMetric_IterAdaptive::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_OptNodeSurfaceUniMetric_IterAdaptive);

#endif // !_Aft2d_OptNodeSurfaceUniMetric_IterAdaptive_Header
