#pragma once
#ifndef _StbGMaker_Model_Header
#define _StbGMaker_Model_Header

#include <StbGMaker_Entity.hxx>

#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class StbGMaker_Hull;
	class StbGMaker_Sail;
	class StbGMaker_Tank;
	class StbGMaker_Creator;

	class StbGMaker_Model
		: public StbGMaker_Entity
	{

		friend class StbGMaker_Creator;
		/*Private Data*/

		std::shared_ptr<StbGMaker_Hull> theHull_;

		std::vector<std::shared_ptr<StbGMaker_Tank>> theTanks_;
		std::vector<std::shared_ptr<StbGMaker_Sail>> theSails_;


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

		template<class... _Types>
		StbGMaker_Model(_Types&&... _Args)
			: StbGMaker_Entity(_Args)
		{}


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

#endif // !_StbGMaker_Model_Header
