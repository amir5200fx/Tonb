#pragma once
#ifndef _Voyage_Graph_Header
#define _Voyage_Graph_Header

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]
	class Voyage_Edge;
	class Voyage_Node;

	class Voyage_Graph
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Node> theDeparture_;
		std::shared_ptr<Voyage_Node> theDestination_;

		std::vector<std::shared_ptr<Voyage_Edge>> theEdges_;

	public:

		// default constructor [7/21/2023 Payvand]

		Voyage_Graph()
		{}

		// constructors [7/21/2023 Payvand]

		Voyage_Graph(const std::vector<std::shared_ptr<Voyage_Edge>>& theEdges)
			: theEdges_(theEdges)
		{}

		Voyage_Graph(std::vector<std::shared_ptr<Voyage_Edge>>&& theEdges)
			: theEdges_(std::move(theEdges))
		{}


		// Public functions and operators [7/21/2023 Payvand]

		const auto& Edges() const { return theEdges_; }
		auto& EdgesRef() { return theEdges_; }

		const auto& Departure() const { return theDeparture_; }
		const auto& Destination() const { return theDestination_; }

		void SetEdges(const std::vector<std::shared_ptr<Voyage_Edge>>& theEdges) { theEdges_ = theEdges; }
		void SetEdges(std::vector<std::shared_ptr<Voyage_Edge>>&& theEdges) { theEdges_ = std::move(theEdges); }

		void SetDeparture(const std::shared_ptr<Voyage_Node>& theNode) { theDeparture_ = theNode; }
		void SetDestination(const std::shared_ptr<Voyage_Node>& theNode) { theDestination_ = theNode; }
	};

}

#endif // !_Voyage_Graph_Header
