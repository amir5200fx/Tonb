#pragma once
#ifndef _Aft2d_gPlnWireSurfaceUniMetricFwd_Header
#define _Aft2d_gPlnWireSurfaceUniMetricFwd_Header

#include <Aft2d_gPlnCurveSurfaceUniMetricFwd.hxx>

namespace tnbLib
{
	// Forward Declarations
	template<class PlnCurve> class Mesh_PlnWire;

	typedef Mesh_PlnWire<Aft2d_gPlnCurveSurfaceUniMetric> Aft2d_gPlnWireSurfaceUniMetric;
}

#endif // !_Aft2d_gPlnWireSurfaceUniMetricFwd_Header
