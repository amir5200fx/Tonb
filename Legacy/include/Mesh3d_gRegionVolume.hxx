#pragma once
#ifndef _Mesh3d_gRegionVolume_Header
#define _Mesh3d_gRegionVolume_Header

#include <Mesh3d_gRegionVolumeFwd.hxx>
#include <Mesh_RegionVolume.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_gRegionVolume::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_gRegionVolume::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

#endif // !_Mesh3d_gRegionVolume_Header
