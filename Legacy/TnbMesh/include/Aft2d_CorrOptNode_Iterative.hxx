#pragma once
#ifndef _Aft2d_CorrOptNode_Iterative_Header
#define _Aft2d_CorrOptNode_Iterative_Header

#include <Aft_OptNode_Corrector.hxx>
#include <Aft2d_CorrOptNode_IterativeFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_CorrOptNode_Iterative::Perform(const Aft_SizeCorr_IterativeInfo& theInfo);
}

#endif // !_Aft2d_CorrOptNode_Iterative_Header
