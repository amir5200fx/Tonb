#pragma once
#ifndef _Aft3d_EdgeAnIso_Header
#define _Aft3d_EdgeAnIso_Header

#include <Mesh_Module.hxx>
#include <Aft_Edge.hxx>
#include <Aft3d_EdgeAnIsoTraits.hxx>
#include <Aft3d_EdgeAnIsoFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Edge<Aft3d_EdgeAnIsoTraits>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Edge<Aft3d_EdgeAnIsoTraits>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft3d_EdgeAnIso);

#endif // !_Aft3d_EdgeAnIso_Header