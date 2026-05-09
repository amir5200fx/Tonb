#pragma once
#ifndef _Mesh2d_SizeMapControl_Header
#define _Mesh2d_SizeMapControl_Header

#include <Mesh_SizeMapControl.hxx>
#include <Mesh2d_SizeMapControlFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void Mesh2d_SizeMapControl::Perform();
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Mesh2d_SizeMapControl);

namespace tnbLib
{
	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_SizeMapControl::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_SizeMapControl::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_version*/
			);
}

#endif // !_Mesh2d_SizeMapControl_Header
