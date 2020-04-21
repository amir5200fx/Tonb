#pragma once
#ifndef _HydStatic_Model_Header
#define _HydStatic_Model_Header

#include <HydStatic_Entity.hxx>

#include <map>

namespace tnbLib
{

	namespace hydStcLib
	{
		class Model_Hull;
		class Model_Sail;
		class Model_Tank;
		class Model_Mass;
		class Model_Light;
		class Model_Moment;
	}

	class HydStatic_Model
		: public HydStatic_Entity
	{

		/*Private Data*/

		std::shared_ptr<hydStcLib::Model_Hull> theHull_;
		

		std::map<Standard_Integer, std::shared_ptr<hydStcLib::Model_Tank>> theTanks_;
		std::map<Standard_Integer, std::shared_ptr<hydStcLib::Model_Mass>> theMasses_;
		std::map<Standard_Integer, std::shared_ptr<hydStcLib::Model_Moment>> theMoments_;

		std::shared_ptr<hydStcLib::Model_Light> theLight_;

	public:

		HydStatic_Model();

		HydStatic_Model(const Standard_Integer theIndex);

		HydStatic_Model(const Standard_Integer theIndex, const word& theName);


		const auto& Hull() const
		{
			return theHull_;
		}

		const auto& Light() const
		{
			return theLight_;
		}

		const auto& Tanks() const
		{
			return theTanks_;
		}

		const auto& Masses() const
		{
			return theMasses_;
		}

		const auto& Moments() const
		{
			return theMoments_;
		}
	};
}

#endif // !_HydStatic_Model_Header
