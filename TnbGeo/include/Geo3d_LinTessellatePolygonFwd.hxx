#pragma once
#ifndef _Geo3d_LinTessellatePolygonFwd_Header
#define _Geo3d_LinTessellatePolygonFwd_Header

namespace tnbLib
{

	// Forward Declarations [5/21/2022 Amir]

	class Pnt3d;

	template<class Point>
	class Geo_LinTessellatePolygon;

	typedef Geo_LinTessellatePolygon<Pnt3d> Geo2d_LinTessellatePolygon;
}

#endif // !_Geo3d_LinTessellatePolygonFwd_Header
