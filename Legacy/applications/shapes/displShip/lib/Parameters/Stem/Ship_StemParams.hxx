#pragma once
#ifndef _Ship_StemParams_Header
#define _Ship_StemParams_Header

#include <Ship_Parameter.hxx>

namespace tnbLib
{

	class Ship_StemParams
	{

		/*private Data*/

		Ship_Parameter theBowRounding_;
		Ship_Parameter theStemRake_;
		Ship_Parameter theForeFootShape_;


	public:

		// default constructor [11/1/2022 Amir]

		Ship_StemParams()
		{}


		// constructors [11/1/2022 Amir]


		// public functions and operators [11/1/2022 Amir]


		const auto& BowRounding() const
		{
			return theBowRounding_;
		}

		auto& BowRoundingRef()
		{
			return theBowRounding_;
		}

		const auto& StemReke() const
		{
			return theStemRake_;
		}

		auto& StemRakeRef()
		{
			return theStemRake_;
		}

		const auto& ForeFootShape() const
		{
			return theForeFootShape_;
		}

		auto& ForeFootShapeRef() 
		{
			return theForeFootShape_;
		}
	};
}

#endif // !_Ship_StemParams_Header
