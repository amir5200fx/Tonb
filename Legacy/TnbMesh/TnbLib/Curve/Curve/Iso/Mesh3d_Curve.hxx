#pragma once
#ifndef _Mesh3d_Curve_Header
#define _Mesh3d_Curve_Header
#include <Mesh3d_CurveFwd.hxx>
#include <Mesh3d_CurveEntity.hxx>
#include <Mesh_Curve.hxx>

namespace tnbLib
{
	template<>
	inline const Pnt3d& Entity_Polygon<std::pair<Pnt3d, Standard_Real>>::Coord(const Standard_Integer) const;
	template<>
	inline Pnt3d& Entity_Polygon<std::pair<Pnt3d, Standard_Real>>::Coord(const Standard_Integer);

	template<>
	TnbMesh_EXPORT void Mesh_Curve<Geom_Curve, Geo3d_MetricPrcsr, true>::MakeChain(
		const std::vector<Standard_Real>& theParams);
}

#include <Mesh3d_CurveI.hxx>

#endif