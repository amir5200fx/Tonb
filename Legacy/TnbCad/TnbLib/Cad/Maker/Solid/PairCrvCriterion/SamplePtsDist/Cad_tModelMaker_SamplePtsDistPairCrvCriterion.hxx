#pragma once
#ifndef _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
#define _Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header

#include <Cad_tModelMaker_PairCrvCriterion.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/16/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;
	class Cad_CurveLength_Info;
	class Cad_CurveSplitter_Info;

	class Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		: public Cad_tModelMaker_PairCrvCriterion
	{

		/*Private Data*/

		std::shared_ptr<Cad_CurveLength_Info> theLengthInfo_;
		std::shared_ptr<Cad_CurveSplitter_Info> theSplitterInfo_;


		// private functions and operators [1/21/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	protected:

		// default constructor [1/16/2022 Amir]

		TnbCad_EXPORT Cad_tModelMaker_SamplePtsDistPairCrvCriterion();

		// constructors [1/16/2022 Amir]

		Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		(
			const std::shared_ptr<Cad_CurveLength_Info>& theLengthInfo,
			const std::shared_ptr<Cad_CurveSplitter_Info>& theSplitterInfo
		)
			: theLengthInfo_(theLengthInfo)
			, theSplitterInfo_(theSplitterInfo)
		{}

	public:

		// public functions and operators [1/16/2022 Amir]

		const auto& CurveLengthInfo() const
		{
			return theLengthInfo_;
		}

		const auto& CurveSplitterInfo() const
		{
			return theSplitterInfo_;
		}

		void OverrideCurveLengthInfo(const std::shared_ptr<Cad_CurveLength_Info>& theInfo)
		{
			theLengthInfo_ = theInfo;
		}

		void OverrideCurveLengthInfo(std::shared_ptr<Cad_CurveLength_Info>&& theInfo)
		{
			theLengthInfo_ = std::move(theInfo);
		}

		void OverrideCurveSplitterInfo(const std::shared_ptr<Cad_CurveSplitter_Info>& theInfo)
		{
			theSplitterInfo_ = theInfo;
		}

		void OverrideCurveSplitterInfo(std::shared_ptr<Cad_CurveSplitter_Info>&& theInfo)
		{
			theSplitterInfo_ = std::move(theInfo);
		}

	};
}

BOOST_SERIALIZATION_ASSUME_ABSTRACT(tnbLib::Cad_tModelMaker_SamplePtsDistPairCrvCriterion);

#endif // !_Cad_tModelMaker_SamplePtsDistPairCrvCriterion_Header
