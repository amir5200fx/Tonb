#pragma once
#ifndef _Cad_tPlnGapCurveUniMetricFwd_Header
#define _Cad_tPlnGapCurveUniMetricFwd_Header

#include <Aft2d_tPlnCurveSurfaceUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/20/2022 Amir]
	template<class PlnCurve>
	class Cad_PlnGapCurve;

	typedef Cad_PlnGapCurve<Aft2d_tPlnCurveSurfaceUniMetric>
		Cad_tPlnGapCurveUniMetric;
}

#endif // !_Cad_tPlnGapCurveUniMetricFwd_Header
