#pragma once
#ifndef _Mesh3d_Facet_Header
#define _Mesh3d_Facet_Header

#include <Mesh_Facet.hxx>
#include <Mesh3d_FacetTraits.hxx>
#include <Mesh3d_Node.hxx>

namespace tnbLib
{

	typedef Mesh_Facet<Mesh3d_FacetTraits> Mesh3d_Facet;

	template<>
	TnbMesh_EXPORT Standard_Boolean Mesh3d_Facet::IsRightSide(const Pnt3d& theCoord) const;

	template<>
	TnbMesh_EXPORT Standard_Boolean  Mesh3d_Facet::IsLeftSide(const Pnt3d& theCoord) const;
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Facet);

#endif // !_Mesh3d_Facet_Header