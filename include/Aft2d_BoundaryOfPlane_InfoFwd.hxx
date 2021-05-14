#pragma once
#ifndef _Aft2d_BoundaryOfPlane_InfoFwd_Header
#define _Aft2d_BoundaryOfPlane_InfoFwd_Header

namespace tnbLib
{

	// Forward Declarations

	class NumAlg_AdaptiveInteg_Info;
	
	template<class MetricPrcsrInfo> class Aft_BoundaryOfPlane_Info;

	typedef Aft_BoundaryOfPlane_Info<NumAlg_AdaptiveInteg_Info> Aft2d_BoundaryOfPlane_Info;
}

#endif // !_Aft2d_BoundaryOfPlane_InfoFwd_Header
