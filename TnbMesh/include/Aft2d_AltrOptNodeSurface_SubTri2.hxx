#pragma once
#ifndef _Aft2d_AltrOptNodeSurface_SubTri2_Header
#define _Aft2d_AltrOptNodeSurface_SubTri2_Header

#include <Aft2d_AltrOptNodeSurface.hxx>
#include <Pnt2d.hxx>

namespace tnbLib
{

	// Forward Declarations [6/11/2022 Amir]
	class Aft_SizeCorr_IterativeInfo;
	class NumAlg_BisectionSolver_Info;

	class Aft2d_AltrOptNodeSurface_SubTri2
		: public Aft2d_AltrOptNodeSurface
	{

		/*Private Data*/

		std::shared_ptr<Aft_SizeCorr_IterativeInfo> theSizeCorrInfo_;
		std::shared_ptr<NumAlg_BisectionSolver_Info> theBisectInfo_;

		Standard_Integer theMaxLev_;
		Standard_Real theTolerance_;

		// private functions and operators [6/11/2022 Amir]

		TnbMesh_EXPORT std::tuple<Standard_Real, Standard_Real, Standard_Boolean> Iter
		(
			const Pnt2d& theCentre,
			const Pnt2d& theP0, 
			const Pnt2d& theP1,
			const Standard_Real theH
		);

	public:

		static TnbMesh_EXPORT const Standard_Integer DEFAULT_MAX_LEV;
		static TnbMesh_EXPORT const Standard_Real DEFAULT_TOLERANCE;

		// default constructor [6/11/2022 Amir]

		Aft2d_AltrOptNodeSurface_SubTri2()
			: theMaxLev_(DEFAULT_MAX_LEV)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}


		// constructors [6/11/2022 Amir]

		Aft2d_AltrOptNodeSurface_SubTri2
		(
			const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theSizeCorrInfo,
			const std::shared_ptr<NumAlg_BisectionSolver_Info>& theBisectInfo
		)
			: theSizeCorrInfo_(theSizeCorrInfo)
			, theBisectInfo_(theBisectInfo)
			, theMaxLev_(DEFAULT_MAX_LEV)
			, theTolerance_(DEFAULT_TOLERANCE)
		{}

		// public functions and operators [6/11/2022 Amir]

		const auto& SizeCorrInfo() const
		{
			return theSizeCorrInfo_;
		}

		const auto& BisectInfo() const
		{
			return theBisectInfo_;
		}

		auto MaxLevel() const
		{
			return theMaxLev_;
		}

		auto Tolerance() const
		{
			return theTolerance_;
		}

		TnbMesh_EXPORT void Perform() override;

		void SetSizeCorrInfo(const std::shared_ptr<Aft_SizeCorr_IterativeInfo>& theInfo)
		{
			theSizeCorrInfo_ = theInfo;
		}

		void SetBisectInfo(const std::shared_ptr<NumAlg_BisectionSolver_Info>& theInfo)
		{
			theBisectInfo_ = theInfo;
		}

		void SetMaxLev(const Standard_Integer theMax)
		{
			theMaxLev_ = theMax;
		}

		void SetTolerance(const Standard_Real theTol)
		{
			theTolerance_ = theTol;
		}
	};
}

#endif // !_Aft2d_AltrOptNodeSurface_SubTri2_Header
