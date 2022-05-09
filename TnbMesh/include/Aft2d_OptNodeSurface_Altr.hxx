#pragma once
#ifndef _Aft2d_OptNodeSurface_Altr_Header
#define _Aft2d_OptNodeSurface_Altr_Header

#include <Aft_OptNode.hxx>
#include <Aft2d_OptNodeSurface_AltrFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeSurface_Altr::Perform();
}

#endif // !_Aft2d_OptNodeSurface_Altr_Header
