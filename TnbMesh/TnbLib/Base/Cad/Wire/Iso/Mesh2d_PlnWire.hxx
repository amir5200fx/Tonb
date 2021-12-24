#pragma once
#ifndef _Mesh2d_PlnWire_Header
#define _Mesh2d_PlnWire_Header

#include <Mesh_Module.hxx>
#include <Mesh_PlnWire.hxx>
#include <Mesh2d_PlnWireFwd.hxx>

namespace tnbLib
{

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnWire::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_PlnWire::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

#endif // !_Mesh2d_PlnWire_Header