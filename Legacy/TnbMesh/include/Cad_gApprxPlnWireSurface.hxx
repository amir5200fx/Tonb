#pragma once
#ifndef _Cad_ApprxPlnWireSurface_Header
#define _Cad_ApprxPlnWireSurface_Header

#include <Cad_ApprxPlnWireSurfaceTraits.hxx>
#include <Cad_ApprxWire.hxx>
#include <Cad_gApprxPlnWireSurfaceFwd.hxx>
#include <Cad_gApprxPlnCurveSurface.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gPlnCurveSurface>>
		Cad_gApprxPlnWireSurface::RetrieveCurves
		(
			const Aft2d_gPlnWireSurface&
		);
}

#endif // !_Cad_ApprxPlnWireSurface_Header
