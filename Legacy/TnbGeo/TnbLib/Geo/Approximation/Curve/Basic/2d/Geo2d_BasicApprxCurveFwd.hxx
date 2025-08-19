#pragma once
#ifndef _Geo2d_BasicApprxCurveFwd_Header
#define _Geo2d_BasicApprxCurveFwd_Header

#include <Geo2d_BasicApprxCurveAdaptorFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]

	template<class CurveType, bool RandSamples>
	class Geo_ApprxCurve;

	typedef Geo_ApprxCurve<std::shared_ptr<Geo2d_BasicApprxCurveAdaptor>, false>
		Geo2d_BasicApprxCurve;
}

#endif // !_Geo2d_BasicApprxCurveFwd_Header
