#pragma once
#ifndef _VoyageMesh_CorrOptNode_Iterative_Header
#define _VoyageMesh_CorrOptNode_Iterative_Header

#include <VoyageMesh_CorrOptNode_IterativeFwd.hxx>
#include <Voyage_Module.hxx>
#include <Aft_OptNode_Corrector.hxx>

namespace tnbLib
{
	template<>
	TnbVoyage_EXPORT void VoyageMesh_CorrOptNode_Iterative::Perform
	(
		const Aft_SizeCorr_IterativeInfo& theInfo
	);
}

#endif // !_VoyageMesh_CorrOptNode_Iterative_Header

