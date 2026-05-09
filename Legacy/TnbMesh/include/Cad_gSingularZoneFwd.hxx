#pragma once
#ifndef _Cad_gSingularZoneFwd_Header
#define _Cad_gSingularZoneFwd_Header

#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<Aft2d_gRegionPlaneSurface> Cad_gSingularZone;
}

#endif // !_Cad_gSingularZoneFwd_Header
