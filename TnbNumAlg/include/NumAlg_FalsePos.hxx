#pragma once
#ifndef _NumAlg_FalsePos_Header
#define _NumAlg_FalsePos_Header

#include <Global_Bound.hxx>
#include <Global_Done.hxx>
#include <NumAlg_FalsePos_Info.hxx>
#include <NumAlg_System.hxx>

namespace tnbLib
{

	//class NumAlg_FalsePos_Bound
	//	: public Global_Bound<Standard_Real>
	//{

	//	/*Private Data*/

	//protected:

	//	NumAlg_FalsePos_Bound
	//	(
	//		const Standard_Real theLower = 0,
	//		const Standard_Real theUpper = 0
	//	)
	//		: Global_Bound<Standard_Real>(theLower, theUpper)
	//	{}

	//};

	struct NumAlg_FalsePos_Function
	{
		virtual Standard_Real Value(const Standard_Real) const
		{
			Iter::ChackFun("Standard_Real Value(const Standard_Real) const");
			return 0;
		}
	};

	template<class Function>
	class NumAlg_FalsePos_Alg
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

	protected:

		NumAlg_FalsePos_Alg(const fun& theFun)
			: fun(theFun)
		{}

	public:

		void Perform(const Standard_Real x0, const Standard_Real x1)
		{
			//fun::CheckBound(x0);
			//fun::CheckBound(x1);

			auto ya = fun::Value(x0);
			auto yb = fun::Value(x1);

			ChangeNbIter() = 0;
			ChangeResidual() = (Standard_Real)0.;
			ChangeResult() = (Standard_Real)0.;

			auto b = x1;
			auto a = x0;

			ChangeA() = a;
			ChangeB() = b;

			Standard_Real yc, c;

			ChangeConverge() = Standard_False;

			forThose(Iter, 1, MaxNbIterations())
			{
				ChangeNbIter()++;

				auto dx = yb * (b - a) / (yb - ya);
				c = b - dx;

				yc = fun::Value(c);

				if (yb*yc > 0)
				{
					b = c;
					yb = yc;	
				}
				else
				{
					a = c;
					ya = yc;	
				}

				if (ABS(dx) <= Delta() OR ABS(yc) <= Tolerance())
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
	class NumAlg_FalsePos
		: public NumAlg_FalsePos_Alg<Function>
	{

		typedef Function fun;

		/*Private Data*/

		NumAlg_FalsePos_Info& theInfo_;


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

		NumAlg_FalsePos
		(
			const Function& theFunction,
			NumAlg_FalsePos_Info& theInfo
		)
			: NumAlg_FalsePos_Alg<Function>(theFunction)
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
	class NumAlg_FalsePos<Function, false>
		: public NumAlg_FalsePos_Alg<Function>
		, public NumAlg_FalsePos_Info
	{

		typedef Function fun;
		typedef NumAlg_FalsePos_Info info;

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

		NumAlg_FalsePos
		(
			const Function& theFunction
		)
			: NumAlg_FalsePos_Alg<Function>(theFunction)
		{}
	};
}

#endif // !_NumAlg_FalsePos_Header
