#include <VoyageSim_MinTime_Cost.hxx>

#include <Voyage_Tools.hxx>
#include <NumAlg_BisectionSolver.hxx>

namespace tnbLib
{
	namespace voyageLib
	{
		
		class MinTime_CostIntegFun
		{

		public:

			typedef VoyageSim_MinTime_Cost obj;
			
		private:

			/*Private Data*/

			const obj& theObj_;

			
			const variable::State& theS0_;
			const Pnt2d& theP1_;
			const var::Distance& theDist_;
			const var::Power& thePower_;
			
		public:

			// constructor

			MinTime_CostIntegFun
			(
				const obj& theObj, 
				const variable::State& theS0, 
				const Pnt2d& theP1,
				const var::Distance& theDist,
				const var::Power& thePower
			)
				: theObj_(theObj)
				, theS0_(theS0)
				, theP1_(theP1)
				, theDist_(theDist)
				, thePower_(thePower)
			{}
			
			Standard_Real Value(const Standard_Real velocity) const;
		};

		
	}
}

Standard_Real
tnbLib::voyageLib::MinTime_CostIntegFun::Value(const Standard_Real U) const
{
	const auto t = theDist_.value / U;
	const auto resist = theObj_.resistFunc({ theS0_, {theP1_, {t}} }, theDist_).value;
	const auto power = resist * U;
	const auto value = power - thePower_.value;
	return value;
}

tnbLib::voyageLib::variable::Time
tnbLib::VoyageSim_MinTime_Cost::CalcTime
(
	const var::State& theS0,
	const Pnt2d& theP1,
	const var::Power& thePower,
	const var::Distance& theDist
) const
{
	if (NOT resistFunc)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no function is found." << endl
			<< abort(FatalError);
	}
	const voyageLib::MinTime_CostIntegFun bisectFun(*this, theS0, theP1, theDist, thePower);
	NumAlg_BisectionSolver<voyageLib::MinTime_CostIntegFun, true>
		alg(bisectFun, *SolvInfo());
	try
	{
		alg.Perform(VelRange().first.value, VelRange().second.value);
		Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed!");
		const auto vel = MEAN(SolvInfo()->X0(), SolvInfo()->X1());
		return { theDist.value / vel };
	}
	catch (const error& x)
	{
		return  theS0.time;
	}
}
