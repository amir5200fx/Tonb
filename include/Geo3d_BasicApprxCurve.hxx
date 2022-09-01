#pragma once
#ifndef _Geo3d_BasicApprxCurve_Header
#define _Geo3d_BasicApprxCurve_Header

#include <Geo3d_BasicApprxCurveFwd.hxx>
#include <Geo_ApprxCurve.hxx>
#include <Geo_BasicApprxCurve_Info.hxx>
#include <Geo_BasicApprxCurve_Traits.hxx>

namespace tnbLib
{

	template<>
	TnbGeo_EXPORT void Geo3d_BasicApprxCurve::Subdivide(segList&) const;
}

#endif // !_Geo3d_BasicApprxCurve_Header
