#pragma once
#ifndef _Aft2d_gPlnWireSurface_Header
#define _Aft2d_gPlnWireSurface_Header

#include <Mesh_Module.hxx>
#include <Mesh_PlnWire.hxx>
#include <Aft2d_gPlnWireSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnWireSurface::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_gPlnWireSurface::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);

	// Forward Declarations [4/19/2022 Amir]
	class GModel_ParaWire;

	template<>
	template<>
	static TnbMesh_EXPORT std::shared_ptr<GModel_ParaWire>
		Aft2d_gPlnWireSurface::MakeOrignWire<GModel_ParaWire>
		(
			const std::shared_ptr<Aft2d_gPlnWireSurface>&
			);

	template<>
	TnbMesh_EXPORT Entity2d_Box 
		Aft2d_gPlnWireSurface::CalcBoundingBox
		(
			const Aft2d_gPlnCurveSurface&
		);
}

#endif // !_Aft2d_gPlnWireSurface_Header
