#pragma once
#ifndef _VoyageSim_GetGraphNode_Header
#define _VoyageSim_GetGraphNode_Header

#include <VoyageSim_Graph.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class VoyageSim_MinFuel;

	template<class T>
	class Geo_AdTree;
	class Pnt3d;

	class VoyageSim_GetGraphNode
		: public Global_Done
	{

	public:

		struct Node
		{
			typedef Pnt3d ptType;

			std::shared_ptr<VoyageSim_Graph::Node> node;
		};

		struct Position
		{
			Pnt2d value;
		};

		struct Time
		{
			Standard_Real value;
		};

		/*Private Data*/

		std::shared_ptr<VoyageSim_MinFuel> theSimulation_;

		// Cache data
		std::shared_ptr<Geo_AdTree<std::shared_ptr<Node>>> theEngine_;

	public:

		// default constructor

		VoyageSim_GetGraphNode()
			= default;

		// constructors

		explicit VoyageSim_GetGraphNode(const std::shared_ptr<VoyageSim_MinFuel>& theSim)
			: theSimulation_(theSim)
		{}

		// Public functions and operators

		[[nodiscard]] const auto& Simulation() const { return theSimulation_; }

		TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageSim_Graph::Node>>
			Find(const std::pair<Position, Time>& theState, const Standard_Real theRadius) const;

		TnbVoyage_EXPORT void Perform();

		// Static functions

		static TnbVoyage_EXPORT Pnt3d ConvertToPnt3d(const std::pair<Position, Time>&);
	};

}

#endif