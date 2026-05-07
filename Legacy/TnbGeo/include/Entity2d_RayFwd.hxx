#pragma once
#ifndef _Entity2d_RayFwd_Header
#define _Entity2d_RayFwd_Header

namespace tnbLib
{

	// Forward Declarations [4/30/2023 Payvand]
	template<class Point, class Dir>
	class Entity_Ray;

	class Pnt2d;
	class Dir2d;

	typedef Entity_Ray<Pnt2d, Dir2d> Entity2d_Ray;
}

#endif // !_Entity2d_RayFwd_Header
