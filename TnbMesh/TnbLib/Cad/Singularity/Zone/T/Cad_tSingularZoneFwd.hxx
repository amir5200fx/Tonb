#pragma once
#ifndef _Cad_tSingularZoneFwd_Header
#define _Cad_tSingularZoneFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]
	class TModel_Plane;

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<TModel_Plane> Cad_tSingularZone;
}

#endif // !_Cad_tSingularZoneFwd_Header
