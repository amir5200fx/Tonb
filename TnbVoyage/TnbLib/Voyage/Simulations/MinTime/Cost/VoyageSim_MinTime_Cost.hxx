#pragma once
#ifndef _VoyageSim_MinTime_Cost_Header
#define _VoyageSim_MinTime_Cost_Header

#include <VoyageSim_Variables.hxx>
#include <Voyage_Module.hxx>
#include <Pnt2d.hxx>
#include <Dir2d.hxx>

#include <tuple>

namespace tnbLib
{

	// Forward Declarations
	class NumAlg_BisectionSolver_Info;
	
	class VoyageSim_MinTime_Cost
	{

	public:

		using voyageLib::variable::Resistance;
		using voyageLib::variable::Velocity;
		using voyageLib::variable::SOG;
		using voyageLib::variable::Time;
		using voyageLib::variable::Power;
		using voyageLib::variable::State;
		using voyageLib::variable::Path;
		using voyageLib::variable::NbSamples;

		typedef std::pair<Time, Time> timeRange;

		std::function<Power(const Path&)> powFunc;

	private:

		/*Private Data*/

		timeRange theTimeRange_;
		std::shared_ptr<NumAlg_BisectionSolver_Info> theIntegInfo_;
		
		

	public:

		// default constructor

		VoyageSim_MinTime_Cost() = default;

		// constructors


		// Public functions and operators

		const auto& TimeRange() const { return theTimeRange_; }
		const auto& IntegInfo() const { return theIntegInfo_; }

		TnbVoyage_EXPORT Time CalcTime(const State&, const Pnt2d&, const Power&) const;

		void SetTimeRange(const timeRange& theRange) { theTimeRange_ = theRange; }
		
	};
}

#endif