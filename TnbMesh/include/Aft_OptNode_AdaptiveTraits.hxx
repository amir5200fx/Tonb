#pragma once
#ifndef _Aft_OptNode_AdaptiveTraits_Header
#define _Aft_OptNode_AdaptiveTraits_Header

#include <Aft2d_EdgeFwd.hxx>
#include <Aft2d_CorrOptNode_FractionFwd.hxx>
#include <Aft2d_CorrOptNode_IterativeFwd.hxx>

namespace tnbLib
{

	template<class T>
	struct corrector_info_type_from_alg {};

	// Forward declarations [3/1/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;
	class Aft_SizeCorr_FractionInfo;

	template<> struct corrector_info_type_from_alg<Aft2d_CorrOptNode_Iterative> { typedef Aft_SizeCorr_IterativeInfo infoType; };
	template<> struct corrector_info_type_from_alg<Aft2d_CorrOptNode_Fraction> { typedef Aft_SizeCorr_FractionInfo infoType; };
}

#endif // !_Aft_OptNode_AdaptiveTraits_Header
