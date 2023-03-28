#pragma once
#ifndef _Aft2d_OptNodeUniMetric_nonIterAdaptive_Header
#define _Aft2d_OptNodeUniMetric_nonIterAdaptive_Header

#include <Aft2d_OptNodeUniMetric_nonIterAdaptiveFwd.hxx>
#include <Aft2d_OptNodeUniMetric_Calculator.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_nonIterAdaptive::Perform();

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_nonIterAdaptive::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_nonIterAdaptive::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_OptNodeUniMetric_nonIterAdaptive);

#endif // !_Aft2d_OptNodeUniMetric_nonIterAdaptive_Header
