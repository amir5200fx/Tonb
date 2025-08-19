#pragma once
#ifndef _Geo2d_MetricPrcsrUniSizeFwd_Header
#define _Geo2d_MetricPrcsrUniSizeFwd_Header

#include <GeoSizeFun2d_UniformFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class SizeFun, class MetricFun>
	class Geo_MetricPrcsr;

	typedef Geo_MetricPrcsr<GeoSizeFun2d_Uniform, void>
		Geo2d_MetricPrcsrUniSize;
}

#endif // !_Geo2d_MetricPrcsrUniSizeFwd_Header
