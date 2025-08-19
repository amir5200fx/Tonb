#pragma once
#ifndef _Geo2d_NormalSizeFunFwd_Header
#define _Geo2d_NormalSizeFunFwd_Header

#include <Geo2d_SizeFunFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/5/2022 Amir]

	template<class Point>
	class Geo_NormalSizeFun;

	class Pnt2d;

	typedef Geo_NormalSizeFun<Pnt2d> Geo2d_NormalSizeFun;
}

#endif // !_Geo2d_NormalSizeFunFwd_Header
