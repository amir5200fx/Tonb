#pragma once
#ifndef _PtdModel2d_Curve_Header
#define _PtdModel2d_Curve_Header

#include <PtdModel2d_CurveFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	void tnbLib::PtdModel2d_Curve::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	void tnbLib::PtdModel2d_Curve::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_PtdModel2d_Curve_Header
