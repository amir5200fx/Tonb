#pragma once
#ifndef _Aft2d_SegmentGapNodeFwd_Header
#define _Aft2d_SegmentGapNodeFwd_Header

#include <Aft2d_SegmentNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_SegmentNode>
		Aft2d_SegmentGapNode;
}

#endif // !_Aft2d_SegmentGapNodeFwd_Header
