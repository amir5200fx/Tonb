#pragma once
#ifndef _NumAlg_Secant_Header
#define _NumAlg_Secant_Header

#include <Global_Bound.hxx>
#include <Global_Done.hxx>
#include <NumAlg_Secant_Info.hxx>
#include <NumAlg_Secant_Condition.hxx>
#include <NumAlg_System.hxx>

namespace tnbLib
{

	class NumAlg_Secant_Bound
		: public Global_Bound<Standard_Real>
	{

		/*Private Data*/

	protected:

		NumAlg_Secant_Bound
		(
			const Standard_Real theLower = 0,
			const Standard_Real theUpper = 0
		)
			: Global_Bound<Standard_Real>(theLower, theUpper)
		{}

	};

	struct NumAlg_Secant_Value
	{
		virtual Standard_Real Value(const Standard_Real) const
		{
			Iter::ChackFun("Standard_Real Value(const Standard_Real) const");
			return 0;
		}
	};

	template<bool BoundCheck = false>
	struct NumAlg_Secant_Function
		: public NumAlg_Secant_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound<false>(x, 0, 0);
		}
	};

	template<>
	struct NumAlg_Secant_Function<true>
		: public NumAlg_Secant_Bound
		, public NumAlg_Secant_Value
	{
		void CheckBound(Standard_Real& x) const
		{
			Iter::CheckBound(x, Lower(), Upper());
		}
	};

	template<class Function>
	class NumAlg_Secant_Alg
		: public Function
		, public Global_Done
	{

		typedef Function fun;

		/*Private Data*/

		virtual Standard_Integer& ChangeNbIter() = 0;

		virtual NumAlg_Secant_Condition Condition() const = 0;

		virtual NumAlg_Secant_Condition& ChangeCondition() = 0;

		virtual Standard_Real& ChangeResidual() = 0;

		virtual Standard_Real& ChangeP0() = 0;

		virtual Standard_Real& ChangeP1() = 0;

		virtual Standard_Integer MaxNbIterations() const = 0;

		virtual Standard_Real UnderRelaxation() const = 0;

		virtual Standard_Real Tolerance() const = 0;

		virtual Standard_Real Zero() const = 0;

		virtual Standard_Real Small() const = 0;

	protected:

		NumAlg_Secant_Alg
		(
			const fun& theFun
		)
			: fun(theFun)
		{}

	public:

		void Perform(const Standard_Real theP0, const Standard_Real theP1)
		{
			auto p0 = theP0;
			auto p1 = theP1;

			fun::CheckBound(p0);
			auto y0 = fun::Value(p0);

			fun::CheckBound(p1);
			auto y1 = fun::Value(p1);

			Standard_Real df, dp, rel_err, y2;

			ChangeNbIter() = 0;
			ChangeResidual() = (Standard_Real)0.;
			ChangeP0() = p0;
			ChangeP1() = p1;
			ChangeCondition() = NumAlg_Secant_Condition::LEVEL_EXCEEDED;

			forThose(Iter, 1, MaxNbIterations())
			{
				ChangeNbIter()++;

				df = (y1 - y0) / (p1 - p0);
				if (ABS(df) <= Zero())
				{
					dp = (Standard_Real)0.;
					ChangeCondition() = NumAlg_Secant_Condition::ZERODIVIDE;
				}
				else
				{
					dp = y1 / df;
				}

				auto p2 = p1 - dp;

				fun::CheckBound(p2);
				y2 = fun::Value(p2);

				rel_err = (Standard_Real)2.0 * ABS(dp) / (ABS(p1) + Small());

				if (rel_err < Tolerance() OR ABS(y1) < Zero())
					if (Condition() NOT_EQUAL NumAlg_Secant_Condition::ZERODIVIDE)
						ChangeCondition() = NumAlg_Secant_Condition::CONVERGED;

				p0 = p1;
				p1 = p2;
				y0 = y1;
				y1 = y2;

				if (Condition() NOT_EQUAL NumAlg_Secant_Condition::LEVEL_EXCEEDED)
					break;
			}

			ChangeP0() = p0;
			ChangeP1() = p1;
			ChangeResidual() = rel_err;
			Change_IsDone() = Standard_True;
		}
	};

	template<class Function, bool RefInfo = true>
	class NumAlg_Secant
		: public NumAlg_Secant_Alg<Function>
	{

		typedef Function fun;

		/*Private Data*/

		NumAlg_Secant_Info& theInfo_;


		Standard_Integer& ChangeNbIter() override
		{
			return theInfo_.ChangeNbIter();
		}

		NumAlg_Secant_Condition& ChangeCondition() override
		{
			return theInfo_.ChangeCondition();
		}

		Standard_Real& ChangeResidual() override
		{
			return theInfo_.ChangeResidual();
		}

		Standard_Real& ChangeP0() override
		{
			return theInfo_.ChangeX0();
		}

		Standard_Real& ChangeP1() override
		{
			return theInfo_.ChangeX1();
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

		NumAlg_Secant_Condition Condition() const override
		{
			return theInfo_.Condition();
		}

	public:

		
		NumAlg_Secant
		(
			const fun& theFun,
			NumAlg_Secant_Info& theInfo
		)
			: NumAlg_Secant_Alg<fun>(theFun)
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


	template<class Function>
	class NumAlg_Secant<Function, false>
		: public NumAlg_Secant_Alg<Function>
		, public NumAlg_Secant_Info
	{
		typedef Function fun;
		typedef NumAlg_Secant_Info info;

		/*Private Data*/

		Standard_Integer& ChangeNbIter() override
		{
			return info::ChangeNbIter();
		}

		NumAlg_Secant_Condition& ChangeCondition() override
		{
			return info::ChangeCondition();
		}

		Standard_Real& ChangeResidual() override
		{
			return info::ChangeResidual();
		}

		Standard_Real& ChangeP0() override
		{
			return info::ChangeX0();
		}

		Standard_Real& ChangeP1() override
		{
			return info::ChangeX1();
		}

		Standard_Integer MaxNbIterations() const override
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

		NumAlg_Secant_Condition Condition() const override
		{
			return info::Condition();
		}

	public:

		NumAlg_Secant
		(
			const Function& theFunction
		)
			: NumAlg_Secant_Alg<Function>(theFunction)
		{}
	};
}

#endif // !_NumAlg_Secant_Header
