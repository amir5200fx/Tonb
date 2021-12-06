#pragma once
#ifndef _Aft2d_BoundaryOfPlane_InfoFwd_Header
#define _Aft2d_BoundaryOfPlane_InfoFwd_Header

namespace tnbLib
{

	// Forward Declarations

	class Aft_MetricPrcsr_Info;
	
	template<class MetricPrcsrInfo> class Aft_BoundaryOfPlane_Info;

	typedef Aft_BoundaryOfPlane_Info<Aft_MetricPrcsr_Info> Aft2d_BoundaryOfPlane_Info;
}

#endif // !_Aft2d_BoundaryOfPlane_InfoFwd_Header
