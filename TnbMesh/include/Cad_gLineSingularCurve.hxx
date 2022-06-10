#pragma once
#ifndef _Cad_gLineSingularCurve_Header
#define _Cad_gLineSingularCurve_Header

#include <Cad_LineSingularCurve.hxx>
#include <Cad_gLineSingularCurveFwd.hxx>
#include <Cad_gSingularCurve.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT std::pair
		<
		std::shared_ptr<Aft2d_gPlnCurveSurface>, 
		std::shared_ptr<Aft2d_gPlnCurveSurface>
		> 
		Cad_gLineSingularCurve::Split(const Standard_Real x) const;

	template<>
	TnbMesh_EXPORT Standard_Real 
		Cad_gLineSingularCurve::ProjectAt
		(
			const Pnt3d& thePnt,
			const GModel_Surface&
		) const;

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>>
		Cad_gLineSingularCurve::TopoMesh<Aft2d_gSegmentEdge>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap,
			const std::shared_ptr<Mesh_Curve_Info>&
			);
}

#endif // !_Cad_gLineSingularCurve_Header
