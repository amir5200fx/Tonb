#pragma once
#ifndef _Aft3d_Element_Header
#define _Aft3d_Element_Header

#include <Aft3d_ElementAdaptor.hxx>
#include <Aft3d_Entity.hxx>
#include <Global_AccessMethod.hxx>
#include <Pnt3d.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/24/2023 Payvand]
		class Aft3d_Facet;
		class Aft3d_Edge;
		class Aft3d_Node;

		class Aft3d_Element
			: public Aft3d_ElementAdaptor
			, public Aft3d_Entity
		{

		public:

			enum {nbNodes = 4, nbEdges = 6, nbFactes = 4, id0 = 0, id1 = 1, id2 = 2, id3 = 4};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Aft3d_Facet>, nbFactes> theFacets_;
			std::array<std::shared_ptr<Aft3d_Edge>, nbEdges> theEdges_;
			std::array<std::shared_ptr<Aft3d_Node>, nbNodes> theNodes_;


			// Private functions and operators [3/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);
	

		public:

			// default constructor [2/24/2023 Payvand]

			Aft3d_Element()
			{}

			// constructors [2/24/2023 Payvand]

			explicit Aft3d_Element(const Standard_Integer theIndex)
				: Aft3d_Entity(theIndex)
			{}

			Aft3d_Element
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(theNodes)
			{}

			Aft3d_Element
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(std::move(theNodes))
			{}

			// Public functions and operators [2/24/2023 Payvand]


			auto NbNodes() const
			{
				return (Standard_Integer)nbNodes;
			}

			auto NbEdges() const
			{
				return (Standard_Integer)nbEdges;
			}

			auto NbFacets() const
			{
				return (Standard_Integer)nbFactes;
			}

			TnbLegMesh_EXPORT Pnt3d CalcCentre() const;

			TnbLegMesh_EXPORT Standard_Integer 
				OppositeVertexIndex(const std::shared_ptr<Aft3d_Facet>&) const;

			TnbLegMesh_EXPORT std::tuple
				<
				std::shared_ptr<Aft3d_Node>,
				std::shared_ptr<Aft3d_Node>,
				std::shared_ptr<Aft3d_Node>,
				std::shared_ptr<Aft3d_Node>
				>
				Nodes() const;

			TnbLegMesh_EXPORT std::tuple
				<
				std::shared_ptr<Aft3d_Edge>,
				std::shared_ptr<Aft3d_Edge>,
				std::shared_ptr<Aft3d_Edge>,
				std::shared_ptr<Aft3d_Edge>,
				std::shared_ptr<Aft3d_Edge>,
				std::shared_ptr<Aft3d_Edge>
				>
				Edges() const;

			TnbLegMesh_EXPORT std::tuple
				<
				std::shared_ptr<Aft3d_Facet>,
				std::shared_ptr<Aft3d_Facet>,
				std::shared_ptr<Aft3d_Facet>,
				std::shared_ptr<Aft3d_Facet>
				>
				Facets() const;
			
			//- Marcos

			GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 0)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 1)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 2)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 3)

				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 0)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 1)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 2)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 3)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 4)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 5)

				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Facet>, Facet, 0)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Facet>, Facet, 1)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Facet>, Facet, 2)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Facet>, Facet, 3)

				GLOBAL_ACCESS_VECTOR_INDEX(std::shared_ptr<Aft3d_Node>, Node)
				GLOBAL_ACCESS_VECTOR_INDEX(std::shared_ptr<Aft3d_Edge>, Edge)
				GLOBAL_ACCESS_VECTOR_INDEX(std::shared_ptr<Aft3d_Facet>, Facet)
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::legLib::Aft3d_Element);

#endif // !_Aft3d_Element_Header
