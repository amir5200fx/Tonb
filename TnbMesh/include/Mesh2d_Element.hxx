#pragma once
#ifndef _Mesh2d_Element_Header
#define _Mesh2d_Element_Header

#include <Mesh_Element.hxx>
#include <Mesh2d_ElementTraits.hxx>
#include <Mesh2d_Node.hxx>

namespace tnbLib
{

	typedef Mesh_Element<Mesh2d_ElementTraits, Mesh_ElementType_Triangle2D> Mesh2d_Element;

	template<>
	TnbMesh_EXPORT Mesh2d_Element::array3 Mesh2d_Element::InterpWeights(const Pnt2d& theCoord) const;

	template<>
	std::tuple<Pnt2d, Pnt2d, Pnt2d> Mesh2d_Element::RetrieveCoords() const;


	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_Element::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh2d_Element::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh2d_Element);

#endif // !_Mesh2d_Element_Header