#pragma once
#ifndef _Aft2d_tSegmentGapEdgeFwd_Header
#define _Aft2d_tSegmentGapEdgeFwd_Header

#include <Aft2d_tSegmentEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_tSegmentEdge>
		Aft2d_tSegmentGapEdge;
}

#endif // !_Aft2d_tSegmentGapEdgeFwd_Header
