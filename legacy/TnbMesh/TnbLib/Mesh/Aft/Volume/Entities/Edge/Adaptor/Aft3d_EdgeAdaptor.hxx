#pragma once
#ifndef _Aft3d_EdgeAdaptor_Header
#define _Aft3d_EdgeAdaptor_Header

#include <Mesh_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>
#include <map>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/23/2023 Payvand]
		class Aft3d_Facet;
		class Aft3d_Element;

		class Aft3d_EdgeAdaptor
		{

			/*Private Data*/

			std::map<Standard_Integer, std::weak_ptr<Aft3d_Facet>> theFacets_;
			std::map<Standard_Integer, std::weak_ptr<Aft3d_Element>> theElements_;

			std::map<Standard_Integer, std::weak_ptr<Aft3d_Facet>> theFronts_;


			// Private functions and operators [2/28/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);


		protected:

			// default constructor [2/23/2023 Payvand]

			Aft3d_EdgeAdaptor()
			{}

			// constructors [2/23/2023 Payvand]


		public:

			// Public functions and operators [2/23/2023 Payvand]

			TnbLegMesh_EXPORT Standard_Integer NbFacets() const;
			TnbLegMesh_EXPORT Standard_Integer NbElements() const;

			TnbLegMesh_EXPORT Standard_Integer NbFronts() const;

			TnbLegMesh_EXPORT Standard_Boolean IsContainsFacet(const std::shared_ptr<Aft3d_Facet>&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsContainsElement(const std::shared_ptr<Aft3d_Element>&) const;

			TnbLegMesh_EXPORT Standard_Boolean IsContainsFront(const std::shared_ptr<Aft3d_Facet>&) const;

			const auto& Facets() const { return theFacets_; }
			const auto& Elements() const { return theElements_; }

			const auto& Fronts() const { return theFronts_; }

			TnbLegMesh_EXPORT void RemoveFacet(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void RemoveElement(const std::shared_ptr<Aft3d_Element>&);

			TnbLegMesh_EXPORT void RemoveFront(const std::shared_ptr<Aft3d_Facet>&);

			TnbLegMesh_EXPORT void InsertFacet(const std::shared_ptr<Aft3d_Facet>&);
			TnbLegMesh_EXPORT void InsertElement(const std::shared_ptr<Aft3d_Element>&);

			TnbLegMesh_EXPORT void InsertFront(const std::shared_ptr<Aft3d_Facet>&);

		};
	}
}

#endif // !_Aft3d_EdgeAdaptor_Header
