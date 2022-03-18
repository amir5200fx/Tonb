#pragma once
#ifndef _Mesh2d_CurveUniMetric_Header
#define _Mesh2d_CurveUniMetric_Header

#include <Mesh_Curve.hxx>
#include <Mesh2d_CurveEntityUniMetric.hxx>

namespace tnbLib
{
	typedef Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Mesh2d_CurveUniMetric;
}

#endif // !_Mesh2d_CurveUniMetric_Header
