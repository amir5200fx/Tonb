#pragma once
#ifndef _Cad_gSingularityTopology_Header
#define _Cad_gSingularityTopology_Header

#include <Cad_SingularityTopology.hxx>
#include <Cad_gSingularityTopologyFwd.hxx>
#include <Mesh_Module.hxx>

#ifdef _DEBUG
namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Cad_gSingularityTopology::Perform();

	template<>
	TnbMesh_EXPORT std::shared_ptr<Geo2d_TopoChainAnalysis>
		Cad_gSingularityTopology::GetTopology
		(
			const std::map<std::shared_ptr<Aft2d_gPlnCurveSurface>, std::shared_ptr<Entity2d_Chain>>& theCurves, 
			std::map<std::shared_ptr<Geo2d_SegmentGraphEdge>, std::shared_ptr<Aft2d_gPlnCurveSurface>>& theEdges
		);
}
#endif // _DEBUG


#endif // !_Cad_gSingularityTopology_Header
