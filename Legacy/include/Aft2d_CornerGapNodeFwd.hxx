#pragma once
#ifndef _Aft2d_CornerGapNodeFwd_Header
#define _Aft2d_CornerGapNodeFwd_Header

#include <Aft2d_CornerNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_CornerNode>
		Aft2d_CornerGapNode;
}

#endif // !_Aft2d_CornerGapNodeFwd_Header
