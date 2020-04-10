#pragma once
#ifndef _Marine_VesselModel_Header
#define _Marine_VesselModel_Header

#include <Marine_Model.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class Marine_VesselTank;
	class Marine_VesselSail;
	class Marine_VesselHull;

	class Marine_VesselModel
		: public Marine_Model
	{

		/*Private Data*/

		std::shared_ptr<Marine_VesselHull> theHull_;
		std::shared_ptr<Marine_VesselSail> theSail_;

		std::vector<std::shared_ptr<Marine_VesselTank>> theTanks_;

	public:

		Marine_VesselModel();

		Marine_VesselModel
		(
			const Standard_Integer theIndex
		);

		Marine_VesselModel
		(
			const Standard_Integer theIndex,
			const word& theName
		);

		Standard_Boolean IsVessel() const override
		{
			return Standard_True;
		}

		auto NbTanks() const
		{
			return (Standard_Integer)theTanks_.size();
		}

		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& Sail() const
		{
			return theSail_;
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}

		auto& ChangeTanks()
		{
			return theTanks_;
		}

		void SetHull
		(
			const std::shared_ptr<Marine_VesselHull>& theHull
		)
		{
			theHull_ = theHull;
		}

		void SetSail
		(
			const std::shared_ptr<Marine_VesselSail>& theSail
		)
		{
			theSail_ = theSail;
		}
	};
}

#endif // !_Marine_VesselModel_Header
