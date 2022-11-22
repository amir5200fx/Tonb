#pragma once
#ifndef _Ship_Parameter_Header
#define _Ship_Parameter_Header

#include <Ship_Entity.hxx>

namespace tnbLib
{

	class Ship_Parameter
		: public Ship_Entity
	{

		/*Private Data*/

		Standard_Real theValue_;

	public:

		// default constructor [10/31/2022 Amir]

		Ship_Parameter()
			: theValue_(0)
		{}

		explicit Ship_Parameter(const Standard_Real theValue)
			: theValue_(theValue)
		{}

		Ship_Parameter(const Standard_Integer theIndex, const word& theName, const Standard_Real theValue)
			: Ship_Entity(theIndex, theName)
			, theValue_(theValue)
		{}

		// public functions and operator [10/31/2022 Amir]

		auto Value() const
		{
			return theValue_;
		}

		auto operator()() const
		{
			return Value();
		}

		void SetValue(const Standard_Real x)
		{
			theValue_ = x;
		}
	};
}

#endif // !_Ship_Parameter_Header
