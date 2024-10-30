#pragma once
#ifndef _Mesh2d_CurveFwd_Header
#define _Mesh2d_CurveFwd_Header
#include <Geo2d_MetricPrcsrFwd.hxx>

// Forward Declarations
class Geom2d_Curve;

namespace tnbLib
{
	// Forward Declarations
	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	class Mesh_Curve;

	using Mesh2d_Curve = Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsr, false>;
}
#endif