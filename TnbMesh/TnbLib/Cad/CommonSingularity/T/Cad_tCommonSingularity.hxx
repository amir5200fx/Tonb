#pragma once
#ifndef _Cad_tCommonSingularity_Header
#define _Cad_tCommonSingularity_Header

#include <Cad_CommonSingularity.hxx>
#include <Cad_tCommonSingularityFwd.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Cad_tCommonSingularity::Perform();
}

#endif // !_Cad_tCommonSingularity_Header
