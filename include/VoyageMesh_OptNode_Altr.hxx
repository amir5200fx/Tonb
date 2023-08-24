#pragma once
#ifndef _VoyageMesh_OptNode_Altr_Header
#define _VoyageMesh_OptNode_Altr_Header

#include <VoyageMesh_OptNode_AltrFwd.hxx>
#include <VoyageMesh_OptNode_Calculator.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Voyage_Module.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbVoyage_EXPORT void VoyageMesh_OptNode_Altr::Perform();
}

#endif // !_VoyageMesh_OptNode_Altr_Header
