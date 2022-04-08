#pragma once
#ifndef _Geo2d_TopoChainAnalysisFwd_Header
#define _Geo2d_TopoChainAnalysisFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/2/2022 Amir]
	template<class ChainTraits>
	class Geo_TopoChainAnalysis;

	struct Geo2d_TopoChainAnalysisTraits;

	typedef Geo_TopoChainAnalysis<Geo2d_TopoChainAnalysisTraits>
		Geo2d_TopoChainAnalysis;
}

#endif // !_Geo2d_TopoChainAnalysisFwd_Header
