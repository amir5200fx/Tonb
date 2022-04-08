#pragma once
#ifndef _Cad_gPoleSingularCurveFwd_Header
#define _Cad_gPoleSingularCurveFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_PoleSingularCurve;

	typedef Cad_PoleSingularCurve<Aft2d_gPlnCurveSurface> Cad_gPoleSingularCurve;
}

#endif // !_Cad_gPoleSingularCurveFwd_Header
