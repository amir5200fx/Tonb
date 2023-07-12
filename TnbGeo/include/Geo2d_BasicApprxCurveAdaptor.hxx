#pragma once
#ifndef _Geo2d_BasicApprxCurveAdaptor_Header
#define _Geo2d_BasicApprxCurveAdaptor_Header

#include <Geo2d_BasicApprxCurveAdaptorFwd.hxx>
#include <Geo_BasicApprxCurveAdaptor.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT gp_Pnt2d Geo2d_BasicApprxCurveAdaptor::Value(const Standard_Real) const;
}

#endif // !_Geo2d_BasicApprxCurveAdaptor_Header
