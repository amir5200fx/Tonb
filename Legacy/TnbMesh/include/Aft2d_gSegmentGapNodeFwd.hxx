#pragma once
#ifndef _Aft2d_gSegmentGapNodeFwd_Header
#define _Aft2d_gSegmentGapNodeFwd_Header

#include <Aft2d_gSegmentNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_gSegmentNode>
		Aft2d_gSegmentGapNode;
}

#endif // !_Aft2d_gSegmentGapNodeFwd_Header
