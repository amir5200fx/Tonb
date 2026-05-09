#pragma once
#ifndef _Aft2d_OptNodeUniMetric_Standard_Header
#define _Aft2d_OptNodeUniMetric_Standard_Header

#include <Aft2d_OptNodeUniMetric_StandardFwd.hxx>
#include <Aft2d_OptNodeUniMetric_Calculator.hxx>
#include <Aft_OptNode.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_OptNodeUniMetric_Standard::Perform();
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_OptNodeUniMetric_Standard);

#endif // !_Aft2d_OptNodeUniMetric_Standard_Header
