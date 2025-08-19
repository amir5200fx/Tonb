#pragma once
#ifndef _Aft2d_CorrOptNodeUniMetric_Fraction_Header
#define _Aft2d_CorrOptNodeUniMetric_Fraction_Header

#include <Aft_OptNode_Corrector.hxx>
#include <Aft2d_CorrOptNodeUniMetric_FractionFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_CorrOptNodeUniMetric_Fraction::Perform
	(
		const Aft_SizeCorr_FractionInfo& theInfo
	);
}

#endif // !_Aft2d_CorrOptNodeUniMetric_Fraction_Header
