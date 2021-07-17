#pragma once
#ifndef _Geo_Traits_Header
#define _Geo_Traits_Header

#include <Traits.hxx>
#include <Entity_Connectivity.hxx>

class gp_Vec;
class gp_Vec2d;
class gp_Trsf2d;
class gp_Trsf;
class Geom2d_Curve;
class Geom_Curve;

namespace tnbLib
{

	class Pnt2d;
	class Pnt3d;

	template<class Point> struct transform_point_type {};
	template<> struct transform_point_type<Pnt2d> { typedef gp_Trsf2d type; };
	template<> struct transform_point_type<Pnt3d> { typedef gp_Trsf type; };
	template<> struct transform_point_type<std::pair<Pnt2d, Standard_Real>> { typedef gp_Trsf2d type; };
	template<> struct transform_point_type<std::pair<Pnt3d, Standard_Real>> { typedef gp_Trsf type; };

	template<class Point> struct entity_connectivity_type {};
	template<> struct entity_connectivity_type<Pnt2d> { typedef typename connectivity::triple type; };
	template<> struct entity_connectivity_type<Pnt3d> { typedef typename connectivity::quadruple type; };

	template<class T> struct entity_coord {};
	template<> struct entity_coord<Pnt2d> { typedef Pnt2d coord; };
	template<> struct entity_coord<Pnt3d> { typedef Pnt3d coord; };
	template<> struct entity_coord<std::pair<Pnt2d, Standard_Real>> { typedef Pnt2d coord; };
	template<> struct entity_coord<std::pair<Pnt3d, Standard_Real>> { typedef Pnt3d coord; };

	namespace cascadeLib
	{

		template<class T> struct pt_type_from_curve {};

		template<> struct pt_type_from_curve<Geom2d_Curve> { typedef Pnt2d ptType; };
		template<> struct pt_type_from_curve<Geom_Curve> { typedef Pnt3d ptType; };

		template<class T> struct vec_type_from_point {};

		template<> struct vec_type_from_point<Pnt2d> { typedef gp_Vec2d vcType; };
		template<> struct vec_type_from_point<Pnt3d> { typedef gp_Vec vcType; };
	}
}

#endif // !_Geo_Traits_Header