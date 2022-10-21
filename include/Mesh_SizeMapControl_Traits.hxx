#pragma once
#ifndef _Mesh_SizeMapControl_Traits_Header
#define _Mesh_SizeMapControl_Traits_Header

#include <GeoMesh3d_BackgroundFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	class Cad2d_Plane;
	class Cad_GModel;
	class Cad_TModel;

	class Geo3d_PatchCloud;
	class Geo2d_PatchCloud;

	class Mesh2d_SizeMapTool;
	class Mesh3d_SizeMapTool;

	template<class Geometry> struct size_map_type{};

	template<> 
	struct size_map_type<Cad2d_Plane> 
	{ 
		typedef Mesh2d_SizeMapTool type; 
		typedef Entity2d_Box boxType;
		typedef Geo2d_PatchCloud cloudType;
		typedef GeoMesh2d_Background backMeshType;	
	};
	template<> 
	struct size_map_type<Cad_GModel> 
	{ 
		typedef Mesh3d_SizeMapTool type; 
		typedef Entity3d_Box boxType;
		typedef Geo3d_PatchCloud cloudType;
		typedef GeoMesh3d_Background backMeshType;	
	};
	template<> 
	struct size_map_type<Cad_TModel> 
	{ 
		typedef Mesh3d_SizeMapTool type;
		typedef Entity3d_Box boxType;
		typedef Geo3d_PatchCloud cloudType;
		typedef GeoMesh3d_Background backMeshType;	
	};
}

#endif // !_Mesh_SizeMapControl_Traits_Header
