#pragma once
#ifndef _VoyageMesh_Core_Header
#define _VoyageMesh_Core_Header

#include <VoyageMesh_CoreFwd.hxx>
#include <VoyageMesh_CoreTemplate.hxx>
#include <VoyageMesh_OptNode_Calculator.hxx>
#include <VoyageMesh_CoreBase.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>

namespace tnbLib
{

	typedef VoyageMesh_CoreTemplate
		<
		VoyageMesh_OptNode_Calculator,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		> VoyageMesh_Core;
}

#endif // !_VoyageMesh_Core_Header
