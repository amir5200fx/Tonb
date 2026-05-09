#pragma once
#ifndef _Aft2d_gCornerGapNode_Header
#define _Aft2d_gCornerGapNode_Header

#include <Aft2d_gCornerGapNodeFwd.hxx>
#include <Aft2d_GapNodeTemplate.hxx>
#include <Aft2d_gCornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeSurface> 
		Aft2d_gCornerGapNode::BlowThisUp();
}

#endif // !_Aft2d_gCornerGapNode_Header
