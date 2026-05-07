#pragma once
#ifndef _Mesh_RegionTraits_Header
#define _Mesh_RegionTraits_Header

#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/18/2022 Amir]
	class Cad2d_Plane;
	class Cad_TModel;

	template<class GeomType>
	struct mesh_region_box_type {};

	template<> struct mesh_region_box_type<Cad2d_Plane> { typedef Entity2d_Box type; };
	template<> struct mesh_region_box_type<Cad_TModel> { typedef Entity3d_Box type; };
}

#endif // !_Mesh_RegionTraits_Header
