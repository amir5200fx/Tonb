#pragma once
#ifndef _Mesh2d_CurveAnIsoFwd_Header
#define _Mesh2d_CurveAnIsoFwd_Header

#include <Geo2d_MetricPrcsrAnIsoFwd.hxx>

class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [10/26/2022 Amir]
	template<class gCurveType, class MetricPrcsrType, bool SavePars>
	class Mesh_Curve;

	typedef Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsrAnIso, false>
		Mesh2d_CurveAnIso;
}

#endif // !_Mesh2d_CurveAnIsoFwd_Header
