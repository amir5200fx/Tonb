#pragma once
#ifndef _Cad2d_PlnGapCurve_Header
#define _Cad2d_PlnGapCurve_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad2d_PlnGapCurveFwd.hxx>
#include <Aft2d_PlnCurve.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_PlnCurve>, 
		std::shared_ptr<Aft2d_PlnCurve>
		> 
		Cad2d_PlnGapCurve::Split(const Standard_Real x) const;

	template<>
	template<>
	TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_SegmentEdge>>
		Cad2d_PlnGapCurve::TopoMesh<Aft2d_SegmentEdge>
		(
			const std::shared_ptr<Aft2d_PlnCurve>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsr>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad2d_PlnGapCurve_Header
