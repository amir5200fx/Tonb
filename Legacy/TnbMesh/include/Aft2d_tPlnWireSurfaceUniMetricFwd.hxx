#pragma once
#ifndef _Aft2d_tPlnWireSurfaceUniMetricFwd_Header
#define _Aft2d_tPlnWireSurfaceUniMetricFwd_Header

#include <Aft2d_tPlnCurveSurfaceUniMetricFwd.hxx>

namespace tnbLib
{
	// Forward Declarations
	template<class PlnCurve> class Mesh_PlnWire;

	typedef Mesh_PlnWire<Aft2d_tPlnCurveSurfaceUniMetric> Aft2d_tPlnWireSurfaceUniMetric;
}

#endif // !_Aft2d_tPlnWireSurfaceUniMetricFwd_Header
