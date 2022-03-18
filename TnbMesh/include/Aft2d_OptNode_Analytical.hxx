#pragma once
#ifndef _Aft2d_OptNode_Analytical_Header
#define _Aft2d_OptNode_Analytical_Header

#include <Aft2d_OptNode_AnalyticalFwd.hxx>
#include <Aft_OptNode_Analytical.hxx>
#include <Aft2d_Edge.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNode_Analytical::Perform();
}

#endif // !_Aft2d_OptNode_Analytical_Header