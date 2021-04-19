#pragma once
#ifndef _GeoMesh2d_Data_Header
#define _GeoMesh2d_Data_Header

#include <GeoMesh_Data.hxx>
#include <Entity2d_Triangulation.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{
	typedef GeoMesh_Data<Mesh2d_Element>
		GeoMesh2d_Data;

	template<>
	TnbMesh_EXPORT void GeoMesh2d_Data::Construct(const triangulation& theTriangulation);


	template<>
	template<>
	TnbMesh_EXPORT void GeoMesh2d_Data::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void GeoMesh2d_Data::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);
}

#endif // !_GeoMesh2d_Data_Header