#pragma once
#ifndef _Cad_gPlnGapCurve_Header
#define _Cad_gPlnGapCurve_Header

#include <Cad_PlnGapCurve.hxx>
#include <Cad_gPlnGapCurveFwd.hxx>
#include <Aft2d_gPlnCurveSurface.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_gPlnCurveSurface>,
		std::shared_ptr<Aft2d_gPlnCurveSurface>
		>
		Cad_gPlnGapCurve::Split(const Standard_Real x) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Cad_gPlnGapCurve::TopoMesh<Aft2d_gSegmentEdge>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_gPlnGapCurve_Header
