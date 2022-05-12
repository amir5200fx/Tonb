#pragma once
#ifndef _Cad_gModifySingularPlane_Header
#define _Cad_gModifySingularPlane_Header

#include <Cad_ModifySingularPlane.hxx>
#include <Cad_gModifySingularPlaneFwd.hxx>

#ifdef _DEBUG
namespace tnbLib
{
	template<>
	TnbMesh_EXPORT void Cad_gModifySingularPlane::RemoveColoredEdges
	(
		Cad_SingularityTopology<GModel_Surface>& theTopo,
		const Cad_ColorApprxMetric & theColors,
		const Cad_SingularityTopology<GModel_Surface>::edgeToCurveMap & theEdgeToCurve, 
		const std::map<std::shared_ptr<Aft2d_gPlnCurveSurface>, Cad_ModifySingularPlaneToolsBase::pCurveType>& theMap,
		std::map<std::shared_ptr<Geo_TopoChainAnalysis_Entity<Geo2d_SegmentGraphEdge>>, Standard_Integer>& theColored
	);

	template<>
	TnbMesh_EXPORT void Cad_gModifySingularPlane::Perform();
}
#endif // _DEBUG


#endif // !_Cad_gModifySingularPlane_Header
