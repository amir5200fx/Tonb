#pragma once
#ifndef _VoyageMesh_ElementBase_Header
#define _VoyageMesh_ElementBase_Header

#include <VoyageMesh_ElementBaseFwd.hxx>
#include <VoyageMesh_ElementTraits.hxx>
#include <VoyageMesh_Node.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Aft_Element.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT VoyageMesh_ElementBase::array3
		VoyageMesh_ElementBase::InterpWeights(const Pnt2d& theCoord) const;
}

#endif // !_VoyageMesh_ElementBase_Header
