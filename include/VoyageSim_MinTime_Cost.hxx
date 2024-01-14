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
		typedef std::pair<var::Velocity, var::Velocity> velRange;

		std::function<var::Resistance(const var::Path&, const var::Distance&)> resistFunc;

	private:

		/*Private Data*/
		
		velRange theVelRange_;
		
		std::shared_ptr<NumAlg_BisectionSolver_Info> theInfo_;
		
		

	public:

		// default constructor

		VoyageSim_MinTime_Cost() = default;

		// constructors


		// Public functions and operators
		
		const auto& VelRange() const { return theVelRange_; }
		const auto& SolvInfo() const { return theInfo_; }

		TnbVoyage_EXPORT var::Time CalcTime
		(
			const var::State&,
			const Pnt2d&,
			const var::Power&,
			const var::Distance&
		) const;
		
		void SetVelRange(const velRange& theRange) { theVelRange_ = theRange; }
		void SetInfo(const std::shared_ptr<NumAlg_BisectionSolver_Info>& theInfo) { theInfo_ = theInfo; }
		
	};
}

#endif