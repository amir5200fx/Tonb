#pragma once
#ifndef _Cad_gSingularCurveFwd_Header
#define _Cad_gSingularCurveFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_SingularCurve;

	typedef Cad_SingularCurve<Aft2d_gPlnCurveSurface> Cad_gSingularCurve;
}

#endif // !_Cad_gSingularCurveFwd_Header
