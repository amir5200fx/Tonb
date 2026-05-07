#pragma once
#ifndef _VoyageMesh_NodeBase_Header
#define _VoyageMesh_NodeBase_Header

#include <VoyageMesh_NodeBaseFwd.hxx>
#include <VoyageMesh_NodeTraits.hxx>
#include <Voyage_Module.hxx>
#include <Aft_Node.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT Standard_Real VoyageMesh_NodeBase::CalcMaxParaAdjLength() const;
}

#endif // !_VoyageMesh_NodeBase_Header
