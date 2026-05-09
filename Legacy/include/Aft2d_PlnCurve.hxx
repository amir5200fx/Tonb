#pragma once
#ifndef _Aft2d_PlnCurve_Header
#define _Aft2d_PlnCurve_Header

#include <Mesh2d_PlnCurve.hxx>
#include <Aft2d_PlnCurveFwd.hxx>
#include <Geo2d_MetricPrcsr.hxx>
#include <Aft2d_SegmentEdgeFwd.hxx>


namespace tnbLib
{

	template<>
	static TnbMesh_EXPORT std::shared_ptr<Entity2d_Polygon>
		Mesh_PlnCurve_Base::Mesh<Geo2d_SizeFunction>
		(
			const Handle(Geom2d_Curve)& theCurve,
			const Standard_Real theU0,
			const Standard_Real theU1,
			const std::shared_ptr<Geo2d_MetricPrcsr>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdge>>
		Aft2d_PlnCurve::TopoMesh<Aft2d_SegmentEdge>
		(
			const std::shared_ptr<Aft2d_PlnCurve>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsr>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Aft2d_PlnCurve_Header