#pragma once
#ifndef _Aft2d_gCornerGapNode_Header
#define _Aft2d_gCornerGapNode_Header

#include <Aft2d_gCornerGapNodeFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_gCornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_gCornerGapNode::BlowThisUp(const Geo2d_MetricPrcsrAnIso&);
}

#endif // !_Aft2d_gCornerGapNode_Header
