#pragma once
#ifndef _PtdModel3d_Curve_Header
#define _PtdModel3d_Curve_Header

#include <PtdModel3d_CurveFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	void tnbLib::PtdModel3d_Curve::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	void tnbLib::PtdModel3d_Curve::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_PtdModel3d_Curve_Header
