#pragma once
#ifndef _Model_BndParameter_Header
#define _Model_BndParameter_Header

#include <Model_Parameter.hxx>

namespace tnbLib
{

	class Model_BndParameter
		: public Model_Parameter
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;


	public:

		// default constructor [12/20/2022 Payvand]

		Model_BndParameter()
			: theLower_(0)
			, theUpper_(0)
		{}


		// constructors [12/20/2022 Payvand]

		Model_BndParameter
		(
			const Standard_Integer theIndex, 
			const word& theName,
			const Standard_Real theLower, 
			const Standard_Real theUpper, 
			const Standard_Real theValue
		)
			: Model_Parameter(theIndex, theName, theValue)
			, theLower_(theLower)
			, theUpper_(theUpper)
		{}


		// Public functions and operators [12/20/2022 Payvand]

		Standard_Boolean IsBounded() const override
		{
			return Standard_True;
		}

		Standard_Real Lower() const override
		{
			return theLower_;
		}

		Standard_Real Upper() const override
		{
			return theUpper_;
		}

	};
}

#endif // !_Model_BndParameter_Header
