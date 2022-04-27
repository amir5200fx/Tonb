#pragma once
#ifndef _Aft2d_gSegmentPoleEdgeFwd_Header
#define _Aft2d_gSegmentPoleEdgeFwd_Header

#include <Aft2d_gSegmentEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/25/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_PoleEdgeTemplate;

	typedef Aft2d_PoleEdgeTemplate<Aft2d_gSegmentEdge>
		Aft2d_gSegmentPoleEdge;
}

#endif // !_Aft2d_gSegmentPoleEdgeFwd_Header
