#pragma once
#ifndef _VoyageMesh_AltrOptNode_SubTri_Header
#define _VoyageMesh_AltrOptNode_SubTri_Header

#include <VoyageMesh_AltrOptNode.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [9/2/2023 Payvand]
	class Aft_SizeCorr_IterativeInfo;
	class NumAlg_NelderMeadInfo;

	class VoyageMesh_AltrOptNode_SubTri
		: public VoyageMesh_AltrOptNode
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theSizeCorrInfo_;
		std::shared_ptr<NumAlg_NelderMeadInfo> theNelderInfo_;

		Standard_Integer theMaxLev_;


		// Private functions and operators [9/2/2023 Payvand]

		TnbVoyage_EXPORT Standard_Boolean
			Iter
			(
				const Standard_Integer theLev,
				const Pnt2d&, const Pnt2d& theP0,
				const Pnt2d& theP1,
				const Standard_Real h
			);

	public:

		static TnbVoyage_EXPORT const Standard_Integer DEFAULT_MAX_LEV;

		// default constructor [9/2/2023 Payvand]

		VoyageMesh_AltrOptNode_SubTri()
			: theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// constructors [9/2/2023 Payvand]

		VoyageMesh_AltrOptNode_SubTri
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theSizeCorrInfo,
			const std::shared_ptr<NumAlg_NelderMeadInfo>& theNelderInfo
		)
			: theSizeCorrInfo_(theSizeCorrInfo)
			, theNelderInfo_(theNelderInfo)
			, theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// Public functions and operators [9/2/2023 Payvand]

		const auto& SizeCorrInfo() const
		{
			return theSizeCorrInfo_;
		}

		const auto& NelderMeadInfo() const
		{
			return theNelderInfo_;
		}

		auto MaxLevel() const
		{
			return theMaxLev_;
		}

		TnbVoyage_EXPORT void Perform() override;

		void SetSizeCorrInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo)
		{
			theSizeCorrInfo_ = theInfo;
		}

		void SetNealderMeadInfo(const std::shared_ptr<NumAlg_NelderMeadInfo>& theInfo)
		{
			theNelderInfo_ = theInfo;
		}

		void SetMaxLev(const Standard_Integer theMax)
		{
			theMaxLev_ = theMax;
		}

	};
}

#endif // !_VoyageMesh_AltrOptNode_SubTri_Header
