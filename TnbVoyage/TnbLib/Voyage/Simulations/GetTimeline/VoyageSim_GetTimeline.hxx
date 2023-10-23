#pragma once
#ifndef _VoyageSim_GetTimeline_Header
#define _VoyageSim_GetTimeline_Header

#include <VoyageSim_Graph.hxx>
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
			
			Standard_Integer id;
			Pnt2d pt;
		};

	private:

		/*Private Data*/

		std::shared_ptr<VoyageSim_MinFuel> theSimulation_;
		
		std::shared_ptr<Geo_AdTree<std::shared_ptr<Node>>> theEngine_;

	public:

		// default constructor

		VoyageSim_GetTimeline()
		{}

		// constructors

		VoyageSim_GetTimeline(const std::shared_ptr<VoyageSim_MinFuel>& theSim)
			: theSimulation_(theSim)
		{}


		// Public functions and operators

		

		void Perform();
		
		
	};
}

#endif