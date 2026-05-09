#pragma once
#ifndef _Aft2d_gCornerGapNodeFwd_Header
#define _Aft2d_gCornerGapNodeFwd_Header

#include <Aft2d_gCornerNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_gCornerNode>
		Aft2d_gCornerGapNode;
}

#endif // !_Aft2d_gCornerGapNodeFwd_Header
