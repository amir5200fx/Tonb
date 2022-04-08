#pragma once
#ifndef _Cad_gSingularityBaseFwd_Header
#define _Cad_gSingularityBaseFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/30/2022 Amir]
	template<class CurveType>
	class Cad_SingularityBase;

	typedef Cad_SingularityBase<Aft2d_gPlnCurveSurface> Cad_gSingularityBase;
}

#endif // !_Cad_gSingularityBaseFwd_Header
