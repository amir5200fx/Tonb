#pragma once
#ifndef _NumAlg_BisectionSolver_Header
#define _NumAlg_BisectionSolver_Header

#include <Global_Bound.hxx>
#include <Global_Done.hxx>
#include <NumAlg_BisectionSolver_Info.hxx>
#include <NumAlg_System.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include <gp.hxx>

namespace tnbLib
{

	struct NumAlg_Bisection_Function
	{
		virtual Standard_Real Value(const Standard_Real) const
		{
			Iter::ChackFun("Standard_Real Value(const Standard_Real) const");
			return 0;
		}
	};

	template<class Function>
	class NumAlg_Bisection_Alg
		: public Function
		, public Global_Done
	{
		typedef Function fun;

		/*Private Data*/

		virtual Standard_Integer& ChangeNbIter() = 0;

		virtual Standard_Real& ChangeResidual() = 0;

		virtual Standard_Real& ChangeResult() = 0;

		virtual Standard_Real& ChangeA() = 0;

		virtual Standard_Real& ChangeB() = 0;

		virtual Standard_Integer MaxNbIterations() const = 0;

		virtual Standard_Real Tolerance() const = 0;

		virtual Standard_Real Delta() const = 0;

		virtual Standard_Boolean& ChangeConverge() = 0;

		static Standard_Boolean AreSameSign(const Standard_Real x0, const Standard_Real x1)
		{
			return x0 * x1 > 0;
		}

	protected:

		//- default constructor

		NumAlg_Bisection_Alg(const fun& theFunc)
			: fun(theFunc)
		{}


	public:

		//- public functions and operators

		void Perform(const Standard_Real x0, const Standard_Real x1)
		{
			auto ya = fun::Value(x0);
			auto yb = fun::Value(x1);

			ChangeNbIter() = 0;
			ChangeResidual() = (Standard_Real)0.;
			ChangeResult() = (Standard_Real)0.;

			if (ya*yb >= 0)
			{
				FatalErrorIn(FunctionSIG)
					<< "the values of f(x0) and f(x1) are not differ in sign!" << endl
					<< abort(FatalError);
			}

			auto b = x1;
			auto a = x0;

			ChangeA() = a;
			ChangeB() = b;

			Standard_Real yc, c;

			ChangeConverge() = Standard_False;

			forThose(Iter, 1, MaxNbIterations())
			{
				ChangeNbIter()++;

				c = 0.5*(a + b);
				yc = fun::Value(c);

				if (std::abs(yc) <= gp::Resolution())
				{
					a = c;
					b = c;
				}
				else if (AreSameSign(yb, yc))
				{
					b = c;
					yb = yc;
				}
				else
				{
					a = c;
					ya = yc;
				}

				if (std::abs(a-b) <= Delta() OR std::abs(yc) <= Tolerance())
				{
					ChangeConverge() = Standard_True;
					break;
				}
			}

			ChangeA() = a;
			ChangeB() = b;

			ChangeResult() = c;
			ChangeResidual() = yc;
			Change_IsDone() = Standard_True;
		}
	};

	template<class Function, bool RefInfo = true>
	class NumAlg_BisectionSolver
		: public NumAlg_Bisection_Alg<Function>
	{

		typedef Function fun;

		/*Private Data*/

		NumAlg_BisectionSolver_Info& theInfo_;


		Standard_Integer& ChangeNbIter() override
		{
			return theInfo_.ChangeNbIter();
		}

		Standard_Real& ChangeResidual() override
		{
			return theInfo_.ChangeResidual();
		}

		Standard_Real& ChangeResult() override
		{
			return theInfo_.ChangeResult();
		}

		Standard_Real& ChangeA()
		{
			return theInfo_.ChangeX0();
		}

		Standard_Real& ChangeB()
		{
			return theInfo_.ChangeX1();
		}

		Standard_Integer MaxNbIterations() const override
		{
			return theInfo_.MaxIterations();
		}

		Standard_Real Tolerance() const override
		{
			return theInfo_.Tolerance();
		}

		Standard_Real Delta() const override
		{
			return theInfo_.Delta();
		}

		Standard_Boolean& ChangeConverge() override
		{
			return theInfo_.Change_IsConverged();
		}

	public:

		//- default constructor


		//- constructors

		NumAlg_BisectionSolver
		(
			const Function& theFun, 
			NumAlg_BisectionSolver_Info& theInfo
		)
			: NumAlg_Bisection_Alg<Function>(theFun)
			, theInfo_(theInfo)
		{
			theInfo_.Reset();
		}

		//- public functions and operators

		const auto& Info() const
		{
			return theInfo_;
		}

		auto& InfoRef()
		{
			return theInfo_;
		}
	};

	template<class Function>
	class NumAlg_BisectionSolver<Function, false>
		: public NumAlg_Bisection_Alg<Function>
		, public NumAlg_BisectionSolver_Info
	{

		typedef Function fun;
		typedef NumAlg_BisectionSolver_Info info;

		/*Private Data*/

		Standard_Integer& ChangeNbIter() override
		{
			return info::ChangeNbIter();
		}

		Standard_Real& ChangeResidual() override
		{
			return info::ChangeResidual();
		}

		Standard_Boolean& ChangeConverge() override
		{
			return info::Change_IsConverged();
		}

		Standard_Real& ChangeResult() override
		{
			return info::ChangeResult();
		}

		Standard_Real& ChangeA()
		{
			return info::ChangeX0();
		}

		Standard_Real& ChangeB()
		{
			return info::ChangeX1();
		}

		Standard_Integer MaxNbIterations() const override
		{
			return info::MaxIterations();
		}

		Standard_Real Tolerance() const override
		{
			return info::Tolerance();
		}

		Standard_Real Delta() const override
		{
			return info::Delta();
		}

	public:

		//- default constructor


		//- constructors

		NumAlg_BisectionSolver(const Function& theFun)
			: NumAlg_Bisection_Alg<Function>(theFun)
		{}


	};
}

#endif // !_NumAlg_BisectionSolver_Header
