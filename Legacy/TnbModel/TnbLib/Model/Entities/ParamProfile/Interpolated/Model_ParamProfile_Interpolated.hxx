#pragma once
#ifndef _Model_ParamProfile_Interpolated_Header
#define _Model_ParamProfile_Interpolated_Header

#include <Model_ParamProfile.hxx>

namespace tnbLib
{

	class Model_ParamProfile_Interpolated
		: public Model_ParamProfile
	{

		/*Private Data*/

	protected:

		// default constructor [12/20/2022 Payvand]

		Model_ParamProfile_Interpolated()
		{}


		// COnstructors [12/21/2022 Payvand]

		Model_ParamProfile_Interpolated(const Standard_Real theLower, const Standard_Real theUpper)
			: Model_ParamProfile(theLower, theUpper)
		{}

	public:

		// public functions and operators [12/20/2022 Payvand]

	};
}

#endif // !_Model_ParamProfile_Interpolated_Header
