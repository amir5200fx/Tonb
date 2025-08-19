#pragma once
#ifndef _VoyageMesh_OptNode_AnalyticalFwd_Header
#define _VoyageMesh_OptNode_AnalyticalFwd_Header

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
	template<class FrontType, class MetricType>
	class Aft_OptNode_Analytical;

	class VoyageMesh_Edge;
	class Entity2d_Metric1;
	
	typedef Aft_OptNode_Analytical<VoyageMesh_Edge, Entity2d_Metric1>
		VoyageMesh_OptNode_Analytical;
}

#endif // !_VoyageMesh_OptNode_AnalyticalFwd_Header
