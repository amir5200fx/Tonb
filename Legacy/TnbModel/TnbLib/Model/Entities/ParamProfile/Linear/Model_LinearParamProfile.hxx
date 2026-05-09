#pragma once
#ifndef _Model_LinearParamProfile_Header
#define _Model_LinearParamProfile_Header

#include <Model_ParamProfile.hxx>

namespace tnbLib
{

	class Model_LinearParamProfile
		: public Model_ParamProfile
	{

		/*Private Data*/

		std::pair<Standard_Real, Standard_Real> theX0_;
		std::pair<Standard_Real, Standard_Real> theX1_;

	public:

		// default constructor [12/20/2022 Payvand]

		Model_LinearParamProfile()
			: theX0_(std::make_pair(0.0, 0.0))
			, theX1_(std::make_pair(0.0, 0.0))
		{}


		// constructors [12/20/2022 Payvand]

		Model_LinearParamProfile
		(
			const std::pair<Standard_Real, Standard_Real>& theX0,
			const std::pair<Standard_Real, Standard_Real>& theX1
		)
			: theX0_(theX0)
			, theX1_(theX1)
		{}


		// Public functions and operators [12/20/2022 Payvand]

		const auto& X0() const
		{
			return theX0_;
		}

		const auto& X1() const
		{
			return theX1_;
		}

		Standard_Real Lower() const override
		{
			return theX0_.first;
		}

		Standard_Real Upper() const override
		{
			return theX1_.first;
		}

		Standard_Real Value(const Standard_Real x) const override;
	};
}

#endif // !_Model_LinearParamProfile_Header
