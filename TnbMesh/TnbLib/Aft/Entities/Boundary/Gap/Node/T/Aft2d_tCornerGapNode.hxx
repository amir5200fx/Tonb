#pragma once
#ifndef _Aft2d_tCornerGapNode_Header
#define _Aft2d_tCornerGapNode_Header

#include <Aft2d_tCornerGapNodeFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_tCornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeSurface>
		Aft2d_tCornerGapNode::BlowThisUp();
}

#endif // !_Aft2d_tCornerGapNode_Header
