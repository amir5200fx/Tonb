#pragma once
#ifndef _Voyage_Dijkstra_Header
#define _Voyage_Dijkstra_Header

#include <Voyage_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [7/21/2023 Payvand]
	class VoyageFun_CostFunction;
	class Voyage_Graph;
	class Voyage_Node;

	class Voyage_Dijkstra
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<Voyage_Graph> theGraph_;

		std::shared_ptr<VoyageFun_CostFunction> theCost_;


		// Private functions and operators [7/21/2023 Payvand]

		std::shared_ptr<Voyage_Node> AnalyzeLevel(const std::shared_ptr<Voyage_Node>& theCurrent, const std::vector<std::shared_ptr<Voyage_Node>>&, std::vector<Standard_Real>& theCost) const;

	public:

		// default constructor [7/21/2023 Payvand]

		Voyage_Dijkstra()
		{}


		// constructors [7/21/2023 Payvand]

		// Public functions and operators [7/21/2023 Payvand]

		const auto& Graph() const { return theGraph_; }
		const auto& Cost() const { return theCost_; }

		void Perform();

	};
}

#endif // !_Voyage_Dijkstra_Header
