#pragma once
#ifndef _Aft2d_gRegionPlaneSurface_Header
#define _Aft2d_gRegionPlaneSurface_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_gRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gRegionPlaneSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gRegionPlaneSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);

	// Forward Declarations [3/26/2022 Amir]
	class GModel_ParaWire;
	class GModel_Plane;

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_gPlnWireSurface>
		Aft2d_gRegionPlaneSurface::MakeMeshWire<GModel_ParaWire>(const GModel_ParaWire&);

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<GModel_Plane> 
		Aft2d_gRegionPlaneSurface::MakeOrignPlane
		(
			const std::shared_ptr<Aft2d_gRegionPlaneSurface>&
		);
}

#endif // !_Aft2d_gRegionPlaneSurface_Header
