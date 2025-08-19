#pragma once
#ifndef _Model_WeightNet_Header
#define _Model_WeightNet_Header

#include <Standard_TypeDef.hxx>

#include <vector>

namespace tnbLib
{

	class Model_WeightNet
	{

		/*Private Data*/

		std::vector<std::vector<Standard_Real>> theWeights_;

	public:

		// default constructor [12/20/2022 Payvand]

		Model_WeightNet()
		{}


		// constructors [12/20/2022 Payvand]


		// Public functions and operators [12/20/2022 Payvand]

		const auto& Weights() const
		{
			return theWeights_;
		}

		auto& WeightsRef()
		{
			return theWeights_;
		}

		void SetWeights(const std::vector<std::vector<Standard_Real>>& theWeights)
		{
			theWeights_ = theWeights;
		}

		void SetWeights(std::vector<std::vector<Standard_Real>>&& theWeights)
		{
			theWeights_ = std::move(theWeights);
		}
	};
}

#endif // !_Model_WeightNet_Header
