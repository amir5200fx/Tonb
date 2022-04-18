#pragma once
#ifndef _Cad_ApprxPlnWireSurfaceTraits_Header
#define _Cad_ApprxPlnWireSurfaceTraits_Header

#include <Cad_ApprxWireTraits.hxx>
#include <Aft2d_gPlnCurveSurfaceFwd.hxx>
#include <Aft2d_tPlnCurveSurfaceFwd.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>
#include <Aft2d_tPlnWireSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	struct cad_apprx_wire_traits<Aft2d_gPlnWireSurface> { typedef Aft2d_gPlnCurveSurface curveType; };

	template<>
	struct cad_apprx_wire_traits<Aft2d_tPlnWireSurface> { typedef Aft2d_tPlnCurveSurface curveType; };
}

#endif // !_Cad_ApprxPlnWireSurfaceTraits_Header
