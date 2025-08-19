#pragma once
#ifndef _Geo3d_NormalSizeFunFwd_Header
#define _Geo3d_NormalSizeFunFwd_Header

#include <Geo3d_SizeFunFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [6/5/2022 Amir]

	template<class Point>
	class Geo_NormalSizeFun;

	class Pnt3d;

	typedef Geo_NormalSizeFun<Pnt3d> Geo3d_NormalSizeFun;
}

#endif // !_Geo3d_NormalSizeFunFwd_Header
