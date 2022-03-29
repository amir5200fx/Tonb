#pragma once
#ifndef _Cad_gSingularZoneFwd_Header
#define _Cad_gSingularZoneFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]
	class GModel_Surface;

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<GModel_Surface> Cad_gSingularZone;
}

#endif // !_Cad_gSingularZoneFwd_Header
