#pragma once
#ifndef _Mesh2d_Edge_Header
#define _Mesh2d_Edge_Header

#include <Mesh_Edge.hxx>
#include <Mesh2d_EdgeTraits.hxx>

namespace tnbLib
{

	typedef Mesh_Edge<Mesh2d_EdgeTraits> Mesh2d_Edge;

	template<>
	template<>
	TnbMesh_EXPORT Standard_Boolean Mesh2d_Edge::IsLeftSide<Standard_Boolean>
		(
			const Pnt2d& theCoord
			) const;

	template<>
	template<>
	TnbMesh_EXPORT Standard_Boolean Mesh2d_Edge::IsRightSide<Standard_Boolean>
		(
			const Pnt2d& theCoord
			) const;

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_Edge::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_Edge::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_Edge);

#endif // !_Mesh2d_Edge_Header