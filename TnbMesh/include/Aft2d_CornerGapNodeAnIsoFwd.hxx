#pragma once
#ifndef _Aft2d_CornerGapNodeAnIsoFwd_Header
#define _Aft2d_CornerGapNodeAnIsoFwd_Header

#include <Aft2d_CornerNodeAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_CornerNodeAnIso>
		Aft2d_CornerGapNodeAnIso;
}

#endif // !_Aft2d_CornerGapNodeAnIsoFwd_Header
