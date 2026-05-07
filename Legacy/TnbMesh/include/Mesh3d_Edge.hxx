#pragma once
#ifndef _Mesh3d_Edge_Header
#define _Mesh3d_Edge_Header

#include <Mesh_Edge.hxx>
#include <Mesh3d_EdgeTraits.hxx>

namespace tnbLib
{

	typedef Mesh_Edge<Mesh3d_EdgeTraits> Mesh3d_Edge;


	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Edge::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Edge::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Edge);

#endif // !_Mesh3d_Edge_Header