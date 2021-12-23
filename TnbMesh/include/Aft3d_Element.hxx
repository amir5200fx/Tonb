#pragma once
#ifndef _Aft3d_Element_Header
#define _Aft3d_Element_Header

#include <Aft3d_Node.hxx>
#include <Aft_Element.hxx>
#include <Aft3d_ElementTraits.hxx>
#include <Aft3d_ElementFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::array4
		Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::InterpWeights(const Pnt3d& theCoord) const;

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_vertion
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Element<Aft3d_ElementTraits, Mesh_ElementType_Tetrahedron>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_vertion
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft3d_Element);

#endif // !_Aft3d_Element_Header