#pragma once
#ifndef _Aft2d_MetricPrcsrFwd_Header
#define _Aft2d_MetricPrcsrFwd_Header

#include <Aft2d_EdgeFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations

	template<class FrontType, class SizeFun, class MetricFun>
	class Aft_MetricPrcsr;

	typedef Aft_MetricPrcsr<Aft2d_Edge, Geo2d_SizeFunction, void>
		Aft2d_MetricPrcsr;
}

#endif // !_Aft2d_MetricPrcsrFwd_Header
