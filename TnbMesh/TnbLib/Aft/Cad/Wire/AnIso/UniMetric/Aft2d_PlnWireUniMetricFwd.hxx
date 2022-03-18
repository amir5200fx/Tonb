#pragma once
#ifndef _Aft2d_PlnWireUniMetricFwd_Header
#define _Aft2d_PlnWireUniMetricFwd_Header

#include <Aft2d_PlnCurveUniMetricFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class PlnCurve> class Mesh_PlnWire;

	typedef Mesh_PlnWire<Aft2d_PlnCurveUniMetric> Aft2d_PlnWireUniMetric;
}

#endif // !_Aft2d_PlnWireUniMetricFwd_Header
