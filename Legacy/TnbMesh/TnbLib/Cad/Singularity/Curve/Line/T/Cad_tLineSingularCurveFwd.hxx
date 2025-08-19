#pragma once
#ifndef _Cad_tLineSingularCurveFwd_Header
#define _Cad_tLineSingularCurveFwd_Header

#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_LineSingularCurve;

	class TModel_ParaCurve;

	typedef Cad_LineSingularCurve<Aft2d_tPlnCurveSurface> Cad_tLineSingularCurve;
}

#endif // !_Cad_tLineSingularCurveFwd_Header
