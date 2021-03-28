#pragma once
#ifndef _HydStatic_FreeSurfEff_Header
#define _HydStatic_FreeSurfEff_Header


#include <Global_Done.hxx>
#include <Marine_VesselParam_DISPV.hxx>
#include <HydStatic_Module.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HydStatic_CrossCurves;
	class HydStatic_rArmCurve;

	class HydStatic_FreeSurfEff
		: public Global_Done
	{

		/*Private Data*/

		marineLib::DISPV theTank_;
		marineLib::DISPV theShip_;

		std::shared_ptr<HydStatic_CrossCurves> theCrossCurves_;

		std::shared_ptr<HydStatic_rArmCurve> theRightingArm_;



		//- private functions and operators


		auto& ChangeRightingArm()
		{
			return theRightingArm_;
		}

	public:

		static TnbHydStatic_EXPORT bool verbose;


		//- default constructor

		TnbHydStatic_EXPORT HydStatic_FreeSurfEff();


		//- constructors

		TnbHydStatic_EXPORT HydStatic_FreeSurfEff
		(
			const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves, 
			const marineLib::DISPV& theTank,
			const marineLib::DISPV& theShip
		);



		//- public functions and operators

		const auto& TankDispv() const
		{
			return theTank_;
		}

		const auto& ShipDispv() const
		{
			return theShip_;
		}

		const auto& CrossCurves() const
		{
			return theCrossCurves_;
		}

		const auto& RightingArm() const
		{
			return theRightingArm_;
		}


		TnbHydStatic_EXPORT void Perform();

		TnbHydStatic_EXPORT void LoadCrossCurves
		(
			const std::shared_ptr<HydStatic_CrossCurves>& theCrossCurves
		);

		TnbHydStatic_EXPORT void LoadCrossCurves
		(
			std::shared_ptr<HydStatic_CrossCurves>&& theCrossCurves
		);

		TnbHydStatic_EXPORT void SetTankDispv(const marineLib::DISPV& theDispv);

		TnbHydStatic_EXPORT void SetTankDispv(marineLib::DISPV&& theDispv);

		TnbHydStatic_EXPORT void SetShipDispv(const marineLib::DISPV& theDispv);

		TnbHydStatic_EXPORT void SetShipDispv(marineLib::DISPV&& theDispv);

	};
}

#endif // !_HydStatic_FreeSurfEff_Header
