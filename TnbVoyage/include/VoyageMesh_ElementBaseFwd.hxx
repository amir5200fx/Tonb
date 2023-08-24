#pragma once
#ifndef _VoyageMesh_ElementBaseFwd_Header
#define _VoyageMesh_ElementBaseFwd_Header

#include <Aft_ElementFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [8/13/2023 aamir]

	struct VoyageMesh_ElementTraits;

	typedef Aft_Element<VoyageMesh_ElementTraits, Mesh_ElementType_Triangle2D>
		VoyageMesh_ElementBase;

}

#endif // !_VoyageMesh_ElementBaseFwd_Header
