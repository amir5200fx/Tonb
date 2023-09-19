#pragma once
#ifndef _Geo3d_FVMesh_Header
#define _Geo3d_FVMesh_Header

#include <Geo3d_FVMeshFwd.hxx>
#include <Geo_FVMesh.hxx>
#include <Geo_Module.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbGeo_EXPORT void Geo3d_FVMesh::Boundary::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo3d_FVMesh::Boundary::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo3d_FVMesh::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo3d_FVMesh::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
		);

	template <>
	TnbGeo_EXPORT void Geo3d_FVMesh::ExportToPlt(OFstream&) const;
}

#endif // !_Geo3d_FVMesh_Header
