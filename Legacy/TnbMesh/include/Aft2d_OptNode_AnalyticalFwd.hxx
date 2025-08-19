#pragma once
#ifndef _Aft2d_OptNode_AnalyticalFwd_Header
#define _Aft2d_OptNode_AnalyticalFwd_Header

#include <Aft2d_EdgeFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [3/5/2022 Amir]
	template<class FrontType, class MetricType>
	class Aft_OptNode_Analytical;

	typedef Aft_OptNode_Analytical<Aft2d_Edge, void>
		Aft2d_OptNode_Analytical;
}

#endif // !_Aft2d_OptNode_AnalyticalFwd_Header
