#pragma once
#ifndef _Entity3d_TetrahedronFwd_Header
#define _Entity3d_TetrahedronFwd_Header

namespace tnbLib
{

	// Forward Declarations [10/28/2022 Amir]
	class Pnt3d;

	template<class Point>
	class Entity_Tetrahedron;

	typedef Entity_Tetrahedron<Pnt3d> Entity3d_Tetrahedron;
}

#endif // !_Entity3d_TetrahedronFwd_Header
