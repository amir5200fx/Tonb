#pragma once
#ifndef _VoyageMesh_OptNode_Standard_Header
#define _VoyageMesh_OptNode_Standard_Header

#include <VoyageMesh_OptNode_StandardFwd.hxx>
#include <VoyageMesh_OptNode_Calculator.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Voyage_Module.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT void VoyageMesh_OptNode_Standard::Perform();
}

#endif // !_VoyageMesh_OptNode_Standard_Header
