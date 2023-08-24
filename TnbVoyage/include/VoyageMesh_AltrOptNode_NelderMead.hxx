#pragma once
#ifndef _VoyageMesh_AltrOptNode_NelderMead_Header
#define _VoyageMesh_AltrOptNode_NelderMead_Header

#include <VoyageMesh_AltrOptNode.hxx>

namespace tnbLib
{

	// Forward Declarations [8/23/2023 aamir]
	class NumAlg_NelderMeadInfo;

	class VoyageMesh_AltrOptNode_NelderMead
		: public VoyageMesh_AltrOptNode
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_NelderMeadInfo> theInfo_;

	public:

		// default constructor [8/23/2023 aamir]

		VoyageMesh_AltrOptNode_NelderMead()
		{}

		// constructors [8/23/2023 aamir]


		// Public functions and operators [8/23/2023 aamir]

		const auto& AlgInfo() const
		{
			return theInfo_;
		}

		TnbMesh_EXPORT void Perform() override;

		void SetInfo(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo)
		{
			theInfo_ = theInfo;
		}

	};
}

#endif // !_VoyageMesh_AltrOptNode_NelderMead_Header
