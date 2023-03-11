#pragma once
#ifndef _Aft3d_Comparison_Header
#define _Aft3d_Comparison_Header

#include <Mesh_Module.hxx>

#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/27/2023 Payvand]
		class Aft3d_Element;
		class Aft3d_Facet;
		class Aft3d_Edge;

		TnbLegMesh_EXPORT Standard_Integer Index(const std::shared_ptr<Aft3d_Edge>&);
		TnbLegMesh_EXPORT Standard_Integer Index(const std::shared_ptr<Aft3d_Facet>&);
		TnbLegMesh_EXPORT Standard_Integer Index(const std::shared_ptr<Aft3d_Element>&);

		auto cmp_edge = []
		(
			const std::shared_ptr<Aft3d_Edge>& theEdge0,
			const std::shared_ptr<Aft3d_Edge>& theEdge1
			)
		{
			return Index(theEdge0) < Index(theEdge1);
		};

		auto cmp_facet = []
		(
			const std::shared_ptr<Aft3d_Facet>& theFacet0, 
			const std::shared_ptr<Aft3d_Facet>& theFacet1
			)
		{
			return Index(theFacet0) < Index(theFacet1);
		};

		auto cmp_element = []
		(
			const std::shared_ptr<Aft3d_Element>& theElement0,
			const std::shared_ptr<Aft3d_Element>& theElement1
			)
		{
			return Index(theElement0) < Index(theElement1);
		};
	}
}

#endif // !_Aft3d_Comparison_Header
