#pragma once
#ifndef _VoyageMesh_IterOptNode_Calculator_Header
#define _VoyageMesh_IterOptNode_Calculator_Header

#include <VoyageMesh_OptNode_Calculator.hxx>

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
	class Aft_SizeCorr_IterativeInfo;

	class VoyageMesh_IterOptNode_Calculator
		: public VoyageMesh_OptNode_Calculator
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theInfo_;


	public:

		// default constructor [8/23/2023 aamir]


		// constructors [8/23/2023 aamir]

		explicit VoyageMesh_IterOptNode_Calculator
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo
		)
			: theInfo_(theInfo)
		{}


		// override functions and operators [3/7/2022 Amir]

		TnbMesh_EXPORT void Perform() override;

		// public functions and operators [3/7/2022 Amir]

		const auto& IterInfo() const
		{
			return theInfo_;
		}

	};

}

#endif // !_VoyageMesh_IterOptNode_Calculator_Header
