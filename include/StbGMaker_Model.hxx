#pragma once
#ifndef _StbGMaker_Model_Header
#define _StbGMaker_Model_Header

#include <StbGMaker_Entity.hxx>
#include <Marine_ModelsFwd.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations

	class StbGMaker_Model
		: public StbGMaker_Entity
	{

		friend class StbGMaker_Creator;

		/*Private Data*/

		std::shared_ptr<marineLib::Model_Hull> theHull_;

		std::vector<std::shared_ptr<marineLib::Model_Tank>> theTanks_;
		std::vector<std::shared_ptr<marineLib::Model_Sail>> theSails_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbStbGMaker_EXPORT);

		auto& ChangeHull()
		{
			return theHull_;
		}

		auto& ChangeTanks()
		{
			return theTanks_;
		}

		auto& ChangeSails()
		{
			return theSails_;
		}

	public:

		//- default constructor

		StbGMaker_Model()
		{}


		//- constructors

		TnbStbGMaker_EXPORT explicit StbGMaker_Model(const Standard_Integer theIndex);

		TnbStbGMaker_EXPORT StbGMaker_Model
		(
			const Standard_Integer theIndex, 
			const word& theName
		);


		//- public functions and operators

		auto NbTanks() const
		{
			return (Standard_Integer)theTanks_.size();
		}

		auto NbSails() const
		{
			return (Standard_Integer)theSails_.size();
		}

		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}

		const auto& Sails() const
		{
			return theSails_;
		}
	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::StbGMaker_Model);

#endif // !_StbGMaker_Model_Header
