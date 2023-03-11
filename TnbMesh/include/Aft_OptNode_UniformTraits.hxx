#pragma once
#ifndef _Aft_OptNode_UniformTraits_Header
#define _Aft_OptNode_UniformTraits_Header

#include <Aft2d_OptNode_AnalyticalFwd.hxx>
#include <Aft2d_EdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/1/2022 Amir]

	template<class T>
	struct analytical_optNode_calculator {};

	template<> struct analytical_optNode_calculator<Aft2d_Edge> { typedef Aft2d_OptNode_Analytical calcType; };
}

#endif // !_Aft_OptNode_UniformTraits_Header
