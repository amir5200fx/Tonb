#pragma once
#ifndef _Aft2d_OptNodeSurface_Calculator_Header
#define _Aft2d_OptNodeSurface_Calculator_Header

#include <Aft_OptNode_Calculator.hxx>
#include <Aft2d_EdgeSurface.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_OptNodeSurface_CalculatorFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Calculator::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Calculator::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Aft2d_OptNodeSurface_Calculator);

#endif // !_Aft2d_OptNodeSurface_Calculator_Header