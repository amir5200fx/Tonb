#pragma once
#ifndef _Mesh_SizeMapTool_Traits_Header
#define _Mesh_SizeMapTool_Traits_Header

#include <GeoMesh2d_BackgroundFwd.hxx>
#include <Entity2d_BoxFwd.hxx>

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
}

#endif // !_Mesh_SizeMapTool_Traits_Header
