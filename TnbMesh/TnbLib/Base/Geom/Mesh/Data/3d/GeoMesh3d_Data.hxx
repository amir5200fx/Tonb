#pragma once
#ifndef _GeoMesh3d_Data_Header
#define _GeoMesh3d_Data_Header

#include <GeoMesh_Data.hxx>
#include <GeoMesh3d_DataFwd.hxx>
#include <Entity3d_Tetrahedralization.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh_Module.hxx>

namespace tnbLib
{

	template<>
	TnbMesh_EXPORT void GeoMesh3d_Data::Construct(const triangulation& theTriangulation);

#ifdef _DEBUG
	template<>
	TnbMesh_EXPORT std::shared_ptr<Mesh3d_Element>
		GeoMesh3d_Data::TriangleLocation
		(
			const std::shared_ptr<Mesh3d_Element>& theElement,
			const Pnt3d& theCoord
		) const;
#endif // _DEBUG


	template<>
	template<>
	TnbMesh_EXPORT void GeoMesh3d_Data::serialize<TNB_iARCH_TYPE>
		(
			TNB_iARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	template<>
	TnbMesh_EXPORT void GeoMesh3d_Data::serialize<TNB_oARCH_TYPE>
		(
			TNB_oARCH_TYPE& ar,
			const unsigned int /*file_vertion*/
			);

	template<>
	TnbMesh_EXPORT void GeoMesh3d_Data::ExportToPlt(OFstream&) const;
}

#endif // !_GeoMesh3d_Data_Header