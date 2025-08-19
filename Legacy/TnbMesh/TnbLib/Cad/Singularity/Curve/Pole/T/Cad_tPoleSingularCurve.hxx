#pragma once
#ifndef _Cad_tPoleSingularCurve_Header
#define _Cad_tPoleSingularCurve_Header

#include <Cad_PoleSingularCurve.hxx>
#include <Cad_tPoleSingularCurveFwd.hxx>
#include <Cad_tSingularCurve.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_tPlnCurveSurface>,
		std::shared_ptr<Aft2d_tPlnCurveSurface>
		>
		Cad_tPoleSingularCurve::Split(const Standard_Real x) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Cad_tPoleSingularCurve::TopoMesh<Aft2d_tSegmentEdge>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_tPoleSingularCurve_Header
