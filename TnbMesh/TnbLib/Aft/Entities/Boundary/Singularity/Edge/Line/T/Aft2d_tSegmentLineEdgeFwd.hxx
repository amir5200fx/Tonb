#pragma once
#ifndef _Aft2d_tSegmentLineEdgeFwd_Header
#define _Aft2d_tSegmentLineEdgeFwd_Header

#include <Aft2d_tSegmentEdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/25/2022 Amir]
	template<class BndEdgeType>
	class Aft2d_LineEdgeTemplate;

	typedef Aft2d_LineEdgeTemplate<Aft2d_tSegmentEdge>
		Aft2d_tSegmentLineEdge;
}

#endif // !_Aft2d_tSegmentLineEdgeFwd_Header
