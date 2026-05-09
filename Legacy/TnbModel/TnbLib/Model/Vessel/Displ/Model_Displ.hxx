#pragma once
#ifndef _Model_Displ_Header
#define _Model_Displ_Header

#include <Model_Vessel.hxx>

namespace tnbLib
{

	class Model_Displ
		: public Model_Vessel
	{

		/*Private Data*/

	protected:

		// default constructor [12/21/2022 Payvand]

		Model_Displ()
		{}

		// constructors [12/21/2022 Payvand]

		Model_Displ(const Standard_Integer theIndex, const word& theName)
			: Model_Vessel(theIndex, theName)
		{}

	public:

		// Public functions and operators [12/21/2022 Payvand]

		Standard_Boolean IsDisplacement() const override
		{
			return Standard_True;
		}

	};
}

#endif // !_Model_Displ_Header
