#pragma once
#ifndef _Cad_gPlnGapCurveUniMetricFwd_Header
#define _Cad_gPlnGapCurveUniMetricFwd_Header

#include <Aft2d_gPlnCurveSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [5/13/2022 Amir]
	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_gPlnCurveSurfaceUniMetric>
		Cad_gPlnGapCurveUniMetric;
}

#endif // !_Cad_gPlnGapCurveUniMetricFwd_Header
