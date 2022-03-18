#pragma once
#ifndef _Aft2d_OptNode_IterAdaptive_Header
#define _Aft2d_OptNode_IterAdaptive_Header

#include <Aft2d_OptNode_IterAdaptiveFwd.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNode_IterAdaptive::Perform();
}

#endif // !_Aft2d_OptNode_IterAdaptive_Header
