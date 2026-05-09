#pragma once
#ifndef _MeshPostAF2d_ElementBase_Header
#define _MeshPostAF2d_ElementBase_Header

#include <MeshPostAF2d_ElementBaseFwd.hxx>
#include <MeshPostAF2d_ElementTraits.hxx>
#include <MeshPostAF2d_Node.hxx>
#include <MeshPostAF2d_Traits.hxx>
#include <Aft_Element.hxx>

namespace tnbLib
{
	template<>
	MeshPostAF2d_ElementBase::array3
		MeshPostAF2d_ElementBase::InterpWeights(const Pnt2d& theCoord) const;
}

#endif // !_MeshPostAF2d_ElementBase_Header
