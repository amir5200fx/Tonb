#pragma once
#ifndef _Aft2d_tCornerLineNodeFwd_Header
#define _Aft2d_tCornerLineNodeFwd_Header

#include <Aft2d_tCornerNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/25/2022 Amir]
	template<class BndNodeType>
	class Aft2d_LineNodeTemplate;

	typedef Aft2d_LineNodeTemplate<Aft2d_tCornerNode>
		Aft2d_tCornerLineNode;
}

#endif // !_Aft2d_tCornerLineNodeFwd_Header
