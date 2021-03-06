#pragma once
#ifndef _NumAlg_NewtonSolver_Header
#define _NumAlg_NewtonSolver_Header

#include <Global_Bound.hxx>
#include <Global_Done.hxx>
#include <NumAlg_NewtonSolver_Info.hxx>
#include <NumAlg_NewtonSolver_Condition.hxx>
#include <NumAlg_System.hxx>

namespace tnbLib
{

	class NumAlg_NewtonSolver_Bound
		: public Global_Bound<Standard_Real>
	{

		/*Private Data*/

	protected:

		NumAlg_NewtonSolver_Bound
		(
			const Standard_Real theLower = 0,
			const Standard_Real theUpper = 0
		)
			: Global_Bound<Standard_Real>(theLower, theUpper)
		{}

	};

	struct NumAlg_NewtonSolver_Value
	{
		virtual Standard_Real Value(const Standard_Real) const
		{
			Iter::ChackFun("Standard_Real Value(const Standard_Real) const");
			return 0;
		}
	};

	template<bool BoundCheck = false>
	struct NumAlg_NewtonSolver_Function
		: public NumAlg_NewtonSolver_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound<false>(x, 0, 0);
		}
	};

	template<>
	struct NumAlg_NewtonSolver_Function<true>
		: public NumAlg_NewtonSolver_Bound
		, public NumAlg_NewtonSolver_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound(x, Lower(), Upper());
		}
	};

	template<bool BoundCheck = false>
	struct NumAlg_NewtonSolver_Derivation
		: public NumAlg_NewtonSolver_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound<false>(x, 0, 0);
		}
	};

	template<>
	struct NumAlg_NewtonSolver_Derivation<true>
		: public NumAlg_NewtonSolver_Bound
		, public NumAlg_NewtonSolver_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound(x, Lower(), Upper());
		}
	};

	template<class Function, class Derivation>
	class NumAlg_NewtonSolver_Alg
		: public Function
		, public Derivation
		, public Global_Done
	{

		typedef Function fun;
		typedef Derivation der;

		/*Private Data*/


		virtual Standard_Integer& ChangeNbIter() = 0;

		virtual NumAlg_NewtonSolver_Condition Condition() const = 0;

		virtual NumAlg_NewtonSolver_Condition& ChangeCondition() = 0;

		virtual Standard_Real& ChangeResidual() = 0;

		virtual Standard_Real& ChangeResult() = 0;

		virtual Standard_Integer MaxNbIterations() const = 0;

		virtual Standard_Real UnderRelaxation() const = 0;

		virtual Standard_Real Tolerance() const = 0;

		virtual Standard_Real Zero() const = 0;

		virtual Standard_Real Small() const = 0;

	protected:

		NumAlg_NewtonSolver_Alg
		(
			const Function& theFunction,
			const Derivation& theDerivation
		)
			: fun(theFunction)
			, der(theDerivation)
		{}

	public:

		void Perform(const Standard_Real guess)
		{
			auto u = guess;

			fun::CheckBound(u);
			auto y0 = fun::Value(u);

			Standard_Real df, dp, p1, y1, rel_err;

			ChangeNbIter() = 0;
			ChangeResidual() = (Standard_Real)0.;
			ChangeResult() = (Standard_Real)0.;
			ChangeCondition() = NumAlg_NewtonSolver_Condition::LEVEL_EXCEEDED;

			forThose(Iter, 1, MaxNbIterations())
			{
				ChangeNbIter()++;

				der::CheckBound(u);
				df = der::Value(u);

				if (ABS(df) <= Zero())
				{
					dp = (Standard_Real)0.;
					ChangeCondition() = NumAlg_NewtonSolver_Condition::ZERODIVIDE;
				}
				else
					dp = y0 / df;

				p1 = u - UnderRelaxation()*dp;

				fun::CheckBound(p1);
				y1 = fun::Value(p1);

				rel_err = (Standard_Real)2.0 * ABS(dp) / (ABS(p1) + Small());

				if (rel_err < Tolerance() OR ABS(y1) < Zero())
					if (Condition() NOT_EQUAL NumAlg_NewtonSolver_Condition::ZERODIVIDE)
						ChangeCondition() = NumAlg_NewtonSolver_Condition::CONVERGED;

				u = p1;
				y0 = y1;

				if (Condition() NOT_EQUAL NumAlg_NewtonSolver_Condition::LEVEL_EXCEEDED)
					break;
			}

			ChangeResult() = u;
			ChangeResidual() = rel_err;
			Change_IsDone() = Standard_True;
		}
	};

	template<class Function, class Derivation, bool RefInfo = true>
	class NumAlg_NewtonSolver
		: public NumAlg_NewtonSolver_Alg<Function, Derivation>
	{

		typedef Function fun;
		typedef Derivation der;

		/*Private Data*/

		NumAlg_NewtonSolver_Info& theInfo_;

		Standard_Integer& ChangeNbIter() override
		{
			return theInfo_.ChangeNbIter();
		}

		NumAlg_NewtonSolver_Condition Condition() const override
		{
			return theInfo_.Condition();
		}

		NumAlg_NewtonSolver_Condition& ChangeCondition() override
		{
			return theInfo_.ChangeCondition();
		}

		Standard_Real& ChangeResidual() override
		{
			return theInfo_.ChangeResidual();
		}

		Standard_Real& ChangeResult() override
		{
			return theInfo_.ChangeResult();
		}

		Standard_Integer MaxNbIterations() const override
		{
			return theInfo_.MaxIterations();
		}

		Standard_Real UnderRelaxation() const override
		{
			return theInfo_.UnderRelaxation();
		}

		Standard_Real Tolerance() const override
		{
			return theInfo_.Tolerance();
		}

		Standard_Real Zero() const override
		{
			return theInfo_.Zero();
		}

		Standard_Real Small() const override
		{
			return theInfo_.Small();
		}

	public:

		NumAlg_NewtonSolver
		(
			const Function& theFunction,
			const Derivation& theDerivation,
			NumAlg_NewtonSolver_Info& theInfo
		)
			: NumAlg_NewtonSolver_Alg<Function, Derivation>(theFunction, theDerivation)
			, theInfo_(theInfo)
		{
			theInfo_.Reset();
		}

		const auto& Info() const
		{
			return theInfo_;
		}

		auto& Info()
		{
			return theInfo_;
		}
	};

	template<class Function, class Derivation>
	class NumAlg_NewtonSolver<Function, Derivation, false>
		: public NumAlg_NewtonSolver_Alg<Function, Derivation>
		, public NumAlg_NewtonSolver_Info
	{

		typedef Function fun;
		typedef Derivation der;
		typedef NumAlg_NewtonSolver_Info info;

		/*Private Data*/

		Standard_Integer& ChangeNbIter() override
		{
			return info::ChangeNbIter();
		}

		NumAlg_NewtonSolver_Condition Condition() const override
		{
			return info::Condition();
		}

		NumAlg_NewtonSolver_Condition& ChangeCondition() override
		{
			return info::ChangeCondition();
		}

		Standard_Real& ChangeResidual() override
		{
			return info::ChangeResidual();
		}

		Standard_Real& ChangeResult() override
		{
			return info::ChangeResult();
		}

		Standard_Integer MaxNbIterations() const
		{
			return info::MaxIterations();
		}

		Standard_Real UnderRelaxation() const override
		{
			return info::UnderRelaxation();
		}

		Standard_Real Tolerance() const override
		{
			return info::Tolerance();
		}

		Standard_Real Zero() const override
		{
			return info::Zero();
		}

		Standard_Real Small() const override
		{
			return info::Small();
		}

	public:

		NumAlg_NewtonSolver
		(
			const Function& theFunction,
			const Derivation& theDerivation
		)
			: NumAlg_NewtonSolver_Alg<Function, Derivation>
			(
				theFunction,
				theDerivation
				)
		{}

		/*NumAlg_NewtonSolver
		(
			const Function& theFunction,
			const Derivation& theDerivation,
			const Numeric_NewtonSolverInfo& theInfo
		)
			: Numeric_NewtonSolver_Alg<Function, Derivation>(theFunction, theDerivation)
			, info(theInfo)
		{}*/


	};
}

#endif // !_NumAlg_NewtonSolver_Header
