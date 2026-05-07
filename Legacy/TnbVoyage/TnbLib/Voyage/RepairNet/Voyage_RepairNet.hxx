#pragma once
#ifndef _Voyage_RepairNet_Header
#define _Voyage_RepairNet_Header

#include <Voyage_Module.hxx>
#include <Global_Done.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations
	class VoyageWP_Net;

	class Voyage_RepairNet
		: public Global_Done
	{

		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;

	public:

		// default constructor

		TnbVoyage_EXPORT Voyage_RepairNet();

		// constructors

		explicit Voyage_RepairNet(const std::shared_ptr<VoyageWP_Net>& theNet)
			: theNet_(theNet)
		{}

		// Public functions and operators

		const auto& Net() const { return theNet_; }

		TnbVoyage_EXPORT void Perform();
		void SetNet(const std::shared_ptr<VoyageWP_Net>& theNet) { theNet_ = theNet; }
		
	};
}

#endif