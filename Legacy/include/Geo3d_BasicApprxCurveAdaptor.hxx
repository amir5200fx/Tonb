#pragma once
#ifndef _Geo3d_BasicApprxCurveAdaptor_Header
#define _Geo3d_BasicApprxCurveAdaptor_Header

#include <Geo3d_BasicApprxCurveAdaptorFwd.hxx>
#include <Geo_BasicApprxCurveAdaptor.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT gp_Pnt Geo3d_BasicApprxCurveAdaptor::Value(const Standard_Real) const;
}

#endif // !_Geo3d_BasicApprxCurveAdaptor_Header
