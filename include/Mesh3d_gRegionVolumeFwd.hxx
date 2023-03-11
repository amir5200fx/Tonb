#pragma once
#ifndef _Mesh3d_gRegionVolumeFwd_Header
#define _Mesh3d_gRegionVolumeFwd_Header

namespace tnbLib
{

	// Forward Declarations [3/9/2023 Payvand]
	template<class SurfType>
	class Mesh_RegionVolume;

	class GModel_Surface;

	typedef Mesh_RegionVolume<GModel_Surface> Mesh3d_gRegionVolume;

}

#endif // !_Mesh3d_gRegionVolumeFwd_Header
