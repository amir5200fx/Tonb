#pragma once
#ifndef _Mesh_SizeMapTool_Traits_Header
#define _Mesh_SizeMapTool_Traits_Header

#include <GeoMesh3d_BackgroundFwd.hxx>
#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Entity2d_BoxFwd.hxx>
#include <Entity3d_BoxFwd.hxx>

namespace tnbLib
{

	template<class BackGroundMesh>
	struct mesh_sizeMapTool_traits
	{};

	template<>
	struct mesh_sizeMapTool_traits<GeoMesh2d_Background>
	{
		typedef Entity2d_Box boxType;
	};

	template<>
	struct mesh_sizeMapTool_traits<GeoMesh3d_Background>
	{
		typedef Entity3d_Box boxType;
	};
}

#endif // !_Mesh_SizeMapTool_Traits_Header
