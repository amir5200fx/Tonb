#pragma once
#ifndef _Aft2d_CoreBaseSurface_Header
#define _Aft2d_CoreBaseSurface_Header

#include <Mesh_Module.hxx>
#include <Aft_Core_Base.hxx>
#include <Aft2d_FrontSurfaceInfo.hxx>
#include <Aft2d_FrontSurfaceGlobalData.hxx>
#include <Aft2d_GlobalDataSurface.hxx>
#include <Geo2d_SizeFunction.hxx>
#include <Geo2d_MetricFunction.hxx>
#include <Aft2d_CoreBaseSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Aft2d_CoreBaseSurface::AddOptimumNodeTo
	(
		std::vector<std::shared_ptr<Aft2d_NodeSurface>>&
	);

	template<>
	TnbMesh_EXPORT Standard_Boolean 
		Aft2d_CoreBaseSurface::IsNewPointCandidate
		(
			const std::vector<std::shared_ptr<Aft2d_EdgeSurface>>&
		) const;

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBaseSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_CoreBaseSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

#endif // !_Aft2d_CoreBaseSurface_Header
