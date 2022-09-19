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
	TnbMesh_EXPORT Standard_Boolean 
		Mesh3d_Facet::IsRightSide(const Pnt3d& theCoord) const;

	template<>
	TnbMesh_EXPORT Standard_Boolean  
		Mesh3d_Facet::IsLeftSide(const Pnt3d& theCoord) const;

	template<>
	TnbMesh_EXPORT std::tuple<Pnt3d, Pnt3d, Pnt3d> 
		Mesh3d_Facet::RetrieveCoords() const;


	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Facet::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void Mesh3d_Facet::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar, 
			const unsigned int /*file_version*/
			);
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Mesh3d_Facet);

#endif // !_Mesh3d_Facet_Header