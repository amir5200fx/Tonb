#pragma once
#ifndef _Aft2d_OptNodeUniMetric_Calculator_Header
#define _Aft2d_OptNodeUniMetric_Calculator_Header

#include <Aft_OptNode_Calculator.hxx>
#include <Aft2d_EdgeAnIso.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <GeoMetricFun2d_Uniform.hxx>
#include <Aft2d_OptNodeUniMetric_CalculatorFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_Calculator::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_Calculator::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	void Aft2d_OptNodeUniMetric_Calculator::Perform();
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Aft2d_OptNodeUniMetric_Calculator);

#endif // !_Aft2d_OptNodeUniMetric_Calculator_Header
