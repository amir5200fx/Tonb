#pragma once
#ifndef _NumAlg_NewtonSolver_Info_Header
#define _NumAlg_NewtonSolver_Info_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <NumAlg_Module.hxx>
#include <NumAlg_NewtonSolver_Condition.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class Function, class Derivation, bool RefInfo>
	class NumAlg_NewtonSolver;

	class NumAlg_NewtonSolver_Info
	{

		template<class Function, class Derivation, bool RefInfo>
		friend class NumAlg_NewtonSolver;

		/*Private Data*/

		Standard_Integer theMaxIterations_;
		Standard_Integer theIter_;

		Standard_Real theTolerance_;
		Standard_Real theUnderRelaxation_;

		Standard_Real theResidual_;
		Standard_Real theResult_;
		Standard_Real theSmall_;
		Standard_Real theZero_;

		Standard_Boolean IsConverged_;

		NumAlg_NewtonSolver_Condition theCondition_;


		//- private functions and operators


		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theMaxIterations_;
			ar & theIter_;

			ar & theTolerance_;
			ar & theUnderRelaxation_;

			ar & theResidual_;
			ar & theResult_;
			ar & theSmall_;
			ar & theZero_;

			ar & IsConverged_;

			ar & theCondition_;
		}

	protected:

		auto& ChangeNbIter()
		{
			return theIter_;
		}

		auto& ChangeResidual()
		{
			return theResidual_;
		}

		auto& ChangeResult()
		{
			return theResult_;
		}

		auto& Change_IsConverged()
		{
			return IsConverged_;
		}

		auto& ChangeCondition()
		{
			return theCondition_;
		}

		void Reset()
		{
			theIter_ = 0;
			theResidual_ = 0;
			theResult_ = 0;

			IsConverged_ = Standard_False;
		}

	public:

		static TnbNumAlg_EXPORT const Standard_Integer MAX_NB_ITERATIONS;

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_UNDER_RELAXATION;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_SMALL;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_ZERO;


		//- default constructor

		TnbNumAlg_EXPORT NumAlg_NewtonSolver_Info();


		//- constructors


		//- public functions and operators

		auto NbIterations() const
		{
			return theIter_;
		}

		auto Residual() const
		{
			return theResidual_;
		}

		auto Result() const
		{
			return theResult_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		auto Condition() const
		{
			return theCondition_;
		}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Small)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Zero)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, UnderRelaxation)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxIterations)
			

	};
}

#endif // !_NumAlg_NewtonSolver_Info_Header
