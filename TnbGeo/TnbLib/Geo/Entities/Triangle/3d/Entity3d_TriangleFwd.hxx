#pragma once
#ifndef _Entity3d_TriangleFwd_Header
#define _Entity3d_TriangleFwd_Header

namespace tnbLib
{

	// Forward Declarations
	class Pnt3d;

	template<class Point>
	class Entity_Triangle;

	typedef Entity_Triangle<Pnt3d> Entity3d_Triangle;
}

#endif // !_Entity3d_TriangleFwd_Header
