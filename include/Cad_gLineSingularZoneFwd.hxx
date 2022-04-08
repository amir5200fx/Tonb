#pragma once
#ifndef _Cad_gLineSingularZoneFwd_Header
#define _Cad_gLineSingularZoneFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class SurfPln>
	class Cad_LineSingularZone;

	class GModel_Plane;

	typedef Cad_LineSingularZone<GModel_Plane> Cad_gLineSingularZone;
}

#endif // !_Cad_gLineSingularZoneFwd_Header
