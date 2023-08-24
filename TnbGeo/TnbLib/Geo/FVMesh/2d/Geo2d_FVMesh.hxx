#pragma once
#ifndef _Geo2d_FVMesh_Header
#define _Geo2d_FVMesh_Header

#include <Geo2d_FVMeshFwd.hxx>
#include <Geo_FVMesh.hxx>
#include <Geo_Module.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbGeo_EXPORT void Geo2d_FVMesh::Boundary::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo2d_FVMesh::Boundary::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo2d_FVMesh::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
		);

	template<>
	template<>
	TnbGeo_EXPORT void Geo2d_FVMesh::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
		);
}

#endif // !_Geo2d_FVMesh_Header
