#pragma once
#ifndef _Aft2d_RegionPlaneAnIso_Header
#define _Aft2d_RegionPlaneAnIso_Header

#include <Mesh_Module.hxx>
#include <Mesh_RegionPlane.hxx>
#include <Aft2d_RegionPlaneAnIsoFwd.hxx>

namespace tnbLib
{
	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_RegionPlaneAnIso::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Aft2d_RegionPlaneAnIso::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);


	// Forward Declarations [1/24/2023 Payvand]

	class Pln_Wire;

	template<>
	template<>
	TnbMesh_EXPORT std::shared_ptr<Aft2d_PlnWireAnIso>
		Aft2d_RegionPlaneAnIso::MakeMeshWire<Pln_Wire>
		(
			const Pln_Wire&
			);
}

#endif // !_Aft2d_RegionPlaneAnIso_Header
