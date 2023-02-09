#pragma once
#ifndef _Aft2d_SegmentGapNodeAnIsoFwd_Header
#define _Aft2d_SegmentGapNodeAnIsoFwd_Header

#include <Aft2d_SegmentNodeAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_SegmentNodeAnIso>
		Aft2d_SegmentGapNodeAnIso;
}

#endif // !_Aft2d_SegmentGapNodeAnIsoFwd_Header
