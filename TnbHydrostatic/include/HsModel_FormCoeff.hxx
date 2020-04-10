#pragma once
#ifndef _HsModel_FormCoeff_Header
#define _HsModel_FormCoeff_Header

#include <Vessel_FormCoeff.hxx>
#include <HydroStatic_PhysicsModel.hxx>

namespace tnbLib
{

	// Forward Declarations
	class HsModel_FormDim;
	class HsEntity_Vessel;

	class HsModel_FormCoeff
		: public Vessel_FormCoeff_Parameters
		, public HydroStatic_PhysicsModel
	{

		/*Private Data*/

		std::shared_ptr<HsModel_FormDim> theFormDim_;

		std::shared_ptr<HsEntity_Vessel> theVessel_;


		//- private functions

		void CalcVolume();

		void CalcCB();

		void CalcAM();

		void CalcCP();

		void CalcCM();

		void CalcAW();

		void CalcCWL();

		void CalcCVP();

		void CalcWettedArea();

		void CalcLCB();

		void CalcVCB();

		void CalcKB();

	public:

		HsModel_FormCoeff();

		const auto& FormDim() const
		{
			return theFormDim_;
		}

		const auto& Vessel() const
		{
			return theVessel_;
		}
	};
}

#endif // !_HsModel_FormCoeff_Header
