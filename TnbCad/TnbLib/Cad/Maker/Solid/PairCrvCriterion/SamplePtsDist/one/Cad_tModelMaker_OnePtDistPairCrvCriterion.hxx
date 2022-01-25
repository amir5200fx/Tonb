#pragma once
#ifndef _Cad_tModelMaker_OnePtDistPairCrvCriterion_Header
#define _Cad_tModelMaker_OnePtDistPairCrvCriterion_Header

#include <Cad_tModelMaker_SamplePtsDistPairCrvCriterion.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		class tModelMaker_OnePtDistPairCrvCriterion
			: public Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		{

			/*Private Data*/

		public:

			// default constructor [1/16/2022 Amir]

			tModelMaker_OnePtDistPairCrvCriterion()
			{}

			// constructors [1/16/2022 Amir]

			tModelMaker_OnePtDistPairCrvCriterion
			(
				const std::shared_ptr<Cad_CurveLength_Info>& theLengthInfo,
				const std::shared_ptr<Cad_CurveSplitter_Info>& theSplitterInfo
			)
				: Cad_tModelMaker_SamplePtsDistPairCrvCriterion(theLengthInfo, theSplitterInfo)
			{}

			// override functions and operators [1/16/2022 Amir]

			TnbCad_EXPORT Standard_Boolean 
				ArePaired
				(
					const std::shared_ptr<TModel_Curve>& theCurve0, 
					const std::shared_ptr<TModel_Curve>& theCurve1
				) const override;

			// public functions and operators [1/16/2022 Amir]
		};
	}
}

BOOST_CLASS_EXPORT_KEY(tnbLib::cadLib::tModelMaker_OnePtDistPairCrvCriterion);

#endif // !_Cad_tModelMaker_OnePtDistPairCrvCriterion_Header
