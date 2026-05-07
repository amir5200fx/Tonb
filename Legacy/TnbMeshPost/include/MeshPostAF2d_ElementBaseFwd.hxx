#pragma once
#ifndef _MeshPostAF2d_ElementBaseFwd_Header
#define _MeshPostAF2d_ElementBaseFwd_Header

#include <Aft_ElementFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/31/2023 aamir]

	struct MeshPostAF2d_ElementTraits;
	typedef Aft_Element<MeshPostAF2d_ElementTraits, Mesh_ElementType_Triangle2D>
		MeshPostAF2d_ElementBase;

}

#endif // !_MeshPostAF2d_ElementBaseFwd_Header
