#pragma once
#ifndef _Cad_tSingularZoneFwd_Header
#define _Cad_tSingularZoneFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/29/2022 Amir]
	class TModel_Surface;

	template<class SurfPln>
	class Cad_SingularZone;

	typedef Cad_SingularZone<TModel_Surface> Cad_tSingularZone;
}

#endif // !_Cad_tSingularZoneFwd_Header
