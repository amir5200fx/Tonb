#pragma once
#ifndef _Cad_gSingularZoneFwd_Header
#define _Cad_gSingularZoneFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]
	class GModel_Plane;

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<GModel_Plane> Cad_gSingularZone;
}

#endif // !_Cad_gSingularZoneFwd_Header
