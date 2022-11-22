#pragma once
#ifndef _Ship_TransomParams_Header
#define _Ship_TransomParams_Header

#include <Ship_Parameter.hxx>

namespace tnbLib
{

	class Ship_TransomParams
	{

		/*Private Data*/

		Ship_Parameter theRake_;
		Ship_Parameter theWidth_;


	public:

		// default constructor [11/1/2022 Amir]

		Ship_TransomParams()
		{}


		// constructors [11/1/2022 Amir]


		// public functions and operators [11/1/2022 Amir]


		const auto& Rake() const
		{
			return theRake_;
		}

		auto& RakeRef()
		{
			return theRake_;
		}

		const auto& Width() const
		{
			return theWidth_;
		}

		auto& WidthRef()
		{
			return theWidth_;
		}
	};
}

#endif // !_Ship_TransomParams_Header
