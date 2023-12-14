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
			
		public:

			// constructor

			MinTime_CostIntegFun
			(
				const obj& theObj, 
				const variable::State& theS0, 
				const Pnt2d& theP1
			)
				: theObj_(theObj)
				, theS0_(theS0)
				, theP1_(theP1)
			{}
			
			Standard_Real Value(const Standard_Real time) const;
		};

		
	}
}

Standard_Real
tnbLib::voyageLib::MinTime_CostIntegFun::Value(const Standard_Real time) const
{
	return theObj_.powFunc({ theS0_, {theP1_, {time}} }).value;
}

tnbLib::voyageLib::variable::Time
tnbLib::VoyageSim_MinTime_Cost::CalcTime
(
	const State& theS0,
	const Pnt2d& theP1,
	const Power& thePower
) const
{
	if (NOT powFunc)
	{
		FatalErrorIn(FunctionSIG) << endl
			<< "no function is found." << endl
			<< abort(FatalError);
	}
	voyageLib::MinTime_CostIntegFun bisectFun(*this, theS0, theP1);
	NumAlg_BisectionSolver<voyageLib::MinTime_CostIntegFun, true>
		alg(bisectFun, *IntegInfo());
	alg.Perform(TimeRange().first.value, TimeRange().second.value);
	Debug_If_Condition_Message(NOT alg.IsDone(), "the application is not performed!");
	return { MEAN(IntegInfo()->X0(), IntegInfo()->X1())};
}
