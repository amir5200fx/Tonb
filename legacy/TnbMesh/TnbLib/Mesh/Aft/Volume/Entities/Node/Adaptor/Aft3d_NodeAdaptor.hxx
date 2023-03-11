#pragma once
#ifndef _Aft3d_NodeAdaptor_Header
#define _Aft3d_NodeAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <map>
#include <memory>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/23/2023 Payvand]
		class Aft3d_Edge;
		class Aft3d_Facet;
		class Aft3d_Element;

		class Aft3d_NodeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<Aft3d_Edge>> theEdges_;
			std::map<Standard_Integer, std::weak_ptr<Aft3d_Facet>> theFacets_;
			std::map<Standard_Integer, std::weak_ptr<Aft3d_Element>> theElements_;

			std::map<Standard_Integer, std::weak_ptr<Aft3d_Edge>> theFrontEdges_;
			std::map<Standard_Integer, std::weak_ptr<Aft3d_Facet>> theFrontFacets_;


			// Private functions and operators [2/23/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/23/2023 Payvand]

			Aft3d_NodeAdaptor()
			{}

			// constructors [2/23/2023 Payvand]

		public:


			// Public functions and operators [2/23/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Integer NbEdges() const;
			TnbLegMesh_EXPORT Standard_Integer NbFacets() const;
			TnbLegMesh_EXPORT Standard_Integer NbElements() const;

			TnbLegMesh_EXPORT Standard_Integer NbFrontEdges() const;
			TnbLegMesh_EXPORT Standard_Integer NbFrontFacets() const;

			TnbLegMesh_EXPORT Standard_Boolean IsContainsElement(const std::shared_ptr<Aft3d_Element>&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsContainsFacet(const std::shared_ptr<Aft3d_Facet>&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsContainsEdge(const std::shared_ptr<Aft3d_Facet>&) const;

			TnbLegMesh_EXPORT Standard_Boolean IsContainsFrontFacet(const std::shared_ptr<Aft3d_Facet>&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsContainsFrontEdge(const std::shared_ptr<Aft3d_Edge>&) const;

			const auto& Edges() const { return theEdges_; }
			const auto& Facets() const { return theFacets_; }
			const auto& Elements() const { return theElements_; }

			const auto& FrontEdges() const { return theFrontEdges_; }
			const auto& FrontFacets() const { return theFrontFacets_; }

			TnbLegMesh_EXPORT void RemoveEdge(const std::shared_ptr<Aft3d_Edge>&);
			TnbLegMesh_EXPORT void RemoveFacet(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void RemoveElement(const std::shared_ptr<Aft3d_Element>&);

			TnbLegMesh_EXPORT void RemoveFrontEdge(const std::shared_ptr<Aft3d_Edge>&);
			TnbLegMesh_EXPORT void RemoveFrontFacet(const std::shared_ptr<Aft3d_Facet>&);

			TnbLegMesh_EXPORT void InsertEdge(const std::shared_ptr<Aft3d_Edge>&);
			TnbLegMesh_EXPORT void InsertFacet(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void InsertElement(const std::shared_ptr<Aft3d_Element>&);

			TnbLegMesh_EXPORT void InsertFrontEdge(const std::shared_ptr<Aft3d_Edge>&);
			TnbLegMesh_EXPORT void InsertFrontFacet(const std::shared_ptr<Aft3d_Facet>&);
		};

	}
}

#endif // !_Aft3d_NodeAdaptor_Header
