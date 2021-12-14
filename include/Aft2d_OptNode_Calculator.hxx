#pragma once
#ifndef _Aft2d_OptNode_Calculator_Header
#define _Aft2d_OptNode_Calculator_Header

#include <Mesh_Module.hxx>
#include <Aft_OptNode_Calculator.hxx>
#include <Aft2d_OptNode_CalculatorFwd.hxx>
#include <Geo2d_SizeFunction.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNode_Calculator::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_OptNode_Calculator::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_Aft2d_OptNode_Calculator_Header