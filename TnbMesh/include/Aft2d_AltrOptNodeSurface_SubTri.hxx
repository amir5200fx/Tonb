#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_SubTri_Header
#define _Aft2d_AltrOptNodeSurface_SubTri_Header

#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [5/25/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;
	class NumAlg_NelderMeadInfo;

	class Aft2d_AltrOptNodeSurface_SubTri
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theSizeCorrInfo_;
		std::shared_ptr<NumAlg_NelderMeadInfo> theNelderInfo_;

		Standard_Integer theMaxLev_;

		// private functions and operators [5/25/2022 Amir]

		TnbMesh_EXPORT Standard_Boolean 
			Iter
			(
				const Standard_Integer theLev, 
				const Pnt2d&, const Pnt2d& theP0, 
				const Pnt2d& theP1,
				const Standard_Real h
			);

		TNB_SERIALIZATION(TnbMesh_EXPORT);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_LEV;

		// default constructor [5/25/2022 Amir]

		Aft2d_AltrOptNodeSurface_SubTri()
			: theMaxLev_(DEFAULT_MAX_LEV)
		{}


		// constructors [5/25/2022 Amir]

		Aft2d_AltrOptNodeSurface_SubTri
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theSizeCorrInfo,
			const std::shared_ptr<NumAlg_NelderMeadInfo>& theNelderInfo
		)
			: theSizeCorrInfo_(theSizeCorrInfo)
			, theNelderInfo_(theNelderInfo)
			, theMaxLev_(DEFAULT_MAX_LEV)
		{}

		// public functions and operators [5/25/2022 Amir]

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

		TnbMesh_EXPORT void Perform() override;

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

BOOST_CLASS_EXPORT_KEY(tnbLib::Aft2d_AltrOptNodeSurface_SubTri);

#endif // !_Aft2d_AltrOptNodeSurface_SubTri_Header
