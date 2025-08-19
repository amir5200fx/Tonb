#pragma once
#ifndef _NumAlg_BisectionSolver_Info_Header
#define _NumAlg_BisectionSolver_Info_Header

#include <Global_AccessMethod.hxx>
#include <Global_Serialization.hxx>
#include <NumAlg_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	template<class Function, bool RefInfo>
	class NumAlg_BisectionSolver;

	class NumAlg_BisectionSolver_Info
	{

		template<class Function, bool RefInfo>
		friend class NumAlg_BisectionSolver;

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


		//- private functions and operators

		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive& ar, const unsigned int /*file_version*/)
		{
			ar & theMaxIterations_;
			ar & theIter_;

			ar & theDelta_;
			ar & theTolerance_;

			ar & theResidual_;
			ar & theX0_;
			ar & theX1_;
			ar & theResult_;

			ar & IsConverged_;
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

		static TnbNumAlg_EXPORT const Standard_Integer MAX_NB_ITERATIONS;

		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_TOLERANCE;
		static TnbNumAlg_EXPORT const Standard_Real DEFAULT_DELTA;


		//- default constructor

		TnbNumAlg_EXPORT NumAlg_BisectionSolver_Info();


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

#endif // !_NumAlg_BisectionSolver_Info_Header
