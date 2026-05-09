#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_NelderMead_Header
#define _Aft2d_AltrOptNodeSurface_NelderMead_Header

#include <Aft2d_AltrOptNodeSurface.hxx>

namespace tnbLib
{

	// Forward Declarations [5/8/2022 Amir]
	class NumAlg_NelderMeadInfo;

	class Aft2d_AltrOptNodeSurface_NelderMead
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::shared_ptr<NumAlg_NelderMeadInfo> theInfo_;

		// Private functions and operators [3/11/2023 Payvand]

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		// default constructor [5/8/2022 Amir]


		Aft2d_AltrOptNodeSurface_NelderMead()
		{}

		// constructors [5/8/2022 Amir]


		// public functions and operators [5/8/2022 Amir]

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

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_AltrOptNodeSurface_NelderMead);

#endif // !_Aft2d_AltrOptNodeSurface_NelderMead_Header
