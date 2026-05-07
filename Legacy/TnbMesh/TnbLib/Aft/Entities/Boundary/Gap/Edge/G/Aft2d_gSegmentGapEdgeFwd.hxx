#pragma once
#ifndef _Aft2d_gSegmentGapEdgeFwd_Header
#define _Aft2d_gSegmentGapEdgeFwd_Header

#include <Aft2d_gSegmentEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/12/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_gSegmentEdge>
		Aft2d_gSegmentGapEdge;
}

#endif // !_Aft2d_gSegmentGapEdgeFwd_Header
