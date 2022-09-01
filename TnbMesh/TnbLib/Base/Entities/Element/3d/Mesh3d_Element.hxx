#pragma once
#ifndef _Mesh3d_Element_Header
#define _Mesh3d_Element_Header

#include <Mesh3d_Node.hxx>
#include <Mesh_Element.hxx>
#include <Mesh3d_ElementTraits.hxx>

namespace tnbLib
{

	typedef Mesh_Element<Mesh3d_ElementTraits, Mesh_ElementType_Tetrahedron> Mesh3d_Element;

	template<>
	TnbMesh_EXPORT Mesh3d_Element::array4 
		Mesh3d_Element::InterpWeights(const Pnt3d& theCoord) const;

	template<>
	TnbMesh_EXPORT std::tuple<Pnt3d, Pnt3d, Pnt3d, Pnt3d> 
		Mesh3d_Element::RetrieveCoords() const;

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Element::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Element::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Element);

#endif // !_Mesh3d_Element_Header