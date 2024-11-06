#pragma once
#ifndef _Aft3d_Facet_Header
#define _Aft3d_Facet_Header

#include <Aft3d_FacetAdaptor.hxx>
#include <Aft3d_Entity.hxx>
#include <Pnt3d.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	namespace legLib
	{

		// Forward Declarations [2/23/2023 Payvand]
		class Aft3d_Edge;
		class Aft3d_Node;

		class Aft3d_Facet
			: public Aft3d_FacetAdaptor
			, public Aft3d_Entity
		{

		public:

			enum 
			{
				nbNodes = 3,
				nbEdges = 3,
				id0 = 0, 
				id1 = 1, 
				id2 = 2
			};

			typedef std::array<std::shared_ptr<Aft3d_Node>, nbNodes> NodeArray3;
			typedef std::array<std::shared_ptr<Aft3d_Edge>, nbEdges> EdgeArray3;

		private:

			/*Private Data*/

			Standard_Boolean isCavity_;

			std::array<std::shared_ptr<Aft3d_Node>, nbNodes> theNodes_;
			std::array<std::shared_ptr<Aft3d_Edge>, nbEdges> theEdges_;

			Standard_Real theCharLength_;

			// Private functions and operators [3/1/2023 Payvand]

			TNB_SERIALIZATION(TnbLegMesh_EXPORT);

		protected:

			// default constructor [2/23/2023 Payvand]

			Aft3d_Facet()
				: isCavity_(Standard_False)
				, theCharLength_(0)
			{}


			// constructors [2/23/2023 Payvand]

			Aft3d_Facet(const Standard_Integer theIndex)
				: Aft3d_Entity(theIndex)
				, isCavity_(Standard_False)
				, theCharLength_(0)
			{}

			Aft3d_Facet
			(
				const Standard_Integer theIndex, 
				const std::array<std::shared_ptr<Aft3d_Node>, nbNodes>& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(theNodes)
				, isCavity_(Standard_False)
				, theCharLength_(0)
			{}

			Aft3d_Facet
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Aft3d_Node>, nbNodes>&& theNodes
			)
				: Aft3d_Entity(theIndex)
				, theNodes_(std::move(theNodes))
				, isCavity_(Standard_False)
				, theCharLength_(0)
			{}


		public:

			// Public functions and operators [2/23/2023 Payvand]

			auto IsCavity() const
			{
				return isCavity_;
			}

			auto NbNodes() const { return (Standard_Integer)nbNodes; }
			auto NbEdges() const { return (Standard_Integer)nbEdges; }

			const auto& GetNodes() const { return theNodes_; }
			const auto& GetEdges() const { return theEdges_; }

			auto CharLength() const { return theCharLength_; }

			TnbLegMesh_EXPORT Standard_Boolean IsOnFront() const;
			TnbLegMesh_EXPORT Standard_Boolean IsOrphan() const;

			TnbLegMesh_EXPORT Standard_Real Oriented(const Pnt3d&) const;
			TnbLegMesh_EXPORT Standard_Real CalcDistance(const Pnt3d&) const;
			TnbLegMesh_EXPORT Standard_Real CalcSquareDistance(const Pnt3d&) const;

			TnbLegMesh_EXPORT Standard_Real SearchRadius() const;

			TnbLegMesh_EXPORT Standard_Boolean IsRightSide(const Pnt3d&) const;
			TnbLegMesh_EXPORT Standard_Boolean IsLeftSide(const Pnt3d&) const;

			TnbLegMesh_EXPORT Standard_Integer FindNodeId(const std::shared_ptr<Aft3d_Node>&) const;

			TnbLegMesh_EXPORT virtual Standard_Boolean IsBoundary() const;
			TnbLegMesh_EXPORT virtual Standard_Boolean IsInterior() const;

			TnbLegMesh_EXPORT Pnt3d CalcCentre() const;

			TnbLegMesh_EXPORT std::tuple<Pnt3d, Pnt3d, Pnt3d> RetrieveCoords() const;
			TnbLegMesh_EXPORT std::tuple<std::shared_ptr<Aft3d_Node>, std::shared_ptr<Aft3d_Node>, std::shared_ptr<Aft3d_Node>> Nodes() const;
			TnbLegMesh_EXPORT std::tuple<std::shared_ptr<Aft3d_Edge>, std::shared_ptr<Aft3d_Edge>, std::shared_ptr<Aft3d_Edge>> Edges() const;

			void SetCharLength(const Standard_Real x) { theCharLength_ = x; }

			inline void SetIsCavity(const Standard_Boolean isIt);
			inline void SetAsNonCavity();
			inline void SetAsCavity();

			// Macros [2/23/2023 Payvand]

			GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 0)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 1)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Node>, Node, 2)

				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 0)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 1)
				GLOBAL_ACCESS_VECTOR(std::shared_ptr<Aft3d_Edge>, Edge, 2)

				GLOBAL_ACCESS_VECTOR_INDEX(std::shared_ptr<Aft3d_Node>, Node)
				GLOBAL_ACCESS_VECTOR_INDEX(std::shared_ptr<Aft3d_Edge>, Edge)

		};
	}
}

#include <Aft3d_FacetI.hxx>

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::legLib::Aft3d_Facet);

#endif // !_Aft3d_Facet_Header
