#pragma once
#ifndef _Aft2d_CornerGapNode_Header
#define _Aft2d_CornerGapNode_Header

#include <Aft2d_CornerGapNodeFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_CornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdge>
		Aft2d_CornerGapNode::BlowThisUp();
}

#endif // !_Aft2d_CornerGapNode_Header
