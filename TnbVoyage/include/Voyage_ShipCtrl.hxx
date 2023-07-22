#pragma once
#ifndef _Voyage_ShipCtrl_Header
#define _Voyage_ShipCtrl_Header

#include <Global_Serialization.hxx>

#include <Standard_TypeDef.hxx>

namespace tnbLib
{

	class Voyage_ShipCtrl
	{

		/*Private Data*/

		Standard_Real theVelocity_;
		Standard_Real theAngle_;


		// Private functions and operators [7/10/2023 Payvand]

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int file_version)
		{
			ar& theVelocity_;
			ar& theAngle_;
		}

	public:

		// default constructor [7/10/2023 Payvand]

		Voyage_ShipCtrl()
			: theVelocity_(0)
			, theAngle_(0)
		{}

		// constructors [7/10/2023 Payvand]

		Voyage_ShipCtrl(const Standard_Real theVelocity, const Standard_Real theAngle)
			: theVelocity_(theVelocity)
			, theAngle_(theAngle)
		{}

		// Public functions and operators [7/10/2023 Payvand]

		auto Velocity() const { return theVelocity_; }
		auto Angle() const { return theAngle_; }

		void SetVelocity(const Standard_Real theVelocity) { theVelocity_ = theVelocity; }
		void SetAngle(const Standard_Real theAngle) { theAngle_ = theAngle; }

	};

}

#endif // !_Voyage_ShipCtrl_Header
