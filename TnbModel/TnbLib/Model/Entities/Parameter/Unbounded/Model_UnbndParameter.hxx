#pragma once
#ifndef _Model_UnbndParameter_Header
#define _Model_UnbndParameter_Header

#include <Model_Parameter.hxx>

#include <Standard_Real.hxx>

namespace tnbLib
{

	class Model_UnbndParameter
		: public Model_Parameter
	{

		/*Private Data*/

	public:

		// default constructor [12/20/2022 Payvand]

		Model_UnbndParameter()
		{}

		// constructors [12/20/2022 Payvand]

		Model_UnbndParameter
		(
			const Standard_Integer theIndex,
			const word& theName,
			const Standard_Real theValue = 0
		)
			: Model_Parameter(theIndex, theName, theValue)
		{}

		// Public functions and operators [12/20/2022 Payvand]

		Standard_Boolean IsUnbounded() const override
		{
			return Standard_True;
		}

		Standard_Real Lower() const override
		{
			return RealFirst();
		}

		Standard_Real Upper() const override
		{
			return RealLast();
		}

	};
}

#endif // !_Model_UnbndParameter_Header
