#pragma once
#ifndef _Aft2d_tSegmentGapNodeFwd_Header
#define _Aft2d_tSegmentGapNodeFwd_Header

#include <Aft2d_tSegmentNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_tSegmentNode>
		Aft2d_tSegmentGapNode;
}

#endif // !_Aft2d_tSegmentGapNodeFwd_Header
