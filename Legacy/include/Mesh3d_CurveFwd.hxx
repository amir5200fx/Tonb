#pragma once
#ifndef _Mesh3d_CurveFwd_Header
#define _Mesh3d_CurveFwd_Header
#include <Geo3d_MetricPrcsrFwd.hxx>

// Forward Declarations
class Geom_Curve;

namespace tnbLib
{
	// Forward Declarations
	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	class Mesh_Curve;

	using Mesh3d_Curve = Mesh_Curve<Geom_Curve, Geo3d_MetricPrcsr, false>;
}
#endif