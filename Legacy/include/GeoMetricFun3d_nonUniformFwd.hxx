#pragma once
#ifndef _GeoMetricFun3d_nonUniformFwd_Header
#define _GeoMetricFun3d_nonUniformFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	template<class Point>
	class GeoMetricFun_nonUniform;

	typedef GeoMetricFun_nonUniform<Pnt3d> GeoMetricFun3d_nonUniform;
}

#endif // !_GeoMetricFun3d_nonUniformFwd_Header
