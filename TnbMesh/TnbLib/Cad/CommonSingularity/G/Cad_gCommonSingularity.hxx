#pragma once
#ifndef _Cad_gCommonSingularity_Header
#define _Cad_gCommonSingularity_Header

#include <Cad_CommonSingularity.hxx>
#include <Cad_gCommonSingularityFwd.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Cad_gCommonSingularity::Perform();
}

#endif // !_Cad_gCommonSingularity_Header
