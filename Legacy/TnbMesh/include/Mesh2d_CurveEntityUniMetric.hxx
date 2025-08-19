#pragma once
#ifndef _Mesh2d_CurveEntityUniMetric_Header
#define _Mesh2d_CurveEntityUniMetric_Header

#include <Mesh_CurveEntity.hxx>
#include <Geo2d_MetricPrcsrUniMetric.hxx>

#include <opencascade/Geom2d_Curve.hxx>

namespace tnbLib
{
	typedef Mesh_CurveEntity<Geom2d_Curve, Geo2d_MetricPrcsrUniMetric>
		Mesh2d_CurveEntityUniMetric;
}

#endif // !_Mesh2d_CurveEntityUniMetric_Header
