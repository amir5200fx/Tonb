#pragma once
#ifndef _Aft2d_OptNodeSurface_nonIterAdaptive_Header
#define _Aft2d_OptNodeSurface_nonIterAdaptive_Header

#include <Aft2d_OptNodeSurface_nonIterAdaptiveFwd.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_nonIterAdaptive::Perform();
}

#endif // !_Aft2d_OptNodeSurface_nonIterAdaptive_Header
