#pragma once
#ifndef _Cad_tModelMaker_OnePtsDistPairCrvCriterion_Header
#define _Cad_tModelMaker_OnePtsDistPairCrvCriterion_Header

#include <Cad_tModelMaker_SamplePtsDistPairCrvCriterion.hxx>

namespace tnbLib
{

	namespace cadLib
	{

		class tModelMaker_OnePtsDistPairCrvCriterion
			: public Cad_tModelMaker_SamplePtsDistPairCrvCriterion
		{

			/*Private Data*/

		public:

			// default constructor [1/16/2022 Amir]

			tModelMaker_OnePtsDistPairCrvCriterion()
			{}

			// constructors [1/16/2022 Amir]

			explicit tModelMaker_OnePtsDistPairCrvCriterion
			(
				const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo
			)
				: Cad_tModelMaker_SamplePtsDistPairCrvCriterion(theInfo)
			{}

			// override functions and operators [1/16/2022 Amir]

			Standard_Boolean ArePaired(const std::shared_ptr<TModel_Curve>& theCurve0, const std::shared_ptr<TModel_Curve>& theCurve1) const override;

			// public functions and operators [1/16/2022 Amir]
		};
	}
}

#endif // !_Cad_tModelMaker_OnePtsDistPairCrvCriterion_Header
