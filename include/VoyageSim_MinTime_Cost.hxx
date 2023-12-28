#pragma once
#ifndef _VoyageSim_MinTime_Cost_Header
#define _VoyageSim_MinTime_Cost_Header

#include <VoyageSim_Variables.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <tuple>
#include <VoyageFun_CostFunction.hxx>

namespace var = tnbLib::voyageLib::variable;

namespace tnbLib
{
	
	// Forward Declarations
	class NumAlg_BisectionSolver_Info;
	
	class VoyageSim_MinTime_Cost
	{

	public:

		

		typedef std::pair<var::Time, var::Time> timeRange;

		std::function<var::Power(const var::Path&, const var::Distance&)> powFunc;

	private:

		/*Private Data*/

		timeRange theTimeRange_;
		
		std::shared_ptr<NumAlg_BisectionSolver_Info> theInfo_;
		
		

	public:

		// default constructor

		VoyageSim_MinTime_Cost() = default;

		// constructors


		// Public functions and operators

		const auto& TimeRange() const { return theTimeRange_; }
		const auto& SolvInfo() const { return theInfo_; }

		TnbVoyage_EXPORT var::Time CalcTime(const var::State&, const Pnt2d&, const var::Power&, const var::Distance&) const;
		
		void SetTimeRange(const timeRange& theRange) { theTimeRange_ = theRange; }
		void SetInfo(const std::shared_ptr<NumAlg_BisectionSolver_Info>& theInfo) { theInfo_ = theInfo; }
		
	};
}

#endif