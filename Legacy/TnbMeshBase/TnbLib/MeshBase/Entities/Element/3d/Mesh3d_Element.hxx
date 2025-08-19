#pragma once
#ifndef _Mesh3d_Element_Header
#define _Mesh3d_Element_Header

#include <Mesh_Element.hxx>
#include <Mesh3d_ElementTraits.hxx>

namespace tnbLib
{

	typedef Mesh_Element<Mesh3d_ElementTraits, Mesh_ElementType_Tetrahedron> Mesh3d_Element;

	template<>
	template<>
	TnbMeshBase_EXPORT void Mesh3d_Element::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMeshBase_EXPORT void Mesh3d_Element::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Element);

#endif // !_Mesh3d_Element_Header