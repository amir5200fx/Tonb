#pragma once
#ifndef _Aft2d_CorrOptNodeSurfaceUniMetric_Iterative_Header
#define _Aft2d_CorrOptNodeSurfaceUniMetric_Iterative_Header

#include <Mesh_Module.hxx>
#include <Aft_OptNode_Corrector.hxx>
#include <Aft2d_CorrOptNodeSurfaceUniMetric_IterativeFwd.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_CorrOptNodeSurfaceUniMetric_Iterative::Perform(const Aft_SizeCorr_IterativeInfo& theInfo);
}

#endif // !_Aft2d_CorrOptNodeSurfaceUniMetric_Iterative_Header
