#pragma once
#ifndef _HsModeler_Model_Header
#define _HsModeler_Model_Header

#include <HsModeler_Entity.hxx>

#include <vector>
#include <map>

namespace tnbLib
{

	// Forward Declarations
	class HsModeler_Hull;
	class HsModeler_Sail;
	class HsModeler_Tank;

	class HsModeler_Model
		: public HsModeler_Entity
	{

		/*Private Data*/

		std::shared_ptr<HsModeler_Hull> theHull_;
		std::shared_ptr<HsModeler_Sail> theSail_;
		
		std::map<Standard_Integer, std::shared_ptr<HsModeler_Tank>> theTanks_;

	public:

		HsModeler_Model();

		HsModeler_Model(const Standard_Integer theIndex);

		HsModeler_Model(const Standard_Integer theIndex, const word& theName);


		Standard_Integer NbTanks() const
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
	};
}

#endif // !_HsModeler_Model_Header
