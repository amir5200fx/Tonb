#pragma once
#ifndef _Aft2d_OptNodeUniMetric_Standard_Header
#define _Aft2d_OptNodeUniMetric_Standard_Header

#include <Aft2d_OptNodeUniMetric_StandardFwd.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_Standard::Perform();
}

#endif // !_Aft2d_OptNodeUniMetric_Standard_Header
