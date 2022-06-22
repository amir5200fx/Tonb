#pragma once
#ifndef _Aft2d_tCornerPoleNode_Header
#define _Aft2d_tCornerPoleNode_Header

#include <Aft2d_PoleNodeTemplate.hxx>
#include <Aft2d_tCornerPoleNodeFwd.hxx>
#include <Aft2d_tCornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_BndEdgeSurface> Aft2d_tCornerPoleNode::BlowThisUp();

	template<>
	TnbMesh_EXPORT void Aft2d_tCornerPoleNode::RemoveThis
	(
		const Geo2d_MetricPrcsrAnIso&
	);
}

#endif // !_Aft2d_tCornerPoleNode_Header
