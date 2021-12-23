#pragma once
#ifndef _Aft2d_ElementSurface_Header
#define _Aft2d_ElementSurface_Header

#include <Aft2d_NodeSurface.hxx>
#include <Aft_Element.hxx>
#include <Aft2d_ElementSurfaceTraits.hxx>
#include <Aft2d_ElementSurfaceFwd.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::array3
		Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::InterpWeights(const Pnt2d& theCoord) const;

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int file_vertion
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh_Element<Aft2d_ElementSurfaceTraits, Mesh_ElementType_Triangle2D>::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int file_vertion
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_ElementSurface);

#endif // !_Aft2d_ElementSurface_Header