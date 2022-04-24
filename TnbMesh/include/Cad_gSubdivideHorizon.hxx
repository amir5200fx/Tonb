#pragma once
#ifndef _Cad_gSubdivideHorizon_Header
#define _Cad_gSubdivideHorizon_Header

#include <Cad_SubdivideHorizon.hxx>
#include <Cad_gSubdivideHorizonFwd.hxx>
#include <Mesh_Module.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Cad_gSubdivideHorizon::Perform
	(
		const std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>& theCurves
	);
}
#endif // _DEBUG


#endif // !_Cad_gSubdivideHorizon_Header
