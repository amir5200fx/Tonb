#pragma once
#ifndef _MeshPostAF2d_Core_Header
#define _MeshPostAF2d_Core_Header

#include <MeshPostAF2d_CoreFwd.hxx>
#include <MeshPostAF2d_CoreTemplate.hxx>
#include <MeshPostAF2d_OptNode_Calculator.hxx>
#include <MeshPostAF2d_CoreBase.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>

namespace tnbLib
{

	typedef MeshPostAF2d_CoreTemplate
		<
		VoyageMesh_OptNode_Calculator,
		Geo2d_SizeFunction,
		Geo2d_MetricFunction
		> VoyageMesh_Core;
}

#endif // !_MeshPostAF2d_Core_Header
