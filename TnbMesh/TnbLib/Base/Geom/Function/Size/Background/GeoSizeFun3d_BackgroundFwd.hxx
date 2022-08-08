#pragma once
#ifndef _GeoSizeFun3d_BackgroundFwd_Header
#define _GeoSizeFun3d_BackgroundFwd_Header

#include <GeoMesh3d_BackgroundFwd.hxx>

namespace tnbLib
{

	// Forward Declarations [7/20/2022 Amir]
	
	template<class BackMeshData>
	class GeoSizeFun_Background;

	typedef GeoSizeFun_Background<GeoMesh3d_Background> GeoSizeFun3d_Background;
}

#endif // !_GeoSizeFun3d_BackgroundFwd_Header
