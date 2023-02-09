#pragma once
#ifndef _Aft2d_SegmentGapEdgeAnIsoFwd_Header
#define _Aft2d_SegmentGapEdgeAnIsoFwd_Header

#include <Aft2d_SegmentEdgeAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndEdgeType>
	class Aft2d_GapEdgeTemplate;

	typedef Aft2d_GapEdgeTemplate<Aft2d_SegmentEdgeAnIso>
		Aft2d_SegmentGapEdgeAnIso;
}

#endif // !_Aft2d_SegmentGapEdgeAnIsoFwd_Header
