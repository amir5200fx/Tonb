#pragma once
#ifndef _Entity2d_TriangleFwd_Header
#define _Entity2d_TriangleFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;

	template<class Point>
	class Entity_Triangle;

	typedef Entity_Triangle<Pnt2d> Entity2d_Triangle;
}

#endif // !_Entity2d_TriangleFwd_Header
