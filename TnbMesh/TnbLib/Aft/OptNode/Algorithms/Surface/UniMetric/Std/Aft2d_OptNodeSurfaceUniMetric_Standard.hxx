#pragma once
#ifndef _Aft2d_OptNodeSurfaceUniMetric_Standard_Header
#define _Aft2d_OptNodeSurfaceUniMetric_Standard_Header

#include <Aft2d_OptNodeSurfaceUniMetric_StandardFwd.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurfaceUniMetric_Standard::Perform();
}

#endif // !_Aft2d_OptNodeSurfaceUniMetric_Standard_Header
