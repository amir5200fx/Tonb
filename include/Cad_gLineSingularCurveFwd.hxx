#pragma once
#ifndef _Cad_gLineSingularCurveFwd_Header
#define _Cad_gLineSingularCurveFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_LineSingularCurve;

	class GModel_ParaCurve;

	typedef Cad_LineSingularCurve<Aft2d_gPlnCurveSurface> Cad_gLineSingularCurve;
}

#endif // !_Cad_gLineSingularCurveFwd_Header
