#pragma once
#ifndef _Cad_tLineSingularCurve_Header
#define _Cad_tLineSingularCurve_Header

#include <Cad_LineSingularCurve.hxx>
#include <Cad_tLineSingularCurveFwd.hxx>
#include <Cad_tSingularCurve.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_tPlnCurveSurface>,
		std::shared_ptr<Aft2d_tPlnCurveSurface>
		>
		Cad_tLineSingularCurve::Split(const Standard_Real x) const;

	template<>
	TnbMesh_EXPORT Standard_Real
		Cad_tLineSingularCurve::ProjectAt
		(
			const Pnt3d& thePnt,
			const TModel_Surface&
		) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_tSegmentEdge>>
		Cad_tLineSingularCurve::TopoMesh<Aft2d_tSegmentEdge>
		(
			const std::shared_ptr<Aft2d_tPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>&
			);
}

#endif // !_Cad_tLineSingularCurve_Header
