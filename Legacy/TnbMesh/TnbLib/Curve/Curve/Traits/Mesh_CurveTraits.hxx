#pragma once
#ifndef _Mesh_CurveTraits_Header
#define _Mesh_CurveTraits_Header

#include <Global_TypeDef.hxx>

#include <memory>

// Forward Declarations
class Geom2d_Curve;
class Geom_Curve;

namespace tnbLib
{

	// Forward Declarations
	class Pnt2d;
	class Pnt3d;

	namespace meshCurveTraits
	{

		template<class gCurveType, bool SavePars = false>
		struct point_type{};

		template<> struct point_type<Geom2d_Curve, false> { typedef Pnt2d Point; };
		template<> struct point_type<Geom2d_Curve, true> { typedef std::pair<Pnt2d, Standard_Real> Point; };

		template<> struct point_type<Geom_Curve, false> { typedef Pnt3d Point; };
		template<> struct point_type<Geom_Curve, true> { typedef std::pair<Pnt3d, Standard_Real> Point; };
	}
}

#endif // !_Mesh_CurveTraits_Header
