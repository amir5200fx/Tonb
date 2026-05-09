#pragma once
#ifndef _Geo2d_TopoChainAnalysis_Header
#define _Geo2d_TopoChainAnalysis_Header

#include <Geo_TopoChainAnalysis.hxx>
#include <Geo2d_TopoChainAnalysisFwd.hxx>
#include <Geo2d_TopoChainAnalysis_Node.hxx>
#include <Geo2d_SegmentGraphEdge.hxx>
#include <Geo2d_RingGraphEdge.hxx>
#include <Geo2d_TopoChainAnalysisTraits.hxx>
#include <Entity2d_Chain.hxx>

#ifdef _DEBUG
namespace tnbLib
{

	template<>
	TnbGeo_EXPORT std::shared_ptr<Geo2d_TopoChainAnalysis_Node> 
		Geo2d_TopoChainAnalysis::Next
		(
			const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>&, 
			std::shared_ptr<Geo2d_SegmentGraphEdge>&
		);

	template<>
	TnbGeo_EXPORT std::shared_ptr<typename Geo2d_TopoChainAnalysis::entityType> 
		Geo2d_TopoChainAnalysis::GetRing
		(
			const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>&
		);

	template<>
	TnbGeo_EXPORT void Geo2d_TopoChainAnalysis::SetType
	(
		const std::shared_ptr<Geo2d_TopoChainAnalysis_Node>&
	) const;

	template<>
	TnbGeo_EXPORT void Geo2d_TopoChainAnalysis::Perform();

	template<>
	TnbGeo_EXPORT void Geo2d_TopoChainAnalysis::Import(const Entity2d_Chain&);

}
#endif // _DEBUG


#endif // !_Geo2d_TopoChainAnalysis_Header
