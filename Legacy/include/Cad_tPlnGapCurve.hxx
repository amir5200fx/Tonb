#pragma once
#ifndef _Cad_tPlnGapCurve_Header
#define _Cad_tPlnGapCurve_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad_tPlnGapCurveFwd.hxx>
#include <Aft2d_tPlnCurveSurface.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_tPlnCurveSurface>,
		std::shared_ptr<Aft2d_tPlnCurveSurface>
		>
		Cad_tPlnGapCurve::Split(const Standard_Real x) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Cad_tPlnGapCurve::TopoMesh<Aft2d_tSegmentEdge>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_tPlnGapCurve_Header

