#pragma once
#ifndef _Ship_KeelParams_Header
#define _Ship_KeelParams_Header

#include <Ship_Parameter.hxx>

namespace tnbLib
{

	class Ship_KeelParams
	{

		/*Private Data*/

		Ship_Parameter thePosition_;
		Ship_Parameter theRisePoint_;
		Ship_Parameter theRiseSlope_;
		Ship_Parameter theTransomSlope_;


	public:

		// default constructor [11/1/2022 Amir]

		Ship_KeelParams()
		{}


		// public functions and operators [11/1/2022 Amir]

		const auto& Position() const
		{
			return thePosition_;
		}

		auto& PositionRef()
		{
			return thePosition_;
		}

		const auto& RisePoint() const
		{
			return theRisePoint_;
		}

		auto& RisePointRef()
		{
			return theRisePoint_;
		}

		const auto& RiseSlope() const
		{
			return theRiseSlope_;
		}

		auto& RiseSlopeRef()
		{
			return theRiseSlope_;
		}

		const auto& TransomSlope() const
		{
			return theTransomSlope_;
		}
		
	};
}

#endif // !_Ship_KeelParams_Header
