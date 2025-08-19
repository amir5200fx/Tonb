#pragma once
#ifndef _Cad2d_CurveLength_Adaptive_Header
#define _Cad2d_CurveLength_Adaptive_Header

#include <Cad2d_CurveLength.hxx>

namespace tnbLib
{

	namespace cad2dLib
	{

		// Forward Declarations [2/6/2022 Amir]
		class CurveLength_Adaptive_Info;

		class CurveLength_Adaptive
			: public Cad2d_CurveLength
		{

			/*Private Data*/

			std::shared_ptr<CurveLength_Adaptive_Info> theInfo_;

		public:

			// default constructor [2/6/2022 Amir]


			// constructors [2/6/2022 Amir]

			CurveLength_Adaptive
			(
				const std::shared_ptr<CurveLength_Adaptive_Info>& theInfo
			)
				: theInfo_(theInfo)
			{}

			CurveLength_Adaptive
			(
				std::shared_ptr<CurveLength_Adaptive_Info>&& theInfo
			)
				: theInfo_(std::move(theInfo))
			{}

			// override functions and operators [2/6/2022 Amir]

			TnbCad2d_EXPORT Standard_Real CalcLength(const std::shared_ptr<Pln_Curve>&) const override;
			TnbCad2d_EXPORT Standard_Real CalcLength(const std::shared_ptr<Pln_Curve>&, const Standard_Real theLower, const Standard_Real theUpper) const override;

			// public functions and operators [2/6/2022 Amir]

			const auto& CurveLengthInfo() const
			{
				return theInfo_;
			}
		};
	}
}

#endif // !_Cad2d_CurveLength_Adaptive_Header
