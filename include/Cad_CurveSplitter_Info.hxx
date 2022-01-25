#pragma once
#ifndef _Cad_CurveSplitter_Info_Header
#define _Cad_CurveSplitter_Info_Header

#include <Standard_TypeDef.hxx>
#include <Cad_Module.hxx>
#include <Global_Serialization.hxx>

#include <memory>

namespace tnbLib
{

	// Forward Declarations [1/17/2022 Amir]
	class NumAlg_AdaptiveInteg_Info;
	class NumAlg_NewtonSolver_Info;
	class Mesh_CurveOptmPoint_Correction_Info;

	class Cad_CurveSplitter_Info
	{

		/*Private Data*/

		std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> theCorrInfo_;
		std::shared_ptr<NumAlg_NewtonSolver_Info> theNewtonInfo_;

		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theOverallLengthIntgInfo_;
		std::shared_ptr<NumAlg_AdaptiveInteg_Info> theIterIntgInfo_;

		Standard_Integer theMaxLevel_;

		Standard_Real theUnderRelaxation_;

		Standard_Boolean theIgnorNonConvergency_;


		// Private functions and operators [1/20/2022 Amir]

		TNB_SERIALIZATION(TnbCad_EXPORT);

	public:

		static TnbCad_EXPORT const Standard_Integer DEFAULT_MAX_LEVEL;
		static TnbCad_EXPORT const Standard_Real DEFAULT_UR;

		static TnbCad_EXPORT const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info> DEFAULT_CORR_INFO;

		static TnbCad_EXPORT const std::shared_ptr<NumAlg_NewtonSolver_Info> DEFAULT_NEWTON_INFO;

		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_OVERALL_LENGTH_INFO;
		static TnbCad_EXPORT const std::shared_ptr<NumAlg_AdaptiveInteg_Info> DEFAULT_ITER_INTEG_INFO;

		// default constructor [1/17/2022 Amir]

		Cad_CurveSplitter_Info()
			: theCorrInfo_(DEFAULT_CORR_INFO)
			, theNewtonInfo_(DEFAULT_NEWTON_INFO)
			, theOverallLengthIntgInfo_(DEFAULT_OVERALL_LENGTH_INFO)
			, theIterIntgInfo_(DEFAULT_ITER_INTEG_INFO)
			, theMaxLevel_(DEFAULT_MAX_LEVEL)
			, theUnderRelaxation_(DEFAULT_UR)
			, theIgnorNonConvergency_(Standard_True)
		{}

		// constructors [1/17/2022 Amir]


		// public functions and operators [1/17/2022 Amir]

		const auto& CorrInfo() const
		{
			return theCorrInfo_;
		}

		const auto& NewtonIterInfo() const
		{
			return theNewtonInfo_;
		}

		const auto& IterIntgInfo() const
		{
			return theIterIntgInfo_;
		}

		const auto& OverallLengthIntgInfo() const
		{
			return theOverallLengthIntgInfo_;
		}

		auto MaxLevel() const
		{
			return theMaxLevel_;
		}

		auto UnderRelaxation() const
		{
			return theUnderRelaxation_;
		}

		auto IgnoreNonConvergency() const
		{
			return theIgnorNonConvergency_;
		}

		void SetOverrideCorrInfo(const std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>& theInfo)
		{
			theCorrInfo_ = theInfo;
		}

		void SetOverrideCorrInfo(std::shared_ptr<Mesh_CurveOptmPoint_Correction_Info>&& theInfo)
		{
			theCorrInfo_ = std::move(theInfo);
		}

		void OverrideOverallLengthIntgInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theOverallLengthIntgInfo_ = theInfo;
		}

		void OverrideOverallLengthIntgInfo(std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo)
		{
			theOverallLengthIntgInfo_ = std::move(theInfo);
		}

		void OverrideNewtonSolverInfo(const std::shared_ptr<NumAlg_NewtonSolver_Info>& theInfo)
		{
			theNewtonInfo_ = theInfo;
		}

		void OverrideNewtonSolverInfo(std::shared_ptr<NumAlg_NewtonSolver_Info>&& theInfo)
		{
			theNewtonInfo_ = std::move(theInfo);
		}

		void OverrideInterIntgInfo(const std::shared_ptr<NumAlg_AdaptiveInteg_Info>& theInfo)
		{
			theIterIntgInfo_ = theInfo;
		}

		void OverrideInterIntgInfo(std::shared_ptr<NumAlg_AdaptiveInteg_Info>&& theInfo)
		{
			theIterIntgInfo_ = std::move(theInfo);
		}

		void SetMaxLevel(const Standard_Integer theLevel)
		{
			theMaxLevel_ = theLevel;
		}

		void SetUnderRelaxation(const Standard_Real theUr)
		{
			theUnderRelaxation_ = theUr;
		}

		void SetIngnoreNonConvergency(const Standard_Boolean theCond)
		{
			theIgnorNonConvergency_ = theCond;
		}
	};
}

#endif // !_Cad_CurveSplitter_Info_Header
