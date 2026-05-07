#pragma once
#ifndef _Mesh2d_Curve_Header
#define _Mesh2d_Curve_Header

#include <Mesh2d_CurveFwd.hxx>
#include <Mesh_Curve.hxx>
#include <Mesh2d_CurveEntity.hxx>

namespace tnbLib
{
	template<>
	inline const Pnt2d& Entity_Polygon<std::pair<Pnt2d, Standard_Real>>::Coord(const Standard_Integer) const;
	template<>
	inline Pnt2d& Entity_Polygon<std::pair<Pnt2d, Standard_Real>>::Coord(const Standard_Integer);

	template<>
	TnbMesh_EXPORT void Mesh_Curve<Geom2d_Curve, Geo2d_MetricPrcsr, true>::MakeChain
	(
		const std::vector<Standard_Real>& theParameters
	);
}

#include <Mesh2d_CurveI.hxx>

#endif // !_Mesh2d_Curve_Header