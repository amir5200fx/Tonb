#pragma once
#ifndef _Geo3d_BasicApprxCurveAdaptorFwd_Header
#define _Geo3d_BasicApprxCurveAdaptorFwd_Header

#include <Standard_Handle.hxx>

// Forward Declarations [8/25/2022 Amir]
class Geom_Curve;

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]

	template<class CurveType>
	class Geo_BasicApprxCurveAdaptor;

	typedef Geo_BasicApprxCurveAdaptor<Handle(Geom_Curve)>
		Geo3d_BasicApprxCurveAdaptor;
}

#endif // !_Geo3d_BasicApprxCurveAdaptorFwd_Header
