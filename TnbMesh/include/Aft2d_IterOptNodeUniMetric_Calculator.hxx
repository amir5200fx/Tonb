#pragma once
#ifndef _Aft2d_IterOptNodeUniMetric_Calculator_Header
#define _Aft2d_IterOptNodeUniMetric_Calculator_Header

#include <Aft2d_OptNodeUniMetric_Calculator.hxx>

namespace tnbLib
{

	// Forward Declarations [3/6/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;

	class Aft2d_IterOptNodeUniMetric_Calculator
		: public Aft2d_OptNodeUniMetric_Calculator
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theInfo_;

		// private functions and operators [3/6/2022 Amir]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	protected:

		// default constructor [3/6/2022 Amir]

		Aft2d_IterOptNodeUniMetric_Calculator()
		{}

	public:


		// constructors [3/6/2022 Amir]

		explicit Aft2d_IterOptNodeUniMetric_Calculator
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo
		)
			: theInfo_(theInfo)
		{}

		// override functions and operators [3/6/2022 Amir]

		TnbMesh_EXPORT void Perform() override;


		// public functions and operators [3/6/2022 Amir]

		const auto& IterInfo() const
		{
			return theInfo_;
		}

	};
}

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_IterOptNodeUniMetric_Calculator);

#endif // !_Aft2d_IterOptNodeUniMetric_Calculator_Header
