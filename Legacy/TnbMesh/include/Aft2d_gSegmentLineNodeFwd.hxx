#pragma once
#ifndef _Aft2d_gSegmentLineNodeFwd_Header
#define _Aft2d_gSegmentLineNodeFwd_Header

#include <Aft2d_gSegmentNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/25/2022 Amir]
	template<class BndNodeType>
	class Aft2d_LineNodeTemplate;

	typedef Aft2d_LineNodeTemplate<Aft2d_gSegmentNode>
		Aft2d_gSegmentLineNode;
}

#endif // !_Aft2d_gSegmentLineNodeFwd_Header
