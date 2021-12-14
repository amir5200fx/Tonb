#pragma once
#ifndef _Mesh_SizeMapControl_Traits_Header
#define _Mesh_SizeMapControl_Traits_Header

#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Cad3d_GModel;
	class Cad3d_TModel;

	class Mesh2d_SizeMapTool;
	class Mesh3d_SizeMapTool;

	template<class Geometry> struct size_map_type{};

	template<> 
	struct size_map_type<Cad2d_Plane> 
	{ 
		typedef Mesh2d_SizeMapTool type; 
		typedef Entity2d_Box boxType;
	};
	template<> 
	struct size_map_type<Cad3d_GModel> 
	{ 
		typedef Mesh3d_SizeMapTool type; 
		typedef Entity3d_Box boxType;
	};
	template<> 
	struct size_map_type<Cad3d_TModel> 
	{ 
		typedef Mesh3d_SizeMapTool type;
		typedef Entity3d_Box boxType;
	};
}

#endif // !_Mesh_SizeMapControl_Traits_Header
