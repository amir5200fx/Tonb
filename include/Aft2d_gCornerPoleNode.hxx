#pragma once
#ifndef _Aft2d_gCornerPoleNode_Header
#define _Aft2d_gCornerPoleNode_Header

#include <Aft2d_PoleNodeTemplate.hxx>
#include <Aft2d_gCornerPoleNodeFwd.hxx>
#include <Aft2d_gCornerNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_gCornerPoleNode::RemoveThis
	(
		const Geo2d_MetricPrcsrAnIso&
	);
}

#endif // !_Aft2d_gCornerPoleNode_Header
