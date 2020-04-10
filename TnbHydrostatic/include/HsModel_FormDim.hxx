#pragma once
#ifndef _HsModel_FormDim_Header
#define _HsModel_FormDim_Header

#include <Vessel_FormDim.hxx>
#include <HydroStatic_PhysicsModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HsEntity_Vessel;

	class HsModel_FormDim
		: public Vessel_FormDim_Parameters
		, public HydroStatic_PhysicsModel
	{

		/*Private Data*/

		std::shared_ptr<HsEntity_Vessel> theVessel_;

		//- private functions

		// Calculate Auxiliaries

		void CalcFUW();

		void CalcAUW();

		void CalcAWL();

		void CalcFWL();


		// Calculate Dimensions

		void CalcB();

		void CalcBWL();

		void CalcD();

		void CalcFPP();

		void CalcAPP();

		void CalcLPP();

		void CalcMPP();

		void CalcLWL();

		void CalcLOS();

		void CalcLOA();

		// Calculate Area of stations

		//void CalcArea();

	public:

		HsModel_FormDim();

		const auto& Vessel() const
		{
			return theVessel_;
		}

		void Perform();

		void LoadVessel
		(
			const std::shared_ptr<HsEntity_Vessel>& theVessel
		)
		{
			theVessel_ = theVessel;
		}
	};
}

#endif // !_HsModel_FormDim_Header
