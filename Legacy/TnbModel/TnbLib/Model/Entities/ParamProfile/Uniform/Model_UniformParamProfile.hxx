#pragma once
#ifndef _Model_UniformParamProfile_Header
#define _Model_UniformParamProfile_Header

#include <Model_ParamProfile.hxx>

namespace tnbLib
{

	class Model_UniformParamProfile
		: public Model_ParamProfile
	{

		/*Private Data*/

		Standard_Real theLower_;
		Standard_Real theUpper_;

		Standard_Real theValue_;

	public:

		// default constructor [12/20/2022 Payvand]

		Model_UniformParamProfile()
			: theLower_(0)
			, theUpper_(0)
			, theValue_(0)
		{}

		// constructors [12/20/2022 Payvand]

		Model_UniformParamProfile
		(
			const Standard_Real theLower, 
			const Standard_Real theUpper,
			const Standard_Real theValue = 0
		)
			: theLower_(theLower)
			, theUpper_(theUpper)
			, theValue_(theValue)
		{}


		// Public functions and operators [12/20/2022 Payvand]

		Standard_Real Value(const Standard_Real) const override;

	};
}

#endif // !_Model_UniformParamProfile_Header
