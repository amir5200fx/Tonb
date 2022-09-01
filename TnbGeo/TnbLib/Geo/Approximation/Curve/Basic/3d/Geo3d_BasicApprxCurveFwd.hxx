#pragma once
#ifndef _Geo3d_BasicApprxCurveFwd_Header
#define _Geo3d_BasicApprxCurveFwd_Header

#include <Geo3d_BasicApprxCurveAdaptorFwd.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [8/25/2022 Amir]

	template<class CurveType, bool RandSamples>
	class Geo_ApprxCurve;

	typedef Geo_ApprxCurve<std::shared_ptr<Geo3d_BasicApprxCurveAdaptor>, false>
		Geo3d_BasicApprxCurve;
}

#endif // !_Geo3d_BasicApprxCurveFwd_Header
