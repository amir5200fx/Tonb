#pragma once
#ifndef _Cad_gPlnGapCurveFwd_Header
#define _Cad_gPlnGapCurveFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_gPlnCurveSurface>
		Cad_gPlnGapCurve;
}

#endif // !_Cad_gPlnGapCurveFwd_Header

