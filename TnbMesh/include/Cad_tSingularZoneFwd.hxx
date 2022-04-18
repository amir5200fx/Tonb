#pragma once
#ifndef _Cad_tSingularZoneFwd_Header
#define _Cad_tSingularZoneFwd_Header

#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<Aft2d_tRegionPlaneSurface> Cad_tSingularZone;
}

#endif // !_Cad_tSingularZoneFwd_Header
