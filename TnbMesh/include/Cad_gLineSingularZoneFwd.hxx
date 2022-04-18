#pragma once
#ifndef _Cad_gLineSingularZoneFwd_Header
#define _Cad_gLineSingularZoneFwd_Header

#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class SurfPln>
	class Cad_LineSingularZone;

	class GModel_Plane;

	typedef Cad_LineSingularZone<Aft2d_gRegionPlaneSurface> Cad_gLineSingularZone;
}

#endif // !_Cad_gLineSingularZoneFwd_Header
