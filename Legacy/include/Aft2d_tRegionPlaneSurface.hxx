#pragma once
#ifndef _Aft2d_tRegionPlaneSurface_Header
#define _Aft2d_tRegionPlaneSurface_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_tRegionPlaneSurfaceFwd.hxx>
#include <Aft2d_tPlnWireSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tRegionPlaneSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_tRegionPlaneSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);

	// Forward Declarations [6/22/2022 Amir]
	class TModel_ParaWire;
	class TModel_Plane;

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<Aft2d_tPlnWireSurface>
		Aft2d_tRegionPlaneSurface::MakeMeshWire<TModel_ParaWire>(const TModel_ParaWire&);

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<TModel_Plane>
		Aft2d_tRegionPlaneSurface::MakeOrignPlane
		(
			const std::shared_ptr<Aft2d_tRegionPlaneSurface>&
		);
}

#endif // !_Aft2d_tRegionPlaneSurface_Header
