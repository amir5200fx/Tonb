#pragma once
#ifndef _Mesh3d_tRegionVolumeFwd_Header
#define _Mesh3d_tRegionVolumeFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/9/2023 Payvand]
	template<class SurfType>
	class Mesh_RegionVolume;

	class TModel_Surface;

	typedef Mesh_RegionVolume<TModel_Surface> Mesh3d_tRegionVolume;

}

#endif // !_Mesh3d_tRegionVolumeFwd_Header
