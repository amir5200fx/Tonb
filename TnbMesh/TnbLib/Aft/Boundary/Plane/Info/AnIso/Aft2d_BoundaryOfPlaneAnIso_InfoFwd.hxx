#pragma once
#ifndef _Aft2d_BoundaryOfPlaneAnIso_InfoFwd_Header
#define _Aft2d_BoundaryOfPlaneAnIso_InfoFwd_Header

namespace tnbLib
{

	// Forward Declarations
	template<class MetricPrcsrInfo> class Aft_BoundaryOfPlane_Info;

	class Aft_MetricPrcsrAnIso_Info;

	typedef Aft_BoundaryOfPlane_Info<Aft_MetricPrcsrAnIso_Info> Aft2d_BoundaryOfPlaneAnIso_Info;
}

#endif // !_Aft2d_BoundaryOfPlaneAnIso_InfoFwd_Header
