#pragma once
#ifndef _Cad_tPoleSingularCurveFwd_Header
#define _Cad_tPoleSingularCurveFwd_Header

#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/5/2022 Amir]
	template<class CurveType>
	class Cad_PoleSingularCurve;

	typedef Cad_PoleSingularCurve<Aft2d_tPlnCurveSurface> Cad_tPoleSingularCurve;
}

#endif // !_Cad_tPoleSingularCurveFwd_Header
