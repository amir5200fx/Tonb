#pragma once
#ifndef _Cad_tApprxPlnCurveSurfaceFwd_Header
#define _Cad_tApprxPlnCurveSurfaceFwd_Header

#include <Aft2d_tPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/17/2022 Amir]
	template<class CurveType, bool RandSamples>
	class Cad_ApprxCurve;

	typedef Cad_ApprxCurve<Aft2d_tPlnCurveSurface, true>
		Cad_tApprxPlnCurveSurface;
}

#endif // !_Cad_tApprxPlnCurveSurfaceFwd_Header
