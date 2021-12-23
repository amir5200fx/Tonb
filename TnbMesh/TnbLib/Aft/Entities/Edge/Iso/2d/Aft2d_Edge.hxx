#pragma once
#ifndef _Aft2d_Edge_Header
#define _Aft2d_Edge_Header

#include <Mesh_Module.hxx>
#include <Aft_Edge.hxx>
#include <Aft2d_EdgeTraits.hxx>
#include <Aft2d_EdgeFwd.hxx>

namespace tnbLib
{
	
	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Edge<Aft2d_EdgeTraits>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int file_version
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Edge<Aft2d_EdgeTraits>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int file_version
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_Edge);

#endif // !_Aft2d_Edge_Header