#pragma once
#ifndef _VoyageSim_GetTimeline_Header
#define _VoyageSim_GetTimeline_Header

#include <VoyageWP_Net.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class VoyageSim_MinFuel;
	
	template<class T>
	class Geo_AdTree;
	
	class VoyageSim_GetTimeline
		: public Global_Done
	{

	public:

		struct Node
		{
			typedef Pnt2d ptType;
			
			std::shared_ptr<VoyageWP_Net::Node> node;
		};

	private:

		/*Private Data*/

		std::shared_ptr<VoyageSim_MinFuel> theSimulation_;

		//- Cache data
		std::shared_ptr<Geo_AdTree<std::shared_ptr<Node>>> theEngine_;

	public:

		// default constructor

		VoyageSim_GetTimeline()
		= default;

		// constructors

		explicit VoyageSim_GetTimeline(const std::shared_ptr<VoyageSim_MinFuel>& theSim)
			: theSimulation_(theSim)
		{}


		// Public functions and operators

		[[nodiscard]] const auto& Simulation() const { return theSimulation_; }

		TnbVoyage_EXPORT std::vector<std::shared_ptr<VoyageWP_Net::Node>>
			Find(const Pnt2d&, const Standard_Real theRadius) const;
		// Returns the timeline of the node with a specific id.
		TnbVoyage_EXPORT std::vector<Standard_Real> Timeline(const Standard_Integer) const;

		TnbVoyage_EXPORT void Perform();
		
		
	};
}

#endif