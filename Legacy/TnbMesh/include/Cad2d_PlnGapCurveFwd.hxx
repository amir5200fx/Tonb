#pragma once
#ifndef _Cad2d_PlnGapCurveFwd_Header
#define _Cad2d_PlnGapCurveFwd_Header

#include <Aft2d_PlnCurveFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_PlnCurve>
		Cad2d_PlnGapCurve;
}

#endif // !_Cad2d_PlnGapCurveFwd_Header
