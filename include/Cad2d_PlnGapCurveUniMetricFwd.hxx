#pragma once
#ifndef _Cad2d_PlnGapCurveUniMetricFwd_Header
#define _Cad2d_PlnGapCurveUniMetricFwd_Header

#include <Aft2d_PlnCurveUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [1/24/2023 Payvand]

	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_PlnCurveUniMetric>
		Cad2d_PlnGapCurveUniMetric;
}

#endif // !_Cad2d_PlnGapCurveUniMetricFwd_Header
