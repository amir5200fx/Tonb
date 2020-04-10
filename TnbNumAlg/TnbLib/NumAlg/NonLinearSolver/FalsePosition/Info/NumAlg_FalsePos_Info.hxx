#pragma once
#ifndef _NumAlg_FalsePos_Info_Header
#define _NumAlg_FalsePos_Info_Header

#include <Standard_TypeDef.hxx>
#include <Global_AccessMethod.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class Function, bool RefInfo>
	class NumAlg_FalsePos;

	class NumAlg_FalsePos_Info
	{

		template<class Function, bool RefInfo>
		friend class NumAlg_FalsePos;

		/*Private Data*/

		Standard_Integer theMaxIterations_;
		Standard_Integer theIter_;

		Standard_Real theDelta_;
		Standard_Real theTolerance_;

		Standard_Real theResidual_;
		Standard_Real theX0_;
		Standard_Real theX1_;
		Standard_Real theResult_;

		Standard_Boolean IsConverged_;

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

		auto& ChangeResult()
		{
			return theResult_;
		}

		auto& Change_IsConverged()
		{
			return IsConverged_;
		}

		void Reset()
		{
			theIter_ = 0;
			theResidual_ = 0;
			theX0_ = 0;
			theX1_ = 0;
			theResult_ = 0;

			IsConverged_ = Standard_False;
		}

	public:

		static const Standard_Integer MAX_NB_ITERATIONS;

		static const Standard_Real DEFAULT_TOLERANCE;
		static const Standard_Real DEFAULT_DELTA;

		NumAlg_FalsePos_Info();

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

		auto Result() const
		{
			return theResult_;
		}

		auto IsConverged() const
		{
			return IsConverged_;
		}

		//- Macros

		GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Tolerance)
			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Real, Delta)

			GLOBAL_ACCESS_PRIM_SINGLE(Standard_Integer, MaxIterations)
	};
}

#endif // !_NumAlg_FalsePos_Info_Header
