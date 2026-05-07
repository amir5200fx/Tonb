#pragma once
#ifndef _Cad_tPlnGapCurveFwd_Header
#define _Cad_tPlnGapCurveFwd_Header

#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_tPlnCurveSurface>
		Cad_tPlnGapCurve;
}

#endif // !_Cad_tPlnGapCurveFwd_Header
