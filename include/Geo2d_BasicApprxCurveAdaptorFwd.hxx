#pragma once
#ifndef _Geo2d_BasicApprxCurveAdaptorFwd_Header
#define _Geo2d_BasicApprxCurveAdaptorFwd_Header

#include <Standard_Handle.hxx>

// Forward Declarations [8/25/2022 Amir]
class Geom2d_Curve;

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]

	template<class CurveType>
	class Geo_BasicApprxCurveAdaptor;

	typedef Geo_BasicApprxCurveAdaptor<Handle(Geom2d_Curve)> 
		Geo2d_BasicApprxCurveAdaptor;
}

#endif // !_Geo2d_BasicApprxCurveAdaptorFwd_Header
