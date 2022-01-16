#pragma once
#ifndef _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
#define _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header

#include <Cad_tModelMaker_PairCrvCriterion.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/16/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;

	class Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		: public Cad_tModelMaker_PairCrvCriterion
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theInfo_;

	protected:

		// default constructor [1/16/2022 Amir]

		TnbCad_EXPORT Cad_tModelMaker_SamplePtsDistPairCrvCriterion();

		// constructors [1/16/2022 Amir]

		explicit Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		(
			const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
		)
			: theInfo_(theInfo)
		{}

	public:

		// public functions and operators [1/16/2022 Amir]

		const auto& IntegInfo() const
		{
			return theInfo_;
		}

		void OverrideIntegInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion);

#endif // !_Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
