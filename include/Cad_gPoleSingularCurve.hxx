#pragma once
#ifndef _Cad_gPoleSingularCurve_Header
#define _Cad_gPoleSingularCurve_Header

#include <Cad_PoleSingularCurve.hxx>
#include <Cad_gPoleSingularCurveFwd.hxx>
#include <Cad_gSingularCurve.hxx>

namespace tnbLib
{

	template<>
	template<>
	static TnbMesh_EXPORT std::vector<std::shared_ptr<Aft2d_gSegmentEdge>> 
		Cad_gPoleSingularCurve::TopoMesh<Aft2d_gSegmentEdge>
		(
			const std::shared_ptr<Aft2d_gPlnCurveSurface>& theCurve,
			const std::shared_ptr<Geo2d_MetricPrcsrAnIso>& theMap, 
			const std::shared_ptr<Mesh_Curve_Info>& theInfo
			);
}

#endif // !_Cad_gPoleSingularCurve_Header
