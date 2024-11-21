#pragma once
#ifndef _MeshPost2d_OFTopology_Header
#define _MeshPost2d_OFTopology_Header

#include <MeshPost_Module.hxx>
#include <Entity_Connectivity.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>
#include <Global_TypeDef.hxx>

#include <map>

namespace tnbLib
{

	// Forward Declarations [7/6/2023 Payvand]
	class MeshIO2d_FEA;
	class Entity2d_CmpMesh;

	class MeshPost2d_OFTopology
		: public Global_Done
	{

	public:

		class Segment;

		static TnbMeshPost_EXPORT Standard_Boolean
			Compare
			(
				const std::weak_ptr<Segment>&,
				const std::weak_ptr<Segment>&
			);

		struct segment_cmp
		{
			bool operator()
				(
					const std::weak_ptr<Segment>& theS0, 
					const std::weak_ptr<Segment>& theS1
					) const
			{
				return Compare(theS0, theS1);
			}
		};

		class Vertex
			: public Global_Indexed
		{

			/*Private Data*/

			std::set<std::weak_ptr<Segment>, segment_cmp> theSegments_;

		public:

			// default constructor [7/6/2023 Payvand]

			Vertex()
			{}

			// constructors [7/6/2023 Payvand]

			Vertex(const Standard_Integer theIndex)
				: Global_Indexed(theIndex)
			{}

			auto NbSegments() const { return theSegments_.size(); }
			const auto& Segments() const { return theSegments_; }

			void Insert(const std::shared_ptr<Segment>&);

		};

		class Segment
			: public Global_Indexed
		{

		public:

			enum
			{
				nbVertices = 2
			};

		private:

			/*Private Data*/

			std::array<std::shared_ptr<Vertex>, nbVertices> theVertices_;

			Standard_Boolean IsBoundary_;

			Standard_Integer theOwner_;
			Standard_Integer theNeighbor_;

			word thePhysic_;

		public:

			// default constructor [6/28/2023 Payvand]

			Segment()
				: IsBoundary_(Standard_False)
				, theOwner_(0)
				, theNeighbor_(0)
			{}

			// constructors [6/28/2023 Payvand]

			Segment
			(
				const Standard_Integer theIndex,
				const std::array<std::shared_ptr<Vertex>, nbVertices>& theVertices
			)
				: Global_Indexed(theIndex)
				, theVertices_(theVertices)
				, IsBoundary_(Standard_False)
				, theOwner_(0)
				, theNeighbor_(0)
			{}

			Segment
			(
				const Standard_Integer theIndex,
				std::array<std::shared_ptr<Vertex>, nbVertices>&& theVertices
			)
				: Global_Indexed(theIndex)
				, theVertices_(std::move(theVertices))
				, IsBoundary_(Standard_False)
				, theOwner_(0)
				, theNeighbor_(0)
			{}

			// Public functions and operators [6/28/2023 Payvand]

			const auto& Vertices() const { return theVertices_; }
			auto& VerticesRef() { return theVertices_; }

			auto IsBoundary() const { return IsBoundary_; }
			auto Owner() const { return theOwner_; }
			auto Neighbor() const { return theNeighbor_; }

			const auto& Physic() const { return thePhysic_; }

			TnbMeshPost_EXPORT Standard_Boolean
				ChackSense
				(
					const std::shared_ptr<Vertex>&,
					const std::shared_ptr<Vertex>&
				) const;
			TnbMeshPost_EXPORT std::shared_ptr<Vertex>
				Opposite(const std::shared_ptr<Vertex>&) const;

			void SetBoundary(const Standard_Boolean isBoundary)
			{ IsBoundary_ = isBoundary; }
			void SetOwner(const Standard_Integer theIndex) 
			{ theOwner_ = theIndex; }
			void SetNeighbor(const Standard_Integer theIndex) 
			{ theNeighbor_ = theIndex; }

			void SetPhysic(const word& thePhysic) 
			{ thePhysic_ = thePhysic; }

			static TnbMeshPost_EXPORT std::shared_ptr<Segment>
				IsValidToCreate
				(
					const std::shared_ptr<Vertex>&,
					const std::shared_ptr<Vertex>&
				);
			static TnbMeshPost_EXPORT Standard_Boolean
				Compare
				(
					const std::shared_ptr<Segment>&,
					const std::shared_ptr<Segment>&
				);
		};

		class Edge
			: public Global_Indexed
		{

			/*Private Data*/

			Standard_Integer theV0_;
			Standard_Integer theV1_;

			Standard_Integer theOwner_;
			Standard_Integer theNeighbor_;

		public:

			// default constructor [7/6/2023 Payvand]

			Edge()
				: theV0_(0)
				, theV1_(0)
			{}

			Edge(const Standard_Integer theV0, const Standard_Integer theV1)
				: theV0_(theV0)
				, theV1_(theV1)
			{}

			// Public functions and operators [7/6/2023 Payvand]

			auto V0() const { return theV0_; }
			auto V1() const { return theV1_; }
			auto& V0() { return theV0_; }
			auto& V1() { return theV1_; }

			auto Owner() const { return theOwner_; }
			auto Neighbor() const { return theNeighbor_; }

			void SetOwner(const Standard_Integer theIndex) 
			{ theOwner_ = theIndex; }
			void SetNeighbor(const Standard_Integer theIndex) 
			{ theNeighbor_ = theIndex; }
		};

	private:

		/*Private Data*/

		std::shared_ptr<MeshIO2d_FEA> theMeshIO_;

		std::vector<Edge> theInteriors_;
		std::map<word, std::vector<Edge>> theBoundaries_;

		// Private functions and operators [7/6/2023 Payvand]

		TnbMeshPost_EXPORT std::tuple
			<
			std::vector<std::shared_ptr<Vertex>>,
			std::vector<std::shared_ptr<Segment>>,
			std::map<Standard_Integer, Standard_Integer>
			>
			CalcGragh
			(
				const Entity2d_CmpMesh&,
				const std::vector<std::tuple<Standard_Integer, Standard_Integer, word>>&
			);

		static TnbMeshPost_EXPORT std::vector<std::tuple<Standard_Integer, Standard_Integer, word>>
			RetrieveBoundaries(const MeshIO2d_FEA&);

	public:

		// default constructor [7/6/2023 Payvand]

		MeshPost2d_OFTopology()
			= default;

		// constructors [7/6/2023 Payvand]


		// Public functions and operators [7/6/2023 Payvand]

		const auto& MeshIO() const { return theMeshIO_; }
		const auto& Interiors() const { return theInteriors_; }
		const auto& Boundaries() const { return theBoundaries_; }

		TnbMeshPost_EXPORT std::vector<Edge> RetrieveEdges() const;
		TnbMeshPost_EXPORT std::vector<Edge> RetrieveBoundaries() const;
		TnbMeshPost_EXPORT std::map<Standard_Integer, std::vector<Standard_Integer>> 
			RetrieveElementToEdgesMap() const;

		TnbMeshPost_EXPORT void Perform();

		void SetMeshIO(const std::shared_ptr<MeshIO2d_FEA>& theMeshIO) 
		{ theMeshIO_ = theMeshIO; }

	};
}

#endif // !_MeshPost2d_OFTopology_Header
