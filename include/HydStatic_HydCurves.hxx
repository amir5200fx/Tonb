#pragma once
#ifndef _HydStatic_HydCurves_Header
#define _HydStatic_HydCurves_Header

#include <Global_Done.hxx>
#include <Marine_BodiesFwd.hxx>
#include <Marine_VesselParams.hxx>
#include <HydStatic_Module.hxx>

#include <memory>
#include <vector>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_Spacing;
	class HydStatic_HydCurvesGraph;
	class Marine_Body;
	class Marine_Domain;
	class Marine_BaseLine;
	class Marine_MultLevWaterDomain;
	class Marine_Wave;
	class NumAlg_AdaptiveInteg_Info;

	class HydStatic_HydCurves
		: public Global_Done
	{


		typedef NumAlg_AdaptiveInteg_Info info;

		/*Private Data*/

		Standard_Real theRhoS_;
		Standard_Real theRhoF_;
		Standard_Real theDisplFactor_;

		std::shared_ptr<Marine_MultLevWaterDomain> theWaters_;


		Standard_Boolean RudderAxis_;
		Standard_Real theRudderAxisLoc_;


		std::shared_ptr<HydStatic_HydCurvesGraph> theGraph_;


		//- private functions and operators

		TNB_SERIALIZATION(TnbHydStatic_EXPORT);


		static TnbHydStatic_EXPORT marineLib::TM 
			CalcTM
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody, 
				const std::shared_ptr<Marine_Wave>& theWave,
				const marineLib::APP& theApp, 
				const marineLib::FPP& theFpp
			);

		static TnbHydStatic_EXPORT marineLib::APP
			CalcAPP
			(
				const Standard_Real theAxis
			);

		static TnbHydStatic_EXPORT marineLib::APP
			CalcAPP
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody
			);

		TnbHydStatic_EXPORT std::tuple
			<
			marineLib::CB, 
			marineLib::CM,
			marineLib::CP,
			marineLib::CWL,
			marineLib::LCF,
			marineLib::LCB,
			marineLib::AW, 
			marineLib::MCT,
			marineLib::KML,
			marineLib::KM, 
			marineLib::KB,
			marineLib::DISPV
			>
			CalcParameters
			(
				const std::shared_ptr<marineLib::Body_Wetted>& theBody, 
				const Marine_BaseLine& theBase, 
				const std::shared_ptr<Marine_Wave>& theWave,
				const std::shared_ptr<info>& theInfo
			);

		auto & GraphRef()
		{
			return theGraph_;
		}

	public:

		static TnbHydStatic_EXPORT size_t clippNo;
		static TnbHydStatic_EXPORT size_t verbose;

		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_RHOSW;
		static TnbHydStatic_EXPORT const Standard_Real DEFAULT_RHOFW;

		HydStatic_HydCurves()
			: RudderAxis_(Standard_False)
			, theRudderAxisLoc_(0)
			, theDisplFactor_(0)
			, theRhoF_(DEFAULT_RHOFW)
			, theRhoS_(DEFAULT_RHOSW)
		{}


		//- public functions and operators

		Standard_Real RhoSW() const
		{
			return theRhoS_;
		}

		Standard_Real RhoFW() const
		{
			return theRhoF_;
		}

		Standard_Real DisplFactor() const
		{
			return theDisplFactor_;
		}

		const auto& Waters() const
		{
			return theWaters_;
		}

		auto RudderAxis() const
		{
			return RudderAxis_;
		}

		auto RudderAxisLoc() const
		{
			return theRudderAxisLoc_;
		}

		const auto& Graph() const
		{
			return theGraph_;
		}

		TnbHydStatic_EXPORT void Perform();

		void LoadWaters
		(
			const std::shared_ptr<Marine_MultLevWaterDomain>& theWaters
		)
		{
			theWaters_ = theWaters;
		}

		TnbHydStatic_EXPORT void SetRudderLocation(const Standard_Real x);

		void SetRhoSW
		(
			const Standard_Real rho
		)
		{
			theRhoS_ = rho;
		}

		void SetRhoFW
		(
			const Standard_Real rho
		)
		{
			theRhoF_ = rho;
		}

		void SetDisplFactor
		(
			const Standard_Real x
		)
		{
			theDisplFactor_ = x;
		}
	};
}

#endif // !_HydStatic_HydCurves_Header
