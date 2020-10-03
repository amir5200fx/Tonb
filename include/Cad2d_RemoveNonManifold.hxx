#pragma once
#ifndef _Cad2d_RemoveNonManifold_Header
#define _Cad2d_RemoveNonManifold_Header

#include <Global_Indexed.hxx>
#include <Global_Done.hxx>
#include <Geo_ItemCounter.hxx>

#include <memory>
#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class Pln_Edge;
	class Pln_Vertex;

	class Cad2d_RemoveNonManifold
		: public Global_Done
	{

	public:

		class Segment;

		class Node
			: public Global_Indexed
		{

			/*Private Data*/

			std::shared_ptr<Pln_Vertex> theVtx_;

			std::map<Standard_Integer, std::weak_ptr<Segment>> theSegments_;

		public:

			Node
			(
				const std::shared_ptr<Pln_Vertex>& theVtx
			)
				: theVtx_(theVtx)
			{}

			Node
			(
				const Standard_Integer theIndex, 
				const std::shared_ptr<Pln_Vertex>& theVtx
			)
				: Global_Indexed(theIndex)
				, theVtx_(theVtx)
			{}

			const auto& Vtx() const
			{
				return theVtx_;
			}

			const auto& Segments() const
			{
				return theSegments_;
			}

			auto NbSegments() const
			{
				return (Standard_Integer)theSegments_.size();
			}

			Standard_Boolean IsOrphan() const;

			//std::shared_ptr<Segment> Select(const Standard_Integer theIndex) const;

			std::weak_ptr<Segment> 
				Remove
				(
					const Standard_Integer theIndex
				);

			void Insert
			(
				const Standard_Integer theIndex,
				const std::shared_ptr<Segment>& theSegment
			);
		};


		class Segment
			: public Global_Indexed
		{

			/*Private Data*/

			std::vector<std::shared_ptr<Pln_Edge>> theEdges_;

			std::shared_ptr<Node> theNode0_;
			std::shared_ptr<Node> theNode1_;

		public:

			Segment
			(
				std::shared_ptr<Node>&& theNode0, 
				std::shared_ptr<Node>&& theNode1,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			);

			Segment
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			);

			const auto& Edges() const
			{
				return theEdges_;
			}

			auto& EdgesRef()
			{
				return theEdges_;
			}

			const auto& Node0() const
			{
				return theNode0_;
			}

			const auto& Node1() const
			{
				return theNode1_;
			}

			virtual Standard_Boolean IsRing() const
			{
				return Standard_False;
			}

			//- WARNING! this method makes new edges from the existing ones
			virtual std::vector<std::shared_ptr<Pln_Edge>> RetrieveEdges() const;
		};


		class Ring
			: public Segment
		{

			/*Private Data*/

			void CheckRing();

		public:

			Ring
			(
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			)
				: Segment
				(
					std::move(theNode0), 
					std::move(theNode1), std::move(theEdges)
				)
			{
				CheckRing();
			}

			Ring
			(
				const Standard_Integer theIndex,
				std::shared_ptr<Node>&& theNode0,
				std::shared_ptr<Node>&& theNode1,
				std::vector<std::shared_ptr<Pln_Edge>>&& theEdges
			)
				: Segment
				(
					theIndex, std::move(theNode0),
					std::move(theNode1), std::move(theEdges)
				)
			{
				CheckRing();
			}

			Standard_Boolean IsRing() const override
			{
				return Standard_True;
			}
		};

	private:

		/*Private Data*/

		mutable Geo_ItemCounter theSegmentCounter_;

		std::map<Standard_Integer, std::shared_ptr<Node>> theNodes_;
		std::map<Standard_Integer, std::shared_ptr<Segment>> theSegments_;

		const std::vector<std::shared_ptr<Pln_Edge>>& theEdges_;


		auto& SegmentCounter() const
		{
			return theSegmentCounter_;
		}

		const auto& Nodes() const
		{
			return theNodes_;
		}

		auto& NodesRef()
		{
			return theNodes_;
		}

		const auto& Segments() const
		{
			return theSegments_;
		}

		auto& SegmentsRef()
		{
			return theSegments_;
		}

		std::shared_ptr<Node>
			SelectNode
			(
				const Standard_Integer theIndex
			) const;

		std::shared_ptr<Cad2d_RemoveNonManifold::Segment>
			RetrieveString
			(
				const std::shared_ptr<Cad2d_RemoveNonManifold::Node>& theNode
			) const;

		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> 
			RetrieveSegments
			(
				const std::shared_ptr<Cad2d_RemoveNonManifold::Node>& theNode)
			;

		void Import(std::shared_ptr<Node>&& theNode);
		void Import(std::shared_ptr<Segment>&& theSegment);

		void Remove(const std::shared_ptr<Node>& theNode);

		void InsertVertices
		(
			const std::vector<std::shared_ptr<Pln_Vertex>>& theVertices
		);

		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>> 
			InsertEdges();

		void AttachEdgesToNodes
		(
			const std::shared_ptr<Cad2d_RemoveNonManifold::Segment>& theSegment
		) const;

	public:

		Cad2d_RemoveNonManifold
		(
			const std::vector<std::shared_ptr<Pln_Edge>>& theEdges
		)
			: theEdges_(theEdges)
		{}

		Standard_Integer NbRings() const;

		const auto& Edges() const
		{
			return theEdges_;
		}

		std::vector<std::shared_ptr<Cad2d_RemoveNonManifold::Segment>>
			RetrieveRings() const;

		void Perform();
	};
}

#endif // !_Cad2d_RemoveNonManifold_Header
