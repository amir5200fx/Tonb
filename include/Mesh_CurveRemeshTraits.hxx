#pragma once
#ifndef _Mesh_CurveRemeshTraits_Header
#define _Mesh_CurveRemeshTraits_Header

#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Geo2d_SizeFunctionFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Curve;
	class Pnt2d;

	template<class CurveType>
	struct Mesh_CurveRemeshTraits {};

	template<> 
	struct Mesh_CurveRemeshTraits<Pln_Curve> 
	{
		typedef GeoMesh2d_Background BackMesh;
		typedef Pnt2d Point;
		typedef Geo2d_SizeFunction SizeMap;
	};
}

#endif // !_Mesh_CurveRemeshTraits_Header
