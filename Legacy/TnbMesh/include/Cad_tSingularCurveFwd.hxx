#pragma once
#ifndef _Cad_tSingularCurveFwd_Header
#define _Cad_tSingularCurveFwd_Header

#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_SingularCurve;

	typedef Cad_SingularCurve<Aft2d_tPlnCurveSurface> Cad_tSingularCurve;
}

#endif // !_Cad_tSingularCurveFwd_Header
