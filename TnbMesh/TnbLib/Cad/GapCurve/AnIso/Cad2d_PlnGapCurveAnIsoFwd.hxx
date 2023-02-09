#pragma once
#ifndef _Cad2d_PlnGapCurveAnIsoFwd_Header
#define _Cad2d_PlnGapCurveAnIsoFwd_Header

#include <Aft2d_PlnCurveAnIsoFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_PlnCurveAnIso>
		Cad2d_PlnGapCurveAnIso;
}

#endif // !_Cad2d_PlnGapCurveAnIsoFwd_Header
