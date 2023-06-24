#pragma once
#ifndef _GeoSizeFun2d_BackgroundFwd_Header
#define _GeoSizeFun2d_BackgroundFwd_Header

#include <GeoMesh2d_BackgroundFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/20/2022 Amir]

	template<class BackMeshData>
	class GeoSizeFun_Background;

	typedef GeoSizeFun_Background<GeoMesh2d_Background> GeoSizeFun2d_Background;
}

#endif // !_GeoSizeFun2d_BackgroundFwd_Header
