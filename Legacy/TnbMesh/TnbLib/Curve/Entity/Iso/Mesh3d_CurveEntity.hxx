#pragma once
#ifndef _Mesh3d_CurveEntity_Header
#define _Mesh3d_CurveEntity_Header
#include <Mesh_CurveEntity.hxx>
#include <Geo3d_MetricPrcsr.hxx>

#include <opencascade/Geom_Curve.hxx>

namespace tnbLib
{
	using Mesh3d_CurveEntity = Mesh_CurveEntity<Geom_Curve, Geo3d_MetricPrcsr>;
}
#endif