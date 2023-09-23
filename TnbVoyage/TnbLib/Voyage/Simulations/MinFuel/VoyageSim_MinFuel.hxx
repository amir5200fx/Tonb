#pragma once
#ifndef _VoyageSim_MinFuel_Header
#define _VoyageSim_MinFuel_Header

#include <Pnt2d.hxx>
#include <Global_Done.hxx>
#include <Global_Indexed.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class VoyageWP_Net;

	class VoyageSim_MinFuel
		: public Global_Done
	{


		/*Private Data*/

		std::shared_ptr<VoyageWP_Net> theNet_;

		Standard_Real theMinVel_;
		Standard_Real theMaxVel_;

		Standard_Integer theNbLevels_;
		Standard_Integer theNbSamples_;

		// functions
		std::function<Standard_Real(const std::pair<Pnt2d, Standard_Real>&, const std::pair<Pnt2d, Standard_Real>&, const Standard_Real, const Standard_Integer)> theResistFun_;
		std::function<Standard_Real(const Pnt2d&, const Pnt2d&)> theDist_;

	public:

		// default constructor

		VoyageSim_MinFuel()
		{}

		// constructors

		// Public functions and operators

		const auto& Net() const { return theNet_; }

		auto MinVel() const { return theMinVel_; }
		auto MaxVel() const { return theMaxVel_; }
		auto NbLevels() const { return theNbLevels_; }
		auto NbSamples() const { return theNbSamples_; }

		void Perform();

	};
}

#endif
