#pragma once
#ifndef _Cad_gApprxPlnCurveSurfaceFwd_Header
#define _Cad_gApprxPlnCurveSurfaceFwd_Header

#include <Aft2d_gPlnCurveSurfaceFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [4/17/2022 Amir]
	template<class CurveType, bool RandSamples>
	class Cad_ApprxCurve;

	typedef Cad_ApprxCurve<Aft2d_gPlnCurveSurface, true>
		Cad_gApprxPlnCurveSurface;
}

#endif // !_Cad_gApprxPlnCurveSurfaceFwd_Header
