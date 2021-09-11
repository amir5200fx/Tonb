#pragma once
#ifndef _NumAlg_Secant_Info_Header
#define _NumAlg_Secant_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>
#include <NumAlg_Secant_Condition.hxx>
#include <NumAlg_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class Function>
	class NumAlg_Secant_Alg;

	template<class Function, bool RefInfo>
	class NumAlg_Secant;

	class NumAlg_Secant_Info
	{

		template<class Function>
		friend class NumAlg_Secant_Alg;

		template<class Function, bool RefInfo>
		friend class NumAlg_Secant;

		/*Private Data*/

		Standard_Integer theMaxIterations_;
		Standard_Integer theIter_;

		Standard_Real theTolerance_;
		Standard_Real theUnderRelaxation_;

		Standard_Real theResidual_;
		Standard_Real theSmall_;
		Standard_Real theZero_;
		Standard_Real theX0_;
		Standard_Real theX1_;

		Standard_Boolean IsConverged_;

		NumAlg_Secant_Condition theCondition_;

	protected:

		auto& ChangeNbIter()
		{
			return theIter_;
		}

		auto& ChangeResidual()
		{
			return theResidual_;
		}

		auto& ChangeX0()
		{
			return theX0_;
		}

		auto& ChangeX1()
		{
			return theX1_;
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
			theX0_ = 0;
			theX1_ = 0;

			IsConverged_ = Standard_False;
		}

	public:

		static TnbNumAlg_EXPORT const Standard_Integer MAX_NB_ITERATIONS;

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_UNDER_RELAXATION;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_SMALL;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_ZERO;

		TnbNumAlg_EXPORT NumAlg_Secant_Info();

		auto NbIterations() const
		{
			return theIter_;
		}

		auto Residual() const
		{
			return theResidual_;
		}

		auto X0() const
		{
			return theX0_;
		}

		auto X1() const
		{
			return theX1_;
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

#endif // !_NumAlg_Secant_Info_Header
