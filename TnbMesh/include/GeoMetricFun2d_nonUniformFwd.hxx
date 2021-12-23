#pragma once
#ifndef _GeoMetricFun2d_nonUniformFwd_Header
#define _GeoMetricFun2d_nonUniformFwd_Header


namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	template<class Point>
	class GeoMetricFun_nonUniform;

	typedef GeoMetricFun_nonUniform<Pnt2d> GeoMetricFun2d_nonUniform;
}

#endif // !_GeoMetricFun2d_nonUniformFwd_Header
