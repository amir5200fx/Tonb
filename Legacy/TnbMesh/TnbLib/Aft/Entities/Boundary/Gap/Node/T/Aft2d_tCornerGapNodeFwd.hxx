#pragma once
#ifndef _Aft2d_gCornerGapNodeFwd_Header
#define _Aft2d_gCornerGapNodeFwd_Header

#include <Aft2d_tCornerNodeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class BndNodeType>
	class Aft2d_GapNodeTemplate;

	typedef Aft2d_GapNodeTemplate<Aft2d_tCornerNode>
		Aft2d_tCornerGapNode;
}

#endif // !_Aft2d_gCornerGapNodeFwd_Header
