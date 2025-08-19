#pragma once
#ifndef _GeoMetricFun2d_UniformFwd_Header
#define _GeoMetricFun2d_UniformFwd_Header

namespace tnbLib
{

	// Forward Declarations [12/23/2021 Amir]
	class Pnt2d;

	template<class Point>
	class GeoMetricFun_Uniform;

	typedef GeoMetricFun_Uniform<Pnt2d>
		GeoMetricFun2d_Uniform;
}

#endif // !_GeoMetricFun2d_UniformFwd_Header
