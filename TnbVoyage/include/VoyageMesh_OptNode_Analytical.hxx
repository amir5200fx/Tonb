#pragma once
#ifndef _VoyageMesh_OptNode_Analytical_Header
#define _VoyageMesh_OptNode_Analytical_Header

#include <VoyageMesh_OptNode_AnalyticalFwd.hxx>
#include <VoyageMesh_Traits.hxx>
#include <Voyage_Module.hxx>
#include <Aft_OptNode_Analytical.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{
	template<>
	void VoyageMesh_OptNode_Analytical::Perform();
}

#endif // !_VoyageMesh_OptNode_Analytical_Header
