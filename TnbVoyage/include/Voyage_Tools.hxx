#pragma once
#ifndef _Voyage_Tools_Header
#define _Voyage_Tools_Header

#include <Voyage_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]

	class Voyage_Edge;
	class Voyage_Node;

	class Voyage_Tools
	{

	public:

		// the nodes are sorted based on their indices 
		// So the first node is departure and the last one is destination [7/21/2023 Payvand]
		static TnbVoyage_EXPORT std::vector<std::shared_ptr<Voyage_Node>> 
			RetrieveNodes(const std::vector<std::shared_ptr<Voyage_Edge>>&);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Node> 
			NeighborNode
			(
				const std::shared_ptr<Voyage_Node>& theCurrent, 
				const std::shared_ptr<Voyage_Edge>& theEdge
			);

		static TnbVoyage_EXPORT std::shared_ptr<Voyage_Edge> 
			RetrieveEdge
			(
				const std::shared_ptr<Voyage_Node>&,
				const std::shared_ptr<Voyage_Node>&
			);

	};
}

#endif // !_Voyage_Tools_Header
